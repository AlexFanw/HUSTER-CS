# 1.poj 1000

```c++
#include <stdio.h>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d",a+b);
    return 0;
```

# 2.poj1005

```c++
#include <stdio.h> 
//#include <math.h>
//#define PI acos(-1)
int main(void){
    int nums = 0;
    int i = 0;
    scanf("%d\n",&nums);
    float a[20];
    float b[20];
    for(;i<nums;i++){
        scanf("%f %f",&a[i],&b[i]);
    }
    i = 0;
    while(nums--){
        
        float jud = (a[i]*a[i]+b[i]*b[i])*3.1415926/2;
        int year = int(jud)/50 + 1;
        printf("Property %d: This property will begin eroding in year %d.\n",i+1,year);
        i+=1;
    }
    printf("END OF OUTPUT.");
    return 0;
}
```



# 3.poj1753

```c++
#include <iostream>
using namespace std;

bool samecolor();
void flip(int i);
bool b_tree(int i);
int getTimes();
void search();

int tf[16] ;
int sq[4][4];
int times = -1;

int main(){
    char temp;
    for (int i = 0;i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> temp;
			if (temp == 'b')
				sq[i][j] = 1;
			else
				sq[i][j] = 0;
		}
	}
    
    search();
    if (times == -1)
	{
		cout << "Impossible" << endl;
	}
    else
	{
		cout << times << endl;
	}

}

void search()
{
	tf[0] = 0;
	flip(0);
	b_tree(1);

	tf[0] = 1;
	flip(0);
	b_tree(1);
}

int getTimes(){
    int curtime = 0;
    for(int i=0;i<16;i++){
        if(tf[i] == 0){
            curtime +=1;
        }
    }
    return curtime;
}

bool b_tree(int i){//i为搜索层数
    if (i == 16)
	{
		if (samecolor())
		{
			if (times == -1)
				times = getTimes();
			else
			{
				int tempTime = getTimes();
				times = tempTime < times ? tempTime:times;
			}
			return true;
		}
        else
			return true;
	}

	tf[i] = 0;
	flip(i);
	b_tree(i+1);
	tf[i] = 1;
	flip(i);
	b_tree(i+1);
    return 1;
}

void flip(int i){
    int n = i/4;
    int m = i%4;
    sq[n][m] = (sq[n][m] ==1)? 0:1;
    if (m != 0){
        sq[n][m-1] = (sq[n][m-1] ==1)? 0:1;
    }
    if (n != 0){
        sq[n-1][m] = (sq[n-1][m] == 1)? 0:1;
    }
    if (m != 3){
        sq[n][m+1] = (sq[n][m+1] ==1)? 0:1;
    }
    if (n != 3){
        sq[n+1][m] = (sq[n+1][m] == 1)? 0:1;
    }
}

bool samecolor(){
    for(int i = 0;i <= 3;i++){
        for(int j = 0;j <= 3;j++){
            if(sq[i][j] != sq[0][0]) return false;
        }
    }
    return true;
}

```

# 4.poj3295

```c++
#include <iostream>
#include <string>
using namespace std;
string wwf;  
int current;
int flag;
int taut(int i) {  
    char ch = wwf[current++];  
    if(ch=='p' || ch=='q'|| ch=='r' || ch=='s' || ch=='t'){
        return (i>>int (ch-'p'))&1;
    }  
    else if(ch=='K') return taut(i) & taut(i);  
    else if(ch=='A') return taut(i) | taut(i);  
    else if(ch=='N') return !taut(i);  
    else if(ch=='C') return (!taut(i)) | taut(i);  
    else if(ch=='E') return taut(i) == taut(i);  
    else return 0;  
}  
  
int main() {
    while(cin >> wwf && wwf[0]!='0') {  
        flag = 1;
        for(int i=0; i<32; i++) {  
            current = 0;  
            if(!taut(i)) {  
                flag = 0;  
                break; 
            } 
        }
        if(flag) cout << "tautology" << endl;  
        else cout << "not" << endl; 
    }

    return 0;  
}  
```



