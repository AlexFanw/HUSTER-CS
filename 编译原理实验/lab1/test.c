int a,b,c;
float m,n,l;
char a;
int fibo(int a){
    if(a==1||a==2)return 1;
    return fibo(a-1)+fibo(a-2);
}
int main(){
    int m,n,i;
    int f = 5;
    int al[3];
    int ex[3]=[1,2,3];
    int fan[2][3]=[[1,2,3],[4,5,6]];
    string s = "alex fan";
    char a = 'a';
    m=read();
    i=1;
    i++;
    i--;
    i+=1;
    i-=1;
    i*=1;
    i/=1;
    while(i<=m){
        n=fibo(i);
        write(n);
        i=i+1;
        if(i = 5) break;
        if(i!=5) continue;
    }
    return 1;
}