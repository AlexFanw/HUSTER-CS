#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  int i=0;
  while(s[i]!='\0')
    i++;
  return i;
}

char *strcpy(char* dst,const char* src) {
  int i=0;
  while(src[i]!='\0'){
    dst[i]=src[i];
    i++;
  }
  dst[i]='\0';
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
  int i=0;
  while(src[i]!='\0'&&i<n){
    dst[i]=src[i];
    i++;
  }
  while(i<n){
    dst[i]='\0';
    i++;
  }
  return dst;
}

char* strcat(char* dst, const char* src) {
  int i=0;
  while(dst[i]!='\0')
    i++;
  int j=0;
  while(src[j]!='\0'){
    dst[i+j]=src[j];
    j++;
  }
  dst[i+j]='\0';
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  int i=0;
  while(s1[i]!='\0'&&s1[i]==s2[i])
    i++;
  return s1[i]-s2[i];
}

int strncmp(const char* s1, const char* s2, size_t n) {
  int i=0;
  while(s1[i]!='\0'&&i<n&&s1[i]==s2[i])
    i++;
  if(i==n)
    return 0;
  return s1[i]-s2[i];
}

void* memset(void* v,int c,size_t n) {
  char *temp=v;
  for(int i=0;i<n;i++){
    temp[i]=(char)c;
  }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  char *temp=out;
  for(int i=0;i<n;i++){
    temp[i]=((char*)in)[i];
  }
  return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  char *temp1=s1;
  char *temp2=s2;
  for(int i=0;i<n;i++){
    if(temp1[i]!=temp2[i])
      return temp1[i]-temp2[i];
  }
  return 0;
}
#endif
