#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
ll bit[MAXN+1];
int n,c[MAXN],d[MAXN];
ll ask(int i)
{
    ll s=0;
    while(i>0)
    {
        s=max(s,bit[i]);
        i-=i&-i;
    }
    return s;
}
void update(int i,ll x)
{
    while(i<=n)
    {
        bit[i]=max(bit[i],x);
        i+=i&-i;
    }
}
vector<P> hor[MAXN],ver[MAXN];
ll ans[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    for(int i=1;i<=n;i++)
    {
        if(c[i]==1) ans[i]+=d[i];
        else
        {
            if(i+c[i]-1<=n) hor[i].push_back(P(n+1-(i+c[i]-1),d[i])); 
            if(i-c[i]+1>=1) ver[i-c[i]+1].push_back(P(n+1-i,d[i])); 
        }
    }
    for(int i=1;i<=n;i++) sort(ver[i].begin(),ver[i].end());
    for(int i=1;i<=n;i++) sort(hor[i].begin(),hor[i].end(),greater<P>());
    for(int i=1;i<=n;i++)
    {
        for(auto p:hor[i-1])
        {
            ll x=p.F,y=p.S;
            ll val=ask(x); update(x,y+val);
        }
        for(auto p:ver[i])
        {
            ll x=p.F,y=p.S;
            ll val=ask(x); update(x+1,y+val);
        }
        ans[i]+=ask(n+1-i);
    }
    for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
    return 0;
}

