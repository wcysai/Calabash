/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-20 17:56:02
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll c,n,m,t;
ll p[MAXN];
bool C(ll x)
{
    ll tt=0,cnt=0,sum=0;
    for(ll i=1;i<=n;i++)
    {
        if(p[i]<=x) 
        {
            tt+=p[i];
            sum+=p[i];
            cnt++;
            if(cnt%m==0) {tt+=sum; sum=0;}
        }
    }
    return tt>t;
}
ll solve(ll x)
{
    ll cnt=0,now=0,tt=0;
    for(ll i=1;i<=n;i++)
    {
        if(p[i]<=x)
        {
            cnt++;
            tt+=p[i];
            now+=p[i];
            if(tt>t) return cnt-1;
            if(tt>=t) return cnt;
        }
        if(cnt%m==0)
        {
            tt+=now;
            now=0;
            if(tt>=t) return cnt;
        }
    }
    return cnt;
}
int main()
{
    scanf("%lld",&c);
    while(c--)
    {
        scanf("%lld%lld%lld",&n,&m,&t);
        for(ll i=1;i<=n;i++) scanf("%lld",&p[i]);
        ll l=0,r=min(200001LL,t);
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(C(mid)) r=mid; else l=mid;
        }
        //printf("%lld %lld\n%lld %lld\n",l,solve(l),r,solve(r));
        if(r==1) printf("%lld %lld\n",solve(r),r);
        else
        {
            if(solve(l)>=solve(r)) printf("%lld %lld\n",solve(l),l);
            else printf("%lld %lld\n",solve(r),r);
        }
    }
    return 0;
}
