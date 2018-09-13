/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-30 12:28:59
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll T,n,m,k,p,q,r,MOD,a[MAXN],add[MAXN];
P deq[MAXN],st[MAXN];
void solve()
{
    ll s=0,t=0,A=0,B=0,val=0,t1=0,cnt=0;
    for(ll i=1;i<=n;i++) add[i]=0;
    for(ll i=1;i<=n;i++)
    {
        if(i<=k) val=a[i]; else val=(1LL*p*val+1LL*q*i+r)%MOD;
        while(s<t&&deq[t-1].S<=val) t--;
        deq[t++]=P(i,val);
        while(t1>0&&st[t1-1].S<val) t1--;
        ll x=t1==0?0:st[t1-1].F;//printf("L[%lld]=%lld\n",i,x);
        if(val!=0){if(x+1<i-m+1) cnt++; else add[x+1]++;}
        if(i>=m) cnt+=add[i-m+1];
        if(val!=0) st[t1++]=P(i,val);
        if(i>=m)
        {
            //printf("%lld %lld\n",deq[s].S,cnt);
            if(deq[s].F==i-m) s++;
            A+=(i-m+1)^deq[s].S;B+=(i-m+1)^(cnt); 
            cnt--;
        }
    }
    printf("%lld %lld\n",A,B);
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&m,&k,&p,&q,&r,&MOD);
        for(ll i=1;i<=k;i++) scanf("%lld",&a[i]);
        solve();
    }
    return 0;
}