# 5.poj2366

```c++
#include <iostream>
using namespace std;
const int N=5e4+10;
int fir[N];
int sec[N];
int main(){
    int first,second;
    cin >> first;
    for(int i = 0;i< first ;i++){
        scanf("%d",fir+i);
    }
    cin >> second;
    for(int i = 0;i< second ;i++){
        scanf("%d",sec+i);
        sec[i] = 10000 - sec[i];
    }
    for(int i = 0;i< first;i++){
        int flag = 0;
        for(int j = flag;j< second;j++){
            if (fir[i] == sec[j]){
                cout << "YES" << endl;
                return 1;
            }
            if (sec[j] > fir[i]) {
                flag = j-1;
                break;
                }
    }
    }
    cout << "NO" << endl;
    return 1;
}
```



# 6.poj2503

```c++
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
```



# 7.poj3714

```c++
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
```



# 8.poj3233

```c++
#include <iostream>
#include <algorithm>

using namespace std;
const int max_number = 110;
const int mod = 2;
typedef long long ll;

struct matrix {
    ll a[max_number][max_number];
};

matrix que, ans;

long long n, k, m;

matrix multip( matrix x, matrix y ) {
    matrix tmp;
    for( ll i = 0; i < 2*n; i ++ ) {
        for( ll j = 0; j < 2*n; j ++ ) {
            tmp.a[i][j] = 0;
            for( ll k = 0; k < 2*n; k ++ ) {
                tmp.a[i][j] = ( tmp.a[i][j] + x.a[i][k] * y.a[k][j] ) % m;
            }
        }
    }
    return tmp;
}
void func( ll x ) {
    while(x) {
        if( x&1 ) {
            ans = multip( ans, que );
        }
        que = multip( que, que );
        x /= 2;
    }
}

int main() {
    while( cin >> n >> k >> m ) {
        memset( ans.a, 0, sizeof(ans.a) );
        memset( que.a, 0, sizeof(que.a) );
        for( ll i = 0; i < n; i ++ ) {
            for( ll j = 0; j < n; j ++ ) {
                cin >> que.a[i][j];
            }
        }
        for( ll i = n; i < 2*n; i ++ ) {
            que.a[i][i-n] = que.a[i][i] = 1;
        }
        for( ll i = 0; i < 2*n; i ++ ) {
            ans.a[i][i] = 1;
        }
        func(k+1);
        for( ll i = n; i < 2*n; i ++ ) {
            for( ll j = 0; j < n; j ++ ) {
                if( i == j+n ) {
                    ans.a[i][j] --;
                }
                if( j != n-1 ) {
                    cout << ( ans.a[i][j] + m ) % m << " ";
                } else {
                    cout << ( ans.a[i][j] + m ) % m << endl;
                }
            }
        }
    }
    return 0;
}
```

# 9:poj1723 SOLDIERS
```c++
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n, x[10001], y[10001];
    cin >> n;
    for (int i = 0; i < n; i++)
        scanf("%d%d", &x[i], &y[i]);
    sort(x, x + n);
    sort(y, y + n);
    for (int i = 0; i < n; i++)
        x[i] -= i;
    sort(x, x + n);
    int s = 0;
    for (int i = 0; i < n / 2; i++)
        s += x[n - 1 - i] - x[i] + y[n - 1 - i] - y[i];
    cout << s <<endl ;
    return 0;
}
```

