#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int a[MAXN];
int cnt[16];
int dp[(1<<15)];
int solve(int mask)
{
    if(mask==0) return 0;
    if(dp[mask]!=-1) return dp[mask];
    int ans=INF;
    for(int i=0;i<15;i++)
    {
        if(!(mask&(1<<i))) continue;
        for(int j=i+1;j<15;j++)
        {
            if(!(mask&(1<<j))) continue;
            int newmask=mask^(1<<i)^(1<<j);
            int to=((i+1)^(j+1))-1;
            if(mask&(1<<to)) ans=min(ans,solve(newmask^(1<<to))+2);
            else ans=min(ans,solve(newmask^(1<<to))+1);
        }
    }
    return dp[mask]=ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);u++;v++;
        a[u]^=w;a[v]^=w;
    }
    for(int i=1;i<=n;i++) cnt[a[i]]++;
    int ans=0,mask=0;
    for(int i=1;i<=15;i++)
    {
        ans+=cnt[i]/2;
        cnt[i]&=1;
        if(cnt[i]) mask+=1<<(i-1);
    }
    memset(dp,-1,sizeof(dp));
    printf("%d\n",ans+solve(mask));
    return 0;
}

