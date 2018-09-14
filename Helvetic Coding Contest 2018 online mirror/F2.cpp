#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,s,a[MAXN],k[MAXN],now[MAXN];
bool C(int x)
{
	int sz=s+x;
	memset(now,0,sizeof(now));
	for(int i=0;i<sz;i++)
		now[a[i]]++;
	bool f=true;
	for(int j=1;j<=m;j++) if(now[j]<k[j]) {f=false; break;}
	if(f) return true;
	for(int i=sz;i<n;i++)
	{
		now[a[i]]++;
		now[a[i-sz]]--;
		f=true;
		for(int j=1;j<=m;j++) if(now[j]<k[j]) {f=false; break;}
		if(f) return true;
	}
	return false;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	s=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&k[i]);
		s+=k[i];
	}
	memset(now,0,sizeof(now));
	for(int i=0;i<n;i++)
		now[a[i]]++;
	for(int i=1;i<=m;i++)
		if(now[i]<k[i]) {puts("-1"); return 0;}
	int lb=-1,rb=n-s;
	while(rb-lb>1)
	{
		int mid=(lb+rb)/2;
		if(C(mid)) rb=mid; else lb=mid;
	}
	printf("%d\n",rb);
	return 0;
}
