//#include <stdio.h>

//int main(){
//    int a,b;
//    scanf("%d%d",&a,&b);
//    printf("%d",a+b);
//    return 0;
//}

//#include <stdio.h>
////#include <math.h>
////#define PI acos(-1)
//int main(void){
//    int nums = 0;
//    int i = 0;
//    scanf("%d\n",&nums);
//    float a[20];
//    float b[20];
//    for(;i<nums;i++){
//        scanf("%f %f",&a[i],&b[i]);
//    }
//    i = 0;
//    while(nums--){
//        
//        float jud = (a[i]*a[i]+b[i]*b[i])*3.1415926/2;
//        int year = int(jud)/50 + 1;
//        printf("Property %d: This property will begin eroding in year %d.\n",i+1,year);
//        i+=1;
//    }
//    printf("END OF OUTPUT.");
//    return 0;
//}

#include <stdio.h>
int main(){
    printf("Flip Game!");
}









//#include <stdio.h>
//char wwf[105];  
//int current;
  
//int taut(int i) {  
//    char ch = wwf[current++];  
//    if(ch=='p' || ch=='q'|| ch=='r' || ch=='s' || ch=='t') return (i>>(ch-'p'))&1;//返回该元素值  
//    else if(ch=='K') return taut(i) & taut(i);  
//    else if(ch=='A') return taut(i) | taut(i);  
//    else if(ch=='N') return  taut(i);  
//    else if(ch=='C') return ( taut(i)) | taut(i);  
//    else if(ch=='E') return taut(i) == taut(i);  
//    else return 0;  
//}  
//  
//int main() {  
//    int flag;  
//    while(scanf("%s",wwf)==1 && wwf[0]!='0') {  
//        flag = 1;         
//        for(int i=0; i<32; i++) {  
//            current = 0;  
//            if( taut(i)) {  
//                flag = 0;  
//                break;  
//            }  
//        }  
//        if(flag) printf("tautology");  
//        else printf("not");  
//    }  
//    return 0;  
//}  