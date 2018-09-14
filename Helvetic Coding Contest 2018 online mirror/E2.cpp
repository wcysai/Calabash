#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 500005
#define MAXK 5005
#define INF 1000000000000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
 #define ll int
ll dp[3][MAXK];
ll k,n,t[MAXN];
int main()
{
	scanf("%d%d",&k,&n);
	for(ll i=1;i<=n;i++) scanf("%d",&t[i]);
	sort(t+1,t+n+1);
	for(ll i=1;i<n;i++) t[i]=t[i+1]-t[i];
	n--;
	for(ll i=0;i<3;i++)
		for(ll j=0;j<=k;j++)
			dp[i][j]=1000000007;
	dp[0][0]=dp[1][0]=dp[2][0]=0;
	dp[1][1]=t[1];
	int tt=1;
	for(ll i=2;i<=n;i++)
	{
		tt++;
		if(tt==3) tt-=3;
		int tt1=tt-1,tt2=tt-2;
		if(tt1<0) tt1+=3;
		if(tt2<0) tt2+=3;
		for(ll j=1;j<=k;j++)
		{
			dp[tt][j]=min(dp[tt1][j],dp[tt2][j-1]+t[i]);
		}
	}
	printf("%d\n",dp[tt][k]);
	return 0;
}
