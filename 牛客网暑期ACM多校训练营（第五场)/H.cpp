/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-02 14:23:49
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
ll n,k,a[MAXN],dp[MAXN];
ll _add(ll a,ll b)
{
    if(a<=INF+1-b) return a+b;
    return INF+1;
}
struct segtree
{
    ll val[4*MAXN];
    void build1(ll k,ll l,ll r)
    {
        val[k]=0;
        if(l==r) return;
        ll mid=(l+r)/2;
        build1(k*2,l,mid);build1(k*2+1,mid+1,r);
    }
    void build2(ll k,ll l,ll r)
    {
        if(l==r)
        {
            val[k]=dp[l]; return;
        }
        ll mid=(l+r)/2;
        build2(k*2,l,mid);build2(k*2+1,mid+1,r);
        val[k]=_add(val[k*2],val[k*2+1]);
    }
    void update1(ll k,ll l,ll r,ll pos,ll x)
    {
        if(l==r)
        {
            val[k]=_add(val[k],x);
            return;
        }
        ll mid=(l+r)/2;
        if(pos<=mid) update1(k*2,l,mid,pos,x);
        else update1(k*2+1,mid+1,r,pos,x);
        val[k]=_add(val[k*2],val[k*2+1]);
    }
    void update2(ll k,ll l,ll r,ll pos,ll x)
    {
        if(l==r)
        {
            val[k]=x;
            return;
        }
        ll mid=(l+r)/2;
        if(pos<=mid) update2(k*2,l,mid,pos,x);
        else update2(k*2+1,mid+1,r,pos,x);
        val[k]=_add(val[k*2],val[k*2+1]);
    }
    ll query(ll k,ll l,ll r,ll x,ll y)
    {
        if(x>r||l>y) return 0;
        if(l>=x&&r<=y) return val[k];
        ll mid=(l+r)/2;
        ll lval=query(k*2,l,mid,x,y);
        ll rval=query(k*2+1,mid+1,r,x,y);
        return _add(lval,rval);
    }
    ll qpos(ll k,ll l,ll r,ll v)
    {
        if(l==r) return l;
        ll mid=(l+r)/2;
        if(val[k*2]>=v) return qpos(k*2,l,mid,v);
        else return qpos(k*2+1,mid+1,r,v-val[k*2]);
    }
}seg;
int main()
{
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    vector<ll> v;
    for(ll i=1;i<=n;i++) v.push_back(a[i]);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    seg.build1(1,1,n);
    for(ll i=n;i>=1;i--)
    {
        ll pos=lower_bound(v.begin(),v.end(),a[i])-v.begin();
        dp[i]=seg.query(1,1,n,pos+2,n);
        dp[i]=_add(dp[i],1);
        seg.update1(1,1,n,pos+1,dp[i]);
    }
    seg.build2(1,1,n);
    vector<ll> ans;
    ll now=1,nowval=0;
    set<P> s;
    for(ll i=1;i<=n;i++) s.insert(P(a[i],i));
    if(seg.query(1,1,n,1,n)<k) {puts("-1"); return 0;}
    while(k>0&&now<=n)
    {
        ll pos=seg.qpos(1,1,n,k);
        ans.push_back(pos);
        k-=seg.query(1,1,n,1,pos-1)+1;
        assert(k>=0);
        for(ll i=now;i<=pos;i++)
        {
            if(s.count(P(a[i],i)))
            {
                s.erase(P(a[i],i));
                seg.update2(1,1,n,i,0);
            }
        }
        nowval=a[pos];now=pos+1;
        while(s.size()&&s.begin()->F<=nowval)
        {
            seg.update2(1,1,n,s.begin()->S,0);
            s.erase(s.begin());
        }
    }
    printf("%lld\n",(ll)ans.size());
    for(ll i=0;i<(int)ans.size();i++)
        if(i==(int)ans.size()-1) printf("%lld\n",ans[i]); else printf("%lld ",ans[i]);
    return 0;
}
