/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-25 12:03:48
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
typedef pair<ll,ll> P;
ll T,n,x;
priority_queue<P> q;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        while(q.size()) q.pop();
        ll ans=0,cnt=0;
        for(ll i=1;i<=n;i++) 
        {
            scanf("%lld",&x);
            if(q.size()&&-q.top().F<x)
            {
                ans+=x+q.top().F;cnt-=q.top().S;
                q.pop();
                q.push(P(-x,0));
            }
            q.push(P(-x,-2));
        }
        printf("%lld %lld\n",ans,cnt);
    }
    return 0;
}
