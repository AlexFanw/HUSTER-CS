#ifndef CONFIG_H
#define CONFIG_H

#include<QString>
class Config
{
public:
    Config();
    static int port;
    static char * ip;\
    static QString tableOfFiles;
};

#endif // CONFIG_H
