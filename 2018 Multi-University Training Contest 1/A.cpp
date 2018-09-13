/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-23 12:05:24
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll t,ans[MAXN];
ll solve2(ll x)
{
    if(x&1) return -1;
    else return x*x/4;
}
ll solve3(ll x)
{
    ll ans=-1;
    if(x%2!=0&&x%3!=0) return -1;
    if(x%2==0)
    {
        if(solve2(x/2)!=-1) ans=max(ans,x/2*solve2(x/2));
    }
    if(x%3==0)
    {
        if(solve2(x*2/3)!=-1) ans=max(ans,x/3*solve2(x*2/3));
    }
    return ans;
}
int main()
{
    for(ll i=1;i<=1000000;i++) ans[i]=solve3(i);
    scanf("%lld",&t);
    while(t--)
    {
        ll x;
        scanf("%lld",&x);
        printf("%lld\n",ans[x]);
    }
    return 0;
}
