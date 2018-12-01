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
ll N,K,a[MAXN],sum[MAXN],dp[MAXN],opt[MAXN],L[MAXN],R[MAXN],num[MAXN];
ll findcost(ll l,ll r)
{
    ll mid=(l+r)/2;
    return a[mid]*(mid*2-l-r)-sum[mid-1]+sum[l-1]+sum[r]-sum[mid];
}
P C(ll x)
{
    dp[0]=0,num[0]=0;
    L[1]=1,R[1]=N,opt[1]=0;
    ll s=1,t=1;
    for(ll i=1;i<=N;i++)
    {
        while(s+1<=t&&R[s]<i) ++s;
        dp[i]=dp[opt[s]]+findcost(opt[s]+1,i)+x;
        num[i]=num[opt[s]]+1;
        while(s<=t&&i<=L[t]&&dp[opt[t]]+findcost(opt[t]+1,L[t])>dp[i]+findcost(i+1,L[t])) --t;
        if(s>t) ++t,opt[t]=i,L[t]=i+1,R[t]=N;
        else
        {
            ll l=max(L[t],i),r=R[t],ps=r+1;
            while(l<=r)
            {
                ll mid=(l+r)/2;
                if(dp[opt[t]]+findcost(opt[t]+1,mid)>dp[i]+findcost(i+1,mid)) ps=mid,r=mid-1;
                else l=mid+1;
            }
            R[t]=ps-1;
            if(ps<=N) ++t,opt[t]=i,L[t]=ps,R[t]=N;
        }
    }
    return P(dp[N],num[N]);
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
    //printf("%lld %lld %lld\n",r,C(r).F,C(r).S);
    printf("%lld\n",C(r).F-r*K);
    return 0;
}