# 10.poj3269 Building A New Barn
```c++
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
 
const int N = 10000;
 
struct point
{
    int x, y;
};
 
int n;
point p[N];
int x[N], y[N];
int x1, x2, y1, y2;
set<int> table;
 
inline int f(int x, int y)
{
    return (x + 10000) * 100000 + (y + 10000);
}
 
inline bool find(int x, int y)
{
    return table.find(f(x, y)) != table.end();
}
 
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", x + i, y + i);
        p[i].x = x[i];
        p[i].y = y[i];
        table.insert(f(x[i], y[i]));
    }
    sort(x, x + n);
    sort(y, y + n);
 
    int sum = 0, cnt = 0;
    if (n & 1)
    {
        x1 = x[n / 2];
        y1 = y[n / 2];
        if (find(x1, y1))
        {
            for (int i = 0; i < n; ++i)
            {
                sum += abs(x1 - x[i]);
                sum += abs(y1 - y[i]);
            }
            ++sum;
 
            x1 = x[n / 2 - 1];
            x2 = x[n / 2 + 1];
            for (int i = x1; i <= x2; ++i)
                if (!find(i, y1))
                    ++cnt;
 
            y1 = y[n / 2 - 1];
            y2 = y[n / 2 + 1];
            for (int i = y1; i <= y2; ++i)
                if (!find(x1, i))
                    ++cnt;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                sum += abs(x1 - x[i]);
                sum += abs(y1 - y[i]);
            }
            cnt = 1;
        }
    }
    else
    {
        x1 = x[n / 2 - 1];
        x2 = x[n / 2];
        y1 = y[n / 2 - 1];
        y2 = y[n / 2];
        cnt = (x2 - x1 + 1) * (y2 - y1 + 1);
        for (int i = 0; i < n; ++i)
        {
            sum += abs(x1 - x[i]);
            sum += abs(y1 - y[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            if (p[i].x >= x1 && p[i].x <= x2 && p[i].y >= y1 && p[i].y <= y2)
                --cnt;
        }
    }
    printf("%d %d\n", sum, cnt);
    return 0;
}
```

# 11.poj3579 Median
```c++
#include <iostream>
#include<algorithm>
using namespace std;

#define pi acos(-1)
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define rep(i,x,n) for(int i=x;i<n;i++)
#define per(i,n,x) for(int i=n;i>=x;i--)

typedef pair<int,int>P;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int x[100010];
int n;
long long pos;
bool check(int mid)
{
	int r = 0;
	long long sum = 0;
	for(int l = 0; l < n; l++)
	{
		while(r < n && x[r] - x[l] <= mid) r++;
		r--;
		sum += r - l;
	}
	return sum < pos; 
}
int main()
{	
	while(cin >> n)
	{
		pos = 1ll * n * (n - 1) / 2;
		if(pos & 1) pos = pos / 2 + 1;
		else pos >>= 1;
		for(int i = 0; i < n; i++)
		scanf("%d", x + i);
		sort(x, x + n);
		if(x[0] == x[n - 1])
		{
			cout << 0 << endl;
			continue;
		}
		int l = 0, r = 1e9, mid;
		while(l <= r)
		{
			mid = (r + l) >> 1;
			if(check(mid))
			l = mid + 1;
			else
			r = mid - 1;
		}
		cout << l << endl;
	}
 	return 0;
}

```

# 12.poj1050 To the Max
```c++
#include <iostream>
#define SIZE 101
 
using namespace std;
 
int a[SIZE][SIZE];
 
int MaxSubArray(int n, int* a)
{
    int max = 0;
    int b = 0;
    for (int i = 0; i < n; i++)
    {
        if (b > 0) b += a[i];
        else b = a[i];
        if (b > max) max = b;
    }
    return max;
}
 
int MaxSubMatrix(int m, int n)
{
    int i, j, k, sum;
    int max = 0;
    int b[SIZE];
    for (i = 0; i < m; i++)
    {
        for (k = 0; k < n; k++)
        {
            b[k] = 0;
        }
       

        for (j = i; j < m; j++)
        {

            for (k = 0; k < n; k++)
            {
                b[k] += a[j][k];
            }
            
            sum = MaxSubArray(k, b);
            if (sum > max)
            {
                max = sum;
            }
        }
    }
    return max;
}
 
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    cout << MaxSubMatrix(n, n) << endl;

    return 0;
}
```