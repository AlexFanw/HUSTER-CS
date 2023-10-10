#include <iostream>
#include <stdlib.h>
#include <time.h>

bool timer(const double & start,const double& length)//统一时钟
{
    return ((double) clock() - start) / CLK_TCK < length;
}

int passcar(int direct){//汽车通行规则
    if(direct > 10){//如果等待汽车超过十台，给的时间片最多也只能让他们通过10台，多余的继续等待
        direct -= 10;
    }
    else
        direct = 0;//如果等待的汽车数量在十台以内，则一次性全部通过
    return direct;
}

int main() {
    printf("Crossing Road control panel\n");
    int n=0,s=0,w=0,e=0;//用于计量各个路口的车的数量
    int n_new,s_new,w_new,e_new;
    const double start=clock();//初始化时钟
    while(timer(start,1000000))//共100秒的总摸你时长
    {
        system("cls");
        const double start_t=clock();
        srand((unsigned)time(NULL));
        n_new = rand() % 11;
        e_new = rand() % 11;
        w_new = rand() % 11;
        s_new = rand() % 11;//模拟每个路口新来的车辆
        printf("\n********************\n");
        printf("各路口新来车辆\n    N：%d \nW:%d     E:%d\n    S:%d \n",n_new,w_new,e_new,s_new);
        n += n_new;
        e += e_new;
        w += w_new;
        s += s_new;//加上原来路口已有的车辆，得出当前每个路口的车的数量。
        printf("--------------------\n");
        printf("各路口车辆总数量\n    N：%d \nW:%d     E:%d\n    S:%d \n",n,w,e,s);
        printf("--------------------\n");
        if((n+s)>(w+e)){
            n=passcar(n);
            s=passcar(s);
            printf("南北方向通行[√]\n东西方向阻塞[X]\n");//判断哪个方向通行，哪个方向阻塞
        }
        else{
            w=passcar(w);
            e=passcar(e);
            printf("东西方向通行[√]\n南北方向阻塞[X]\n");//判断哪个方向通行，哪个方向阻塞
        }
        printf("--------------------\n");
        printf("各路口车辆通行后剩余数量\n    N：%d \nW:%d     E:%d\n    S:%d \n",n,w,e,s);//得出通行后，每个路口剩余的车的数量
        printf("********************\n");
        while(timer(start_t,50000)){
        }//每间隔五秒刷新一次当前的路口状态
    }


    return 0;

}
