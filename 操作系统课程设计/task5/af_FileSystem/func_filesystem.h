//
// Created by AlexFan on 2020/3/2.
//

#ifndef AF_func_filesystem_FUNC_func_filesystem_H
#define AF_func_filesystem_FUNC_func_filesystem_H
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define NAME_LENGTH  20    //文件名或者目录名字最大字节数
extern int disk_storage;


typedef struct file         //文件结构体
{
    char name[NAME_LENGTH];      //文件名 
    int size;                 //文件大小
    struct file *nextFile;  //指向文件列表中下一个文件
    string content;           //文件内容
} file;

typedef struct directory          //目录结构体
{
    char name[NAME_LENGTH];      //目录名字
    int size;                 //目录大小
    directory *nextDir;           //后继目录
    directory *preDir;            //前继目录
    file *filePtr;          //该目录下的文件链表指针
    directory *dirPtr;            //该目录下的目录链表指针
} directory;


class func_filesystem //文件系统类
{
private:
    directory *currentDir; //当前目录
    file *copytempfile; //用于拷贝文件时的临时文件
    directory *root; //根目录
    char password[NAME_LENGTH];   //用户密码
    char name[NAME_LENGTH];   //用户名称
    int size; //用户所使用空间大小

public:
    func_filesystem();//构造函数
    ~func_filesystem();//析构函数

    /*
    *文件操作
    */
public:
    int newFile(); //创建文件
    int dele_file(file *file);//删除文件
    int deleteFile(); //删除文件前的逻辑判断
    int open_file(); //打开文件
    file *copy_file(file *h); //复制文件
    file *copyFile(); //复制文件前的逻辑判断
    int pasteFile(); //粘贴文件
    int write(); //编辑文件

    /*
     * 目录操作
     */
public:
    int newDir(); //创建目录
    int dele_dir(directory *d); //删除目录
    int deleteDir(); //删除目录前的逻辑判断
    int open_dir(); //打开目录
    int ls(); //显示当前目录内容

    /*
     * 路径操作
     */
public:
    int show_path(directory *dir); //显示路径的部分实现
    int showPath(); //显示路径
    int pwd();
    int goback(); //返回上一级目录

    /*
     * 用户操作
     */
public:
    int setUser(char *, char *);//设置用户名与密码
};
#endif //AF_func_filesystem_FUNC_func_filesystem_H
