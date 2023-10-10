#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
using namespace std;
int main()
{
    map<string,string>dic;
    string s1,s2,s;
    char str[15];
    while(gets(str)&&str[0]!='\0')
    {
        s1=s2="\0";
        int i;
        for(i=0;;i++)
            if(str[i]==' ')
            {
                str[i]='\0';
                break;
            }
        s1+=str;
        s2+=str+i+1;
        dic[s2]=s1;
    }
    while(cin>>s)
    {
        if(dic[s].size())
            cout<<dic[s]<<endl;
        else
            cout<<"eh"<<endl;
    }
    return 0;
} 