/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-11 12:10:50
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
ll n;
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
int main()
{
    scanf("%lld",&n);
    ll ans=24;
    ans=((ans-42*n)%MOD+MOD)%MOD;
    ans=(ans+23*pow_mod(n,2))%MOD;
    ans=((ans-6*pow_mod(n,3))%MOD+MOD)%MOD;
    ans=(ans+pow_mod(n,4))%MOD;
    ans=ans*pow_mod(24,MOD-2)%MOD;
    printf("%lld\n",ans);
    return 0;
}
