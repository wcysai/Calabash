/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-04 19:15:48
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
ll n,k;
ll dp[70],ans[70],cnt[70];
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a;
        a=1LL*a*a;
        i>>=1;
    }
    return s;
}
ll solve()
{
    cnt[0]=0;
    for(ll i=1;i<=n;i++) 
    {
        cnt[i]=cnt[i-1];
        if(ans[i]==2) cnt[i]++;
    }
    for(ll i=1;i<=n;i++)
    {
        ll now=pow_mod(2,cnt[i]);
        for(ll j=1;j*2<=i;j++)
        {
            bool f=true;
            for(ll k=1;k<=j;k++) if(ans[k]!=2&&ans[i-j+k]!=2&&ans[k]!=ans[i-j+k]) {f=false; break;}
            if(f) now-=dp[j]*pow_mod(2,cnt[i-j]-cnt[j]);
        }
        dp[i]=now;
    }
    return dp[n];
}
int main()
{
    freopen("borderless.in","r",stdin);
    freopen("borderless.out","w",stdout);
    while(scanf("%llu%llu",&n,&k)==2)
    {
        if(!n&&!k) break;
        for(ll i=1;i<=n;i++) ans[i]=2;
        for(ll i=1;i<=n;i++)
        {
            ans[i]=0;
            ll cur=solve();
            if(cur<k) 
            {
                ans[i]=1;
                k-=cur;
            }
        }
        assert(k==1);
        for(ll i=1;i<=n;i++) if(ans[i]==0) printf("a"); else printf("b");
        puts("");
    }
    return 0;
}

