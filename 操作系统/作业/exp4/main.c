#include"main.h"

#include<sys/stat.h>//目录状态
#include<sys/types.h>
#include<sys/cdefs.h>

#include<bsd/string.h>
#include<grp.h>
#include<pwd.h>
#include<dirent.h>
#include<libgen.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<locale.h>//调用语言

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("在 ./main 后输入目录或文件名\n");
        return 1;
    }
    setlocale(LC_COLLATE, "");//程序调用当前linux系统语言
    char *path = malloc(strlen(argv[1]) + 1);
    strcpy(path, argv[1]);//将路径拷入
    printdir(path, 0);//调用递归函数进行打印目录.
    free(path);
}

static time_t now;//时间
//递归全部目录
int printdir(char *dir, int depth) {
    now = time(NULL);
    char *oldir = NULL;
    long currentPathSize = pathconf(".", _PC_PATH_MAX);
    oldir = getcwd(oldir, currentPathSize);
    char *dirTemp = malloc(strlen(dir) + 1);
    strcpy(dirTemp, dir);
    char *dirBase = basename(dirTemp);
    struct stat statusTemp;
    stat(dirBase, &statusTemp);
    __blkcnt_t blockTotalCount = 0;
    DIR *nowdir = NULL;
    if (dir[0] == '/') {
        if ((nowdir = opendir(dir)) == NULL) {
            perror("Failed to open directory");
            return 1;
        }
        chdir(dir);//cd
    } else {
        if ((nowdir = opendir(dirBase)) == NULL) {
            perror("Failed to open directory");
            return 1;
        }
        chdir(dirBase);//cd
    }

    printf("%s:\n", dir);

    struct dirent *entryItems;
    struct dirent *entryTemp;
    size_t entryCount = 0;
    while ((entryTemp = readdir(nowdir)))
        entryCount++;
    entryItems = (struct dirent *)malloc(entryCount * sizeof(struct dirent));
    rewinddir(nowdir);//回到开头
    for (int i = 0; (entryTemp = readdir(nowdir)); ++i)
        memcpy(entryItems + i, entryTemp, sizeof(struct dirent));
    qsort(entryItems, entryCount, sizeof(struct dirent), sortdir);//目录排序
    __nlink_t maxLinkNum = 0;
    __off_t maxSize = 0;
    int sizeWidth = 0, linkWidth = 0;
    struct stat status;
    for (int i = 0; i < entryCount; ++i) {
        entryTemp = entryItems + i;
        stat(entryTemp->d_name, &status);
        // update max size
        if (status.st_size > maxSize)
            maxSize = status.st_size;
        // update total block size
        if (entryTemp->d_name[0] != '.' &&
                strcmp(entryTemp->d_name, ".") &&
                strcmp(entryTemp->d_name, "..") ) {
            blockTotalCount += status.st_blocks;
            // update max link-num
            if (status.st_nlink > maxLinkNum)
                maxLinkNum = status.st_nlink;
        }
    }
    for (; maxLinkNum; maxLinkNum /= 10)
        ++linkWidth;
    for (; maxSize; maxSize /= 10)
        ++sizeWidth;
    printf("total %lu\n", blockTotalCount * 512 / LS_BLOCK_SIZE );
    // read and print currnet entries
    rewinddir(nowdir);
    for (int i = 0; i < entryCount; ++i) {
        entryTemp = entryItems + i;
        // skip current and upper directory
        if (strcmp(entryTemp->d_name, ".") &&               // pass current file
                strcmp(entryTemp->d_name, "..") &&          // pass upper file
                entryTemp->d_name[0] != '.')                // pass hidden file
            printdetail(entryTemp, linkWidth, sizeWidth);
    }
    rewinddir(nowdir);
    for (int i = 0; i < entryCount; ++i) {
        entryTemp = entryItems + i;
        if (entryTemp->d_type == DT_DIR &&
                entryTemp->d_name[0] != '.' &&             // pass current file
                strcmp(entryTemp->d_name, ".") &&          // pass upper file
                strcmp(entryTemp->d_name, "..") ) {        // pass hidden file

            // construct path
            char *dirTemp = (char *)malloc(strlen(dir) + strlen(entryTemp->d_name) + 2);
            strcpy(dirTemp, dir);
            if (dir[strlen(dir) - 1] != '/')
                strcat(dirTemp, "/");
            strcat(dirTemp, entryTemp->d_name);
            putchar('\n');
            printdir(dirTemp, depth + 1);
            free(dirTemp);
        }
    }
    closedir(nowdir);
    chdir(oldir);
    free(oldir);
    free(entryItems);
    return 0;
}
//打印目录全部信息
int printdetail(struct dirent *entry, int fmtLinkWidth, int fmtSizeWidth) {
    struct stat status;
    if (stat(entry->d_name, &status) == 0) {
        struct passwd *passwdTemp;
        struct group *groupTemp;
        passwdTemp = getpwuid(status.st_uid);
        groupTemp = getgrgid(status.st_gid);
        struct tm *timeTemp = localtime(&(status.st_mtime));
        char strTime[20];
        if (now - status.st_mtime > (365 * 24 * 60 * 60 / 2) || now < status.st_mtime) {
            strftime(strTime, 20, "%b %_d  %Y", timeTemp);
        } else {
            strftime(strTime, 20, "%b %_d %H:%M", timeTemp);
        }
        printf( (S_ISDIR(status.st_mode)) ? "d" : "-");
        printf( (status.st_mode & S_IRUSR) ? "r" : "-");
        printf( (status.st_mode & S_IWUSR) ? "w" : "-");
        printf( (status.st_mode & S_IXUSR) ? "x" : "-");
        printf( (status.st_mode & S_IRGRP) ? "r" : "-");
        printf( (status.st_mode & S_IWGRP) ? "w" : "-");
        printf( (status.st_mode & S_IXGRP) ? "x" : "-");
        printf( (status.st_mode & S_IROTH) ? "r" : "-");
        printf( (status.st_mode & S_IWOTH) ? "w" : "-");
        printf( (status.st_mode & S_IXOTH) ? "x" : "-");
        printf("%*ld %s %s %*ld %s %s\n",
                fmtLinkWidth, status.st_nlink,
                passwdTemp->pw_name,
                groupTemp->gr_name,
                fmtSizeWidth, status.st_size,
                strTime,
                entry->d_name);
        return 0;
    }
    return 1;
}
//目录排序算法
int sortdir(const void *a, const void *b) {
    struct dirent *dirA = (struct dirent *) a,
                   *dirB = (struct dirent *)b;
    return strcoll(dirA->d_name, dirB->d_name);
}