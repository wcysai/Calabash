//
// Created by calabash_boy on 18-5-22.
//
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,p,r;
ll fact[MAXN],invf[MAXN],inv[MAXN];
int main()
{
    scanf("%I64d%I64d%I64d",&n,&p,&r);
    if(n>=2*p)
    {
        if(r!=0) puts("-1 -1"); else puts("2 1");
        return 0;
    }
    fact[0]=invf[0]=inv[1]=1;
    for(ll i=1;i<=p-1;i++)
        fact[i]=1LL*fact[i-1]*i%p;
    inv[1]=1;
    for(ll i=2;i<=p-1;i++)
        inv[i]=(p-(p/i))*inv[p%i]%p;
    /*for(ll i=1;i<=p-1;i++) printf("%I64d ",fact[i]);
    puts("");
    for(ll i=1;i<=p-1;i++) printf("%I64d ",invf[i]);
    puts("");
    for(ll i=1;i<=p-1;i++) printf("%I64d ",inv[i]);
    puts("");*/
    if(n>=p)
    {
        if(r==0)
        {
            if(p==2&&n==2) puts("-1 -1");
            else if(p==2&&n==3) puts("3 1");
            else puts("2 1");
            return 0;
        }
        ll now=1LL*fact[p-1]*fact[n-p]%p;
        if(1LL*r*inv[now]%p<p&&1LL*r*inv[now]%p!=0) printf("%I64d %I64d\n",p,1LL*r*inv[now]%p);
        else puts("-1 -1");
        return 0;
    }
    for(ll i=2;i<=n;i++)
    {
        ll now=1LL*fact[n]*inv[i]%p;
        if(1LL*inv[now]*r%p<i&&1LL*inv[now]*r%p!=0)
        {
            printf("%I64d %I64d\n",i,1LL*inv[now]*r%p);
            return 0;
        }
    }
    puts("-1 -1");
    return 0;
}
