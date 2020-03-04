//
// Created by AlexFan on 2020/3/2.
//

#include "func_filesystem.h"
#include<iostream>
#include<cstring>

using namespace std;
int disk_storage=10000; //全局变量虚拟磁盘空闲空间大小
string error[] = {"/","\\", ":","<",">","|","*","&"} ;  //命名中的非法字符

func_filesystem::func_filesystem() {
    size = 0;
    currentDir = nullptr;
    copytempfile = nullptr;
}//初始化文件系统

func_filesystem::~func_filesystem() {//释放用户所占空间
    disk_storage += size;
    size = 0;				// 置0

    directory *d = root;
    file *f = currentDir->filePtr;
    while (f != nullptr) {
        if (f->nextFile == nullptr) {
            this->dele_file(f);
            f = nullptr;
            break;
        }
        while (f->nextFile->nextFile != nullptr)
            f = f->nextFile;
        this->dele_file(f->nextFile);
        f->nextFile = nullptr;
        f = currentDir->filePtr;
    }
    while (d != nullptr) {
        if (d->nextDir == nullptr) {
            this->dele_dir(d);
            d = nullptr;
            break;
        }
        while (d->nextDir->nextDir != nullptr)
            d = d->nextDir;
        this->dele_dir(d->nextDir);
        d->nextDir = nullptr;
        d = root;
    }
    cout << "已释放所有资源" << endl;
}//释放存储空间

int func_filesystem::newFile() {

    file *p = nullptr;
    p = new file;

    if (p == nullptr) {
        cout << "CREATE           -FALSE";
        return 0;
    }
    cin>>p->name ;
    /*命名检测*/
    string tempname(p->name) ;
    for(int i = 0 ;i< 8 ;++i)
    {
        if(tempname.find(error[i],0)!=string::npos)//从字符串的下标为0处开始查找error[i],如果没找到，返回一个特别的标志c++中用npos表示
        {
            cout << "RENAME            -FALSE"<<endl;
            return 0 ;
        }
    }

    /*创建时候情况如下
     * 1. 目录下没有文件
     * 2. 目录下有文件，新文件命名冲突
     * 3. 目录下有文件，新文件无命名冲突
     * */
    /*检测有无同名函数*/
    if (currentDir->filePtr == nullptr) {
        p->nextFile = currentDir->filePtr;
        currentDir->filePtr = p;
    } else {
        file *q = new file;
        q = currentDir->filePtr;
        while (q != nullptr) {
            if (strcmp(p->name, q->name)==0) {
                cout << "FILE EXISTS             -FALSE" << endl;
                return 0;
            }
            q = q->nextFile;
        }

        /*重置链表结构*/
        p->nextFile = currentDir->filePtr;
        //p->size=0;
        currentDir->filePtr = p;
        directory *h = currentDir;

        /*更改上级目录的大小*/
        while (h != nullptr) {
            h->size += p->size;
            h = h->preDir;
        }

    }
    currentDir->filePtr->size = 0;
    cout <<"CREATE             -OK" << endl;
    disk_storage = disk_storage - p->size;
    size += p->size;
    return 1;
}//touch

int func_filesystem::newDir() {
    directory *p, *h;
    p = new directory;
    cin >> p->name;

    /*命名检测*/
    string tempname(p->name) ;
    for(int i = 0 ;i< 8 ;++i)
    {
        if(tempname.find(error[i],0)!=string::npos)
        {
            cout << "RENAME              -FALSE"<<endl;
            return 0 ;
        }
    }


    p->dirPtr = nullptr;
    p->size = 0;
    p->filePtr = nullptr;
    p->nextDir = nullptr;
    if (currentDir->dirPtr == nullptr)
        h = nullptr;
    else
        h = currentDir->dirPtr;

    /*创建时候情况如下
     * 1. 目录下没有子目录
     * 2. 目录下有子目录，命名冲突
     * 3. 目录下有子目录，无命名冲突
     * */
    /*检测有无同名目录*/

    while (h != nullptr) {
        if (strcmp(h->name, p->name)==0) {
            cout << "DIR EXISTS           -FALSE" << endl;
            return 0;
        }
        h = h->nextDir;
    }

    /*重置链表结构*/
    p->preDir = currentDir;
    p->nextDir = currentDir->dirPtr;
    currentDir->dirPtr = p;

    cout << "CREATE                -OK" << endl;
    return 1;
}//mkdir

