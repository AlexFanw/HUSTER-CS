#include<iostream>
#include<cstring>
#include<algorithm>
#include<math.h>
#include<functional>
using namespace std;

const int maxn=200020;

int T;
double x, y;

struct sit{
	double x, y;
	int mark;
};

sit p[maxn];

bool compare(sit a,sit b){
	return a.x<b.x;
}

double dis(sit a, sit b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double mindis(int l,int r,int n){
	if(l>=r) return 1e10;
	if(r==l+1){
		if(p[l].mark==p[r].mark){
			return 1e10;
		}else return dis(p[l], p[r]);
	}//
	int mid=(l+r)/2;//取中点
	double d1=mindis(l, mid, n);
	double d2=mindis(mid+1, r, n);
    double d=min(d1,d2);
	for(int i=l; i<=r; i++){
		if(p[i].mark!=p[mid].mark)//如果两点不属于同一阵容则返回
		d=min(d, dis(p[mid], p[i]));
	}
	return d;
}

int main()
{
	cin >> T;
	while(T--){
		int n;
        cin >> n;
		for(int i=0;i<n;i++){
			cin >> x >> y;
			p[i].x=x;
            p[i].y=y;
            p[i].mark=0;//录入坐标
		}// 发电站
		for(int i=n;i<2*n;i++){
			cin >> x >> y;
			p[i].x=x;
            p[i].y=y;
            p[i].mark=1;//录入坐标
		}// 士兵
		sort(p,p+2*n,compare);//按照从小到大排序
    	double  res=mindis(0,2*n-1,2*n);
		printf("%.3f\n",res);
	}
	return 0;
}