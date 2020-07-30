//
// Created by AlexFan on 2020/3/2.
//
#include<iostream>
#include<string>
#include"func_filesystem.h"
#include"ui_filesystem.h"
#include<Windows.h>
using namespace std;

void start(){
    int choice = 0;
    char name[30], pass[30], pass1[30];
    system("CLS");
    Sleep(2);
    while (true) {
        system("CLS");
        cout << "\t\t————————————————————————————————————————\t" << endl;
        cout << "\t\t          Alex Fan File System           \t" << endl;
        cout << "\t\t               1. sign up               \t" << endl;
        cout << "\t\t               2. login                    \t" << endl;
        cout << "\t\t               3. help                    \t" << endl;
        cout << "\t\t               4. sign out                    \t" << endl;
        cout << "\t\t————————————————————————————————————————\t" << endl;
        cout << "\t\t请选择(请输入数字编号): " ;
        cin >> choice;
        switch (choice) {
            /*选择注册*/
            case 1: {
                cout << "请输入用户名:";
                cin >> name;
                cout << "请输入密码: ";
                cin >> pass;
                cout << "请确认密码: ";
                cin >> pass1;
                while (strcmp(pass, pass1) != 0) {
                    cout << "密码不一致，请重试" << endl;
                    cout << "请输入密码: ";
                    cin >> pass;
                    cout << "请确认密码: ";
                    cin >> pass1;
                }
                if (regist(name, pass) == 1){
                    cout << "注册成功.." << endl;
                    Sleep(2);
                }
                else{
                    cout << "注册失败" << endl;
                    Sleep(2);
                }
            }
                break;

                /*选择登录*/
            case 2: {
                cout << "请输入用户名:";
                cin >> name;
                cout << "请输入密码:";
                cin >> pass;
                if (login(name, pass) == 1) {
                    cout << "登录成功" << endl;
                    operate(name, pass);

                } else{
                    cout << "登录失败，请检查用户名和密码" << endl;
                    Sleep(2);
                }}
                break;
            case 3:{
                system("CLS");
                help();
                system("Pause");
            }break;

            case 4: {
                system("CLS");
                cout << "退出文件系统" << endl;
                Sleep(3);
                exit(0);
            }
                break;
                /*其他选项*/
            default:
                cout << "命令不存在，请重新选择"<< endl;

                break;
        }
    }

}//开始文件系统
void help() {
    cout << "-------------------------------------------------------------" << endl;
    cout << "-----------------Alex Fan File System 操作手册----------------" << endl;
    cout << " 1.touch + <文件名>                                新建文件   " << endl;
    cout << " 2.rm + <文件名>                                   删除文件   " << endl;
    cout << " 3.cp + <文件名>                                   复制文件   " << endl;
    cout << " 4.ps                                             粘贴文件   " << endl;
    cout << " 5.open + <文件名>                                 打开文件   " << endl;
    cout << " 6.vi + <文件名>                                   编辑文件   " << endl;
    cout << " 7.mkdir + <文件名>                                新建目录   " << endl;
    cout << " 8.rmdir + <文件名>                                删除目录   " << endl;
    cout << " 9.ls                                             展开目录   " << endl;
    cout << " 10.cd + <文件名>                                  进入下级目录" << endl;
    cout << " 11.cd..                                          返回上级目录" << endl;
    cout << " 12.clear                                         清屏       " << endl;
    cout << " 13.exit                                          注销       " << endl;
    cout << "—————————————————————————————————————————————————————————————" << endl
         << endl;

}/*用户注册写入文件函数*/
int regist(char username[30], char password[30]) {

    FILE *cfptr;//文件指针
    if ((cfptr = fopen("user.ini", "a+")) == nullptr) {
        printf("File client.txt could not be opened\n");
        fclose(cfptr);
        return 0;
    } else {
        fprintf(cfptr, "%s %s\n", username, password);
        fclose(cfptr);
        return 1;

    }
}/*用户名字密码检验，是否已经注册（与文件内数据比较）*/
int login(char username[30], char password[30]) {
    char user[30];
    char pass[30];
    FILE *cfptr;//文件指针
    if ((cfptr = fopen("user.ini", "r")) == nullptr) {
        printf("File client.txt could not be opened\n");
        fclose(cfptr);
        return 0;
    } else {
        while (!feof(cfptr)) {
            fscanf(cfptr, "%s%s", user, pass);
            if ((strcmp(username, user) == 0) && (strcmp(password, pass) == 0)) {
                fclose(cfptr);
                return 1;
            }
        }
    }
    fclose(cfptr);
    return 0;
}//登录
int operate(char name[30], char pass[30]) {
    func_filesystem af_filesystem;
    af_filesystem.setUser(name, pass);
    while (1) {
        system("CLS");
        while (1) {
            cout << endl;
            string choice;
            af_filesystem.showPath();
            cin >> choice;
            if (choice == "mkdir")
                af_filesystem.newDir();
            else if (choice == "touch")
                af_filesystem.newFile();
            else if (choice == "rmdir")
                af_filesystem.deleteDir();
            else if (choice == "rm")
                af_filesystem.deleteFile();
            else if (choice == "cd")
                af_filesystem.open_dir();
            else if (choice == "open")
                af_filesystem.open_file();
            else if (choice == "ls")
                af_filesystem.ls();
            else if (choice == "cp")
                af_filesystem.copyFile();
            else if (choice == "ps") {
                af_filesystem.pasteFile();
            } else if (choice == "vi")
                af_filesystem.write();
            else if (choice == "cd..")
                af_filesystem.goback();
            else if (choice == "pwd")
                af_filesystem.pwd();
            else if (choice == "clear") {
                system("CLS");
                help();
            } else if (choice == "exit") {
                system("CLS");
                cout << "用户: " << name << "正在注销"
                     << endl;
                Sleep(3);
                return 0;
            } else if (choice == "help") {
                help();
            }
            else
                cout << "命令无效！" << endl;
        }
    }

}//选择操作
