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
ll S;
int cnt[60];
int dp[60][(1<<19)];
int getmask(int mask,int cnt,int i)
{
    if(mask<cnt) return -1;
    if(((mask-cnt)>>18)&1) return -1;
    return ((mask-cnt)<<1)+(i==0?0:(S>>(i-1))&1);
}
int solve(int now,int mask)
{
    if(now==-1) return (mask==0?1:0);
    if(dp[now][mask]!=-1) return dp[now][mask];
    dp[now][mask]=0;
    if(getmask(mask,cnt[now],now)!=-1) 
        if(solve(now-1,getmask(mask,cnt[now],now))) dp[now][mask]=1;
    if(getmask(mask,n-cnt[now],now)!=-1) 
        if(solve(now-1,getmask(mask,n-cnt[now],now))) dp[now][mask]=1;
    return dp[now][mask];
}
int main()
{
    scanf("%d%lld",&n,&S);
    for(int i=1;i<=n;i++)
    {
        ll x;
        scanf("%lld",&x);
        for(int j=0;j<60;j++) cnt[j]+=(x>>j)&1;
    }
    memset(dp,-1,sizeof(dp));
    int mask=(S>>59)&1;
    if(!solve(59,mask)) {puts("-1"); return 0;}
    ll ans=0;
    for(int i=59;i>=0;i--)
    {
        if(getmask(mask,cnt[i],i)!=-1&&solve(i-1,getmask(mask,cnt[i],i))) 
        {
            mask=getmask(mask,cnt[i],i);
        }
        else
        {
            ans+=1LL<<i;
            mask=getmask(mask,n-cnt[i],i);
            assert(mask!=-1);
        }
    }
    assert(mask==0);
    printf("%lld\n",ans);
    return 0;
}
