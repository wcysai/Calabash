#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN],k[MAXN],now[MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int s=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&k[i]);
		s+=k[i];
	}
	for(int i=0;i<s;i++)
		now[a[i]]++;
	bool f=true;
	for(int j=1;j<=m;j++) if(now[j]!=k[j]) {f=false; break;}
	if(f) {puts("YES"); return 0;}
	for(int i=s;i<n;i++)
	{
		now[a[i]]++;
		now[a[i-s]]--;
		f=true;
		for(int j=1;j<=m;j++) if(now[j]!=k[j]) {f=false; break;}
		if(f) {puts("YES"); return 0;}
	}
	puts("NO");
	return 0;
}
