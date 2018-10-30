/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-30 17:59:13
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> P;
typedef vector<ll> vec;
ll comb[70][70];
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=s*a;
        a=a*a;
        i>>=1;
    }
    return s;
}
vec mult(vec x,vec y)
{
    vec z(64);
    for(ll i=0;i<=63;i++)
        for(ll j=0;j<=i;j++)
            z[i]+=x[j]*y[i-j];
    return z;
}
vec add(vec x,ll k)
{
    vec z(64);
    for(ll i=0;i<64;i++)
    {
        if(!x[i]) continue;
        for(ll j=0;j<=i;j++)
            z[j]+=x[i]*comb[i][j]*pow_mod(k,i-j);
    }
    return z;
}
ll n;
vec fac(ll k)
{
    vec z(64);
    if(k==1)
    {
        z[0]=1;z[1]=2;
        return z;
    }
    if(k&1)
    {
        vec x=fac(k-1);
        z[0]=2*k-1;z[1]=2;
        z=mult(z,x);
        return z;
    }
    else
    {
        vec x=fac(k>>1);
        z=mult(x,add(x,k>>1));
        return z;
    }
}
ll solve(ll n)
{
    if(n==1) return 1;
    if(n&1) return fac((n>>1)+1)[0]*solve((n+1)>>1);
    else return fac(n>>1)[0]*solve(n>>1);
}
int main()
{
    comb[0][0]=1;
    for(ll i=1;i<=64;i++)
    {
        comb[i][0]=comb[i][i]=1;
        for(ll j=1;j<i;j++) comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
    }
    scanf("%lld",&n);
    printf("%llu\n",solve(n));
    return 0;
}

