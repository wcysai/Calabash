/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-01 10:37:51
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll N,K,a[MAXN],sum[MAXN],dp[MAXN],opt[MAXN],cnt[MAXN];
ll findcost(ll l,ll r,ll x)
{
    ll mid=(l+r)/2;
    return a[mid]*(mid*2-l-r)-sum[mid-1]+sum[l-1]+sum[r]-sum[mid]+x;
}
P C(ll x)
{
    fill(dp,dp+N+1,INF);memset(cnt,0,sizeof(cnt));
    dp[0]=0,opt[0]=1;
    vector<P> v;v.clear();
    v.push_back(P(1,1));
    for(ll i=1;i<=N;i++)
    {
        ll l=opt[i-1]-1,r=i;
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(dp[mid-1]+findcost(mid,i,x)<=dp[mid]+findcost(mid+1,i,x)) r=mid; else l=mid;
        }
        opt[i]=r;dp[i]=dp[opt[i]-1]+findcost(opt[i],i,x);cnt[i]=cnt[opt[i]-1]+1;
        if(x==55)printf("%lld %lld %lld\n",i,opt[i],dp[i]);
    }
    return P(dp[N],cnt[N]);
}
int main()
{
    scanf("%lld%lld",&N,&K);
    for(ll i=1;i<=N;i++) scanf("%lld",&a[i]);
    for(ll i=1;i<=N;i++) sum[i]=sum[i-1]+a[i];
    ll l=0,r=sum[N]+1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(C(mid).S>K) l=mid; else r=mid;
    }
    //printf("%lld %lld\n",C(INF).F,C(INF).S);
    printf("%lld %lld %lld\n",l,C(l).F,C(l).S);
    printf("%lld\n",C(r).F-r*K);
    return 0;
}

