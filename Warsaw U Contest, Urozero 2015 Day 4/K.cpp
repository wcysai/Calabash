/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-16 09:11:57
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000000000000LL 
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll n,s,a[MAXN],dp[MAXN];
//dp[i]=max(dp[j]-j-1,a[i]-i)+2i-j-1+2s
int main()
{
    scanf("%lld%lld",&n,&s);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(ll i=2;i<=n;i++) a[i]=max(a[i],a[i-1]+1);
    dp[0]=0;
    ll cur=0;
    for(ll i=1;i<=n;i++)
    {
        dp[i]=INF;
        while(cur<i&&max(dp[cur]-cur-1,a[i]-i)+2*i-cur-1+2*s<dp[i])
        {
            dp[i]=max(dp[cur]-cur-1,a[i]-i)+2*i-cur-1+2*s;
            cur++;
        }
        cur--;
    }
    printf("%lld\n",dp[n]);
    return 0;
}

