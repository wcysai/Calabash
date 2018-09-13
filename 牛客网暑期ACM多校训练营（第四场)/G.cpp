/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-28 12:10:24
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
ll t,n,m,cnt[MAXN],sum[MAXN],sum2[MAXN],maxi[MAXN];
map<ll,ll> mp;
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        mp.clear();
        scanf("%lld%lld",&n,&m);
        ll x,mx=0;
        for(ll i=0;i<n;i++)
        {
            scanf("%lld",&x);
            mp[x]++;mx=max(mx,mp[x]);
        }
        for(ll i=0;i<=mx+1;i++) cnt[i]=sum[i]=sum2[i]=maxi[i]=0;
        for(auto it=mp.begin();it!=mp.end();it++)
        {
            //printf("%lld %lld\n",it->F,it->S);
            cnt[it->S]++,sum2[it->S]+=it->S,maxi[it->S]=max(maxi[it->S],it->F);
        }
        for(ll i=mx;i>=0;i--)
            sum[i]=sum[i+1]+cnt[i];
        for(ll i=mx;i>=0;i--)
            sum2[i]+=sum2[i+1];
        ll ans=-1;
        for(ll i=1;i<=mx;i++)
        {
            if(!cnt[i]) continue;
            ll needed=sum2[i]-sum[i]*(i-1)-1;
            //printf("%lld %lld\n",i,needed);
            if(needed>m) continue;
            ans=max(ans,maxi[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
