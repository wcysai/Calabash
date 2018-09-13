/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-09 13:23:49
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
ll T,n,k;
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
ll _mod(ll x) 
{
    if(x<0) return x+MOD;
    return x>=MOD?x-MOD:x;
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&k);
        ll cur=pow_mod(2,k),ans=cur;
        if(n==1) {printf("%lld\n",cur); continue;}
        if(n==2) {printf("%lld\n",_mod(cur*(cur-1)%MOD)); continue;}
        ll tmp;
        if(n%2==0) tmp=(pow_mod((cur-1)*(cur-1)%MOD,(n-1)/2)-1)*(cur-1)%MOD*pow_mod(cur,MOD-2)%MOD;
        else tmp=(pow_mod((cur-1)*(cur-1)%MOD,(n-1)/2)-1)%MOD*pow_mod(cur,MOD-2)%MOD;
        ans=_mod(ans*(pow_mod(cur-1,n-1)-tmp)%MOD);
        printf("%lld\n",ans);
    }
    return 0;
}