int func_filesystem::dele_file(file *f) {
    delete f;
    f = nullptr;
    return 1;
}//rm

int func_filesystem::deleteFile() {
    char temp[NAME_LENGTH];

    cin >> temp;
    file *f;
    file *above = nullptr;
    f = currentDir->filePtr;

    /*
     * 判断该目录下有无需要删除的文件
     * */

    while (f != nullptr) {
        if (!strcmp(f->name, temp))
            break;
        above = f;
        f = f->nextFile;
    }
    if (f == nullptr) {
        cout << "NO FILE              -FALSE" << endl;
        return 0;
    }
    disk_storage += f->size;
    directory *d = currentDir;
    while (d != 0) //修改删除文件后各级目录的大小
    {
        d->size -= f->size;
        d = d->preDir;
    }

    /*
     * 删除时考虑
     * 1. 需要删除的文件恰好是目录文件链表中的头节点
     * 2. 需要删除的文件在链表中间
     * */

    if (f == currentDir->filePtr)//删除文件结点
        currentDir->filePtr = currentDir->filePtr->nextFile;
    else
        above->nextFile = f->nextFile;
    size -= f->size;
    delete f;
    f = nullptr;
    cout << "DELETE             -OK" << endl;
    return 1;
}//rm

int func_filesystem::dele_dir(directory *d) {
    delete d;
    d = nullptr;
    return 1;
}//rmdir

int func_filesystem::deleteDir() {
    char n[NAME_LENGTH];

    directory *p, *pre = nullptr;
    p = root;
    p = currentDir->dirPtr;
    cin >> n; //删除的文件名

    /*查找所需要删除的目录*/
    while (p != nullptr) {
        if (strcmp(p->name, n)==0)
        {pre = p;break;}
        p = p->nextDir;
    }

    if (p == nullptr) {
        cout << "DELETE            -FALSE" << endl;
        return 0;
    }

    /*删除目录时需要考虑
     * 1. 该目录处于父目录的目录链表的位置
     * 2. 该目录下是否有子目录或者子文件
     * */
    disk_storage += p->size;
    if (p == currentDir->dirPtr)
        currentDir->dirPtr = currentDir->dirPtr->nextDir;
    else
        p->preDir->nextDir = p->nextDir;

    pre = currentDir;
    while (pre != nullptr) //修改删除目录后各级目录大小
    {
        pre->size -= p->size;
        pre = pre->preDir;
    }
    size -= p->size;
    directory *d = p->dirPtr;
    file *f = p->filePtr;
    if (f != nullptr) {
        while (p->filePtr->nextFile != nullptr)//删除此目录下的文件
        {
            f = p->filePtr;
            while (f->nextFile->nextFile != nullptr)//寻找最后一个文件结点
                f = f->nextFile;
            this->dele_file(f->nextFile);
            f->nextFile = nullptr;
        }
        if (p->filePtr->nextFile == nullptr) {
            this->dele_file(p->filePtr);
            p->filePtr = nullptr;
        }
    }
    if (d != nullptr) {
        while (p->dirPtr->nextDir != nullptr)//删除此目录下的目录
        {
            d = p->dirPtr;
            while (d->nextDir->nextDir != nullptr)//寻找最后一个文件结点
                d = d->nextDir;
            this->dele_dir(d->nextDir);//递归调用此函数
            d->nextDir = nullptr;
        }
        if (p->dirPtr->nextDir == nullptr) {
            this->dele_dir(p->dirPtr);
            p->dirPtr = nullptr;
        }
    }
    delete p,d,f;

    cout << "DELETE           -OK" << endl;
    return 1;

}//rmdir

int func_filesystem::open_dir() {
    char name[NAME_LENGTH];
    directory *p;
    p = currentDir->dirPtr;

    cin >> name;
    while (p != nullptr) {
        if (strcmp(p->name, name) == 0) {
            currentDir = p;
            return 1;
        }
        p = p->nextDir;
    }
    cout << "NO DIR             -FALSE" << endl;
    return 0;
}//cd

int func_filesystem::open_file() {
    char n[NAME_LENGTH];
    cin >> n;
    file *f = currentDir->filePtr;
    while (f != nullptr) {
        if (strcmp(f->name, n)==0) {
            cout << f->content << endl;
            return 1;
        }
        f = f->nextFile;
    }
    cout << "NO FILE              -FALSE" << endl;
    return 0;
}//open

