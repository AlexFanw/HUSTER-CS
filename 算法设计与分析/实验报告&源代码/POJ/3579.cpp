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