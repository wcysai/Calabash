/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-16 12:38:52
 ************************************************************************/
  
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,q;
const int blocks=3000;
int a[41][MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int _mod(int x,int y) {x+=y; return x>=MOD?x-MOD:x;}
int fact[MAXN],invf[MAXN];
unordered_map<int,int> mp;
void build()
{
    for(auto it:mp)
        a[0][it.F]=_mod(a[0][it.F],it.S);
    for(int i=1;i<=k;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=_mod(a[i-1][j],a[i][j-1]);
    mp.clear();
}
int solve(int x,int y)
{
    if(y<x) return 0;
    return 1LL*fact[y+k-1-x]*invf[k-1]%MOD*invf[y-x]%MOD;
}
int query(int x)
{
    int ans=a[k][x];
    for(auto it:mp)
    {
        if(it.F>x) continue;
        int res=1LL*it.S*solve(it.F,x)%MOD;
        ans=_mod(ans,res);
    }
    return ans;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=100200;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100200]=pow_mod(fact[100200],MOD-2);
    for(int i=100199;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d%d",&n,&q,&k);
    int t,x,v;
    for(int i=1;i<=q;i++)
    {
        scanf("%d",&t);
        if(t==0)
        {
            scanf("%d%d",&x,&v);
            mp[x]+=v;
            if(mp[x]>=MOD) mp[x]-=MOD;
        }
        else
        {
            scanf("%d",&x);
            printf("%d\n",query(x));
        }
        if(i%blocks==0) build();
    }
    return 0;
}
