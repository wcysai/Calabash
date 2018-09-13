/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-03 19:53:10
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll N,M;
ll p4[MAXN],f[MAXN],g[MAXN],comb[MAXN][MAXN];
int main()
{
    scanf("%lld%lld",&N,&M);
    p4[0]=1;
    for(ll i=1;i<=5000;i++) p4[i]=4LL*p4[i-1]%M;
    ll ans=1LL*p4[N]*(N+1)%M;
    comb[0][0]=1;
    for(ll i=1;i<=5000;i++)
    {
        comb[i][0]=comb[i][i]=1;
        for(ll j=1;j<i;j++)
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%M;
    }
    for(ll i=2;i<=N;i+=2)
    {
        for(ll j=0;j<=i;j+=2)
        {
            ll res=1LL*comb[j][j/2]*comb[(i-j)][(i-j)/2]%M*comb[i][j]%M;
            f[i]+=res;if(f[i]>=M) f[i]-=M;
        }
        g[i]=f[i];
        for(ll j=0;j<i;j+=2) 
        {
            g[i]-=1LL*f[i-j]*g[j]%M;
            if(g[i]<0) g[i]+=M;
        }
    }
    for(ll i=2;i<=N;i+=2) 
    {
        ans-=1LL*g[i]*p4[N-i]%M*(N-i+1)%M;
        if(ans<0) ans+=M;
    }
    printf("%lld\n",ans);
    return 0;
}
