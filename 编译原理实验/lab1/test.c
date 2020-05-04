int a,b,c;
float m,n;
int fibo(int a){
    if(a==1||a==2)return 1;
    return fibo(a-1)+fibo(a-2);
}
int main(){
    int m,n,i;
    //string s = "alex fan";
    m=read();
    i=1;
    while(i<=m){
        n=fibo(i);
        write(n);
        i=i+1;
    }
    return 1;
}