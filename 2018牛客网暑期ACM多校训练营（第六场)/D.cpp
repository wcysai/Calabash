/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-04 12:13:09
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
ll T,n,m,k;
set<int> G[MAXN];
int main()
{
    scanf("%lld",&T);
    ll tot=0;
    while(T--)
    {
        tot++;
        scanf("%lld%lld%lld",&n,&m,&k);
        for(ll i=0;i<=m;i++) G[i].clear();
        for(ll i=0;i<k;i++)
        {
            ll u,v,w;
            scanf("%lld%lld%lld",&u,&v,&w);
            G[v].insert(w);
        }
        ll ans=0;
        for(ll i=1;i<=m;i++)
        {
            if(G[i].size())
            {
                auto it=G[i].end();it--;
                ans+=*it;
            }
        }
        printf("Case #%lld: %lld\n",tot,ans);
    }
    return 0;
}
