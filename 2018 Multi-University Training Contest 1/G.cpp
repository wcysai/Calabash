/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-23 13:00:55
 ************************************************************************/

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
ll t,n;
ll cnt(ll x)
{
    if(x==0) return 0;
    return x+cnt(x/2);
}
ll find_ans(ll x)
{
    if(x==0) return 0;
    ll p,res;
    if(x>=MOD) p=x%MOD; else p=x;
    res=p*(p+1)/2;
    return (res+2LL*find_ans(x/2))%MOD;
}
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        ll l=0,r=(ll)1e18;
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(cnt(mid)<=n-1) l=mid; else r=mid;
        }
        //printf("%lld\n",l);
        ll exd=(n-cnt(l)-1)%MOD;
        printf("%lld\n",(find_ans(l)+1LL+exd*(r%MOD))%MOD);
    }
    return 0;
}
