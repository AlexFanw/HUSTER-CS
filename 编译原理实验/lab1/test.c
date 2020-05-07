int a,b,c;//测试int类型
float m,n;//测试float类型
char d;//测试char类型
int al[3];//测试数组
struct S{//测试strcut类型
    int a;
    char b;
    float c;
    string d;
};
/*
*测试函数定义
*/
int fibo(int a){
    if(a==1||a==2)return 1;
    return fibo(a-1)+fibo(a-2);
}
int main(){
    int m,n,i;
    /*
    *结构体声明
    */
    struct S s;//测试声明结构体
    int i = 5;//测试int变量
    int ex[3]=[1,2,3];//数组赋值测试
    int fan[2][3]=[[1,2,3],[4,5,6]];//多维数组赋值测试
    string s = "alex fan";//string赋值测试
    char a = 'a';//char赋值测试
    s = "alex";//无标示符赋值测试
    a = 'b';//无标示符赋值测试
    ex[2]=1;//无标示符赋值测试
    m=read();
    /*
    *测试switch语句
    */
    switch(i){
        case 1:
            i++;
            i--;
            break;
        case 3:
            i+=1;
            i-=1;
            break;
        case 5:
            i*=1;
            i/=1;
            break;
        default:
            break;
    }
    /*
    *测试while语句 if语句 break语句 continue语句
    */
    while(i<=m){
        n=fibo(i);
        write(n);
        i=i+1;
        if(i = 5) break;
        if(i!=5) continue;
    }
    /*
    *测试for语句
    */
    for(a=1;a<10;a++){
        s.a=1;
        s.b = '1';
        s.c = 1.0;
        s.d = "alex fan";
    }
    return 1;
}