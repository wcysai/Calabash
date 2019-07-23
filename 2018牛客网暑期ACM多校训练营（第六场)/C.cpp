/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-04 12:20:22
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll T,n,m;
ll down[MAXN],inv[MAXN];
ll comb[MAXN];
int main()
{
    ll tot=0;
    scanf("%lld",&T);
    inv[1]=1;
    for(ll i=2;i<=1000000;i++)
        inv[i]=1LL*(MOD-MOD/i)*inv[MOD%i]%MOD;
    while(T--)
    {
        tot++;
        scanf("%lld%lld",&n,&m);
        printf("Case #%lld: ",tot);
        down[0]=1;comb[0]=1;
        for(ll i=1;i<=min(n,m);i++) down[i]=1LL*down[i-1]*((m+1-i)%MOD)%MOD;
        for(ll i=1;i<=min(n,m);i++) comb[i]=1LL*comb[i-1]*((n-i)%MOD)%MOD*inv[i]%MOD;
        ll ans=0;
        for(ll i=1;i<=min(n,m);i++) ans=(ans+1LL*down[i]*comb[i-1])%MOD;
        printf("%lld\n",ans);
    }
    return 0;
}
