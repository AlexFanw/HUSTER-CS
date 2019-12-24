#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdio.h>
#include<map>
#include<string>
#include<iostream>
#include<pthread.h>
#include<QStandardItemModel>
using namespace std;


class Global
{
public:
    Global();

    static pthread_mutex_t sMutex;

    static QStandardItemModel* model;
    static QStringList tableTitleLabels;
    static QStandardItem* item;
    static int i;
};

#endif // GLOBAL_H
