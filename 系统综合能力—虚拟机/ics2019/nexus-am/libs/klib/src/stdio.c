#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  char buf[1000];
  va_list ap;
  va_start(ap,fmt);
  int length=vsprintf(buf,fmt,ap);
  va_end(ap);
  int i=0;
  while(buf[i]!='\0'){
    _putc(buf[i]);
    i++;
  }
  return length;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *temp=out;
  while(*fmt!='\0'){
    if(*fmt!='%'){
      *temp++=*fmt++;
    }
    else{
      fmt++;
      switch(*fmt){
        case 's':{
          char *str=va_arg(ap,char*);
          while(*str!='\0'){
            *temp++=*str++;
          }
          break;
        }
        case 'd':{
          int n=va_arg(ap,int);
          if(n==0){
            *temp++='0';
            break;
          }
          if(n<0){
            *temp++='-';
            n=-n;
          }
          char buf[11];
          int i=0;
          while(n!=0){
            buf[i++]=n%10+'0';
            n=n/10;
          }
          for(int j=i-1;j>=0;j--){
            *temp++=buf[j];
          }
          break;
        }
        case 'x':{
          int n=va_arg(ap,int);
          if(n==0){
            *temp++='0';
            *temp++='x';
            *temp++='0';
            break;
          }
          if(n<0){
            *temp++='-';
            n=-n;
          }
          char buf[12];
          int i=0;
          while(n!=0){
            int a=n%16;
            if(a<10)
              buf[i++]=a+'0';
            else
              buf[i++]=a-10+'a';
            n=n/16;
          }
          *temp++='0';
          *temp++='x';
          for(int j=i-1;j>=0;j--){
            *temp++=buf[j];
          }
          break;
        }
      }
      fmt++;
    }
  }
  *temp='\0';
  return temp-out;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  int length=vsprintf(out,fmt,ap);
  va_end(ap);
  return length;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
