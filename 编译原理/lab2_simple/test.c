int a,b,c;
float m,n;
char c1,c2;
char h[10];

float a,b;//全局变量中出现相同变量名



int fibo(int a)
{
	int i;
        int haha;
	if(a == 1 || a == 2){
	  return 1;
        }
	for(i<15){
          i++;
	}
        
        j = i+1;//无定义错误
        haha(c);//未定义的函数
        a = fibo(1,2);//参数个数不匹配
        b = fibo(m);//参数类型不匹配
	
        return fibo(a-1)+fibo(a-2);
}

int h1(int a, int a){}//出现了相同函数参数

int h2(){int hah; float hah;}//局部变量名出现了相同的变量名

float h1(){}//重复的函数名