file *func_filesystem::copy_file(file *h) {
    file *f;
    f = new file;
    f->size = h->size;
    strcpy(f->name, h->name);
    f->content = h->content;
    return f;
}//cp

file *func_filesystem::copyFile() {
    file *h;
    char n[NAME_LENGTH];
    cin >> n;
    h = currentDir->filePtr;

    while (h != nullptr) {
        if (!strcmp(h->name, n))
            break;
        h = h->nextFile;
    }
    if (h == nullptr) {
        cout << "NO FILE             -FALSE" << endl;
        return nullptr;
    }
    copytempfile = copy_file(h);
    cout << "COPY             -OK" << endl;
    return copytempfile;
}//cp

int func_filesystem::pasteFile() {
    file *h = currentDir->filePtr;
    file *pTemp = h;
    if (copytempfile == nullptr) {
        cout << "NO SOURCE              -FALSE" << endl;
        return 0;
    }
    /*如果当前目录没有文件*/
    if (h == nullptr) {
        if (disk_storage < copytempfile->size) {
            cout << "NO ENOUGH SPACE            -FALSE";
            return 0;
        }
        currentDir->filePtr = copy_file(copytempfile);
        currentDir->size += copytempfile->size;
    }
    else {
        while (h != nullptr) {
            if (!strcmp(h->name, copytempfile->name)) {
                cout << "FILE EXISTS                -FALSE" << endl;
                return 0;
            }
            //break;
            h = h->nextFile;
        }

        if (disk_storage < copytempfile->size) {
            cout << "NO ENOUGH SPACE              -FALSE";
            return 0;
        }
        currentDir->filePtr = copy_file(copytempfile);
        currentDir->filePtr->nextFile = pTemp;
        //currentDir->filePtr->nextFile = h;
        currentDir->size += copytempfile->size;
        cout << "PASTE                -OK" << endl;
        return 1;
    }
    return 0;

}//paste

int func_filesystem::write() {
    char n[NAME_LENGTH];
    string s;
    cin >> n;
    file *f = currentDir->filePtr;
    while (f != 0) {
        if (!strcmp(f->name, n)) {
            cin >> s;
            f->content = s;
            f->size = s.length();
            disk_storage -= f->size;
            directory *d = currentDir;
            while (d != 0)//修改编辑文件后各级目录的大小
            {
                d->size += f->size;
                d = d->preDir;
            }
            cout << "EDIT              -OK" << endl;
            size += f->size;
            return 1;
        }
        f = f->nextFile;
    }

    cout << "NO FILE                -FALSE" << endl;
    return 0;
}//vi


int func_filesystem::ls() {
    directory *d = currentDir->dirPtr;
    file *f = currentDir->filePtr;
    if (d == nullptr && f == nullptr) {
        return 0;
    }
    if (d != nullptr) {
        while (d != nullptr) {
            cout << d->name<<endl;
            d = d->nextDir;
        }
        cout << endl;
    }

    if (f != nullptr) {
        while (f != nullptr) {
            cout << f->name<< endl;
            f = f->nextFile;
        }
    }
    return 1;
}//打印目录下所有文件/文件夹

int func_filesystem::show_path(directory *d)//实现显示当前路径的函数
{
    if (d->preDir == nullptr)
        cout << root->name;
    if (d->preDir != nullptr) {
        this->show_path(d->preDir);//递归调用此函数
        cout << d->name;
    }
    cout << "/";
    return 1;
}

int func_filesystem::showPath()//显示当前路径
{
    cout<<"#";
    show_path(currentDir);
    return 1;
}
int func_filesystem::pwd(){
    cout << "The current directory： ";
    show_path(currentDir);
    return 0;
}//打印当前目录

int func_filesystem::goback() {
    if (currentDir->preDir == nullptr) {
        cout << "当前目录为根目录" << endl;
        return 0;
    }
    currentDir = currentDir->preDir;
    return 1;
}//cd ..

int func_filesystem::setUser(char *n, char *c) {
    directory *root = new directory;
    strcpy(root->name, n);
    strcpy(name, n);
    strcpy(password, c);

    this->root = root;
    currentDir = root;
    currentDir->preDir = nullptr;
    currentDir->dirPtr = nullptr;
    currentDir->filePtr = nullptr;
    currentDir->nextDir = nullptr;
    return 1;
}

