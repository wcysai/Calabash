/*************************************************************************
    > File Name: cdq.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-16 17:51:51
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll n,tot,t,now;
P a[MAXN];
ll dp[MAXN];
P st[MAXN];
ll get(P u,P v) {return (v.S-u.S)/(u.F-v.F);}
void add(ll u,ll v)
{
    P p=P(u,v);
    while(t-now>1&&get(st[t-1],p)<=get(st[t-1],st[t-2])) t--;
    st[t++]=p;
}
bool cmp(P x,P y)
{
    if(x.S!=y.S) return x.S<y.S;
    return x.F<y.F;
}
ll query(ll x)
{
    ll l=-1,r=t-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[mid].F*x+st[mid].S<=st[mid+1].F*x+st[mid+1].S) l=mid;
        else r=mid;
    }
    return st[r].F*x+st[r].S;
}
void solve(ll l,ll r)
{
    if(l==r)
    {
        dp[a[l].F]=max(dp[a[l].F],a[l].S*2-(a[l].F)*(a[l].F-1));
        return;
    }
    ll mid=(l+r)/2;
    solve(l,mid);
    sort(a+l,a+mid+1);sort(a+mid+1,a+r+1);
    t=0;now=0;
    ll p1=l,p2=mid+1;
    while(p1<=mid||p2<=r)
    {
        if(p1<=mid&&(p2>r||a[p1].F<=a[p2].F))
        {
            add(2*a[p1].F,-a[p1].F-a[p1].F*a[p1].F+dp[a[p1].F]);
            p1++;
        }
        else
        {
            dp[a[p2].F]=max(dp[a[p2].F],query(a[p2].F)-a[p2].F*a[p2].F+a[p2].F+2*a[p2].S);
            p2++;
        }
    }
    sort(a+mid+1,a+r+1,cmp);
    solve(mid+1,r);
}
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) 
    {
        scanf("%lld",&a[i].S);
        a[i].F=i;
    }
    sort(a+1,a+n+1,cmp);
    for(ll i=1;i<=n;i++) dp[i]=-INF;
    solve(1,n);
    ll ans=-INF;
    for(ll i=0;i<=n;i++) ans=max(ans,dp[i]-(n-i)*(n-i+1));
    printf("%lld\n",ans/2);
    return 0;
}

