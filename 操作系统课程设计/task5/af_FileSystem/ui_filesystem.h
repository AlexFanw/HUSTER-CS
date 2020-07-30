//
// Created by AlexFan on 2020/3/2.
//

#ifndef AF_FILESYSTEM_UI_FILESYSTEM_H
#define AF_FILESYSTEM_UI_FILESYSTEM_H

void start();
void help();
int regist(char username[30], char password[30]);
int login(char username[30], char password[30]);
int operate(char name[30], char pass[30]);

#endif //AF_FILESYSTEM_UI_FILESYSTEM_H
