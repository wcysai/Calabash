/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-12 09:41:50
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
typedef pair<int,int> P;
ll n,k,a[MAXN],p[MAXN];
vector<int> vv;
struct func
{
    ll a,b,c;
    func(): a(),b(),c(){}

    func(ll st, ll v)
    {
        a=-1;b=2*st-1;c=-st*(st-1)+2*v;
    }

    ll get(ll x)
    {
        return (a*x*x+b*x+c)/2;
    }

    ll getpos(const func &A) const
    {
        ll db=b-A.b; ll dc=c-A.c;
        return min((-dc+db-1)/db,(ll)INF);
    }
};

struct CHull
{
    vector<pair<func,ll> >hull;
    ll cur;
    CHull(){}

    ll get(ll i)
    {
        if(hull.empty()) return -INF;
        while(cur+1<(int)hull.size()&&hull[cur+1].S<=i) cur++;
        return hull[cur].F.get(i);
    }

    void addfunc(ll i,ll v)
    {
        func now=func(i,v);
        while(hull.size())
        {
            ll pos=hull.back().S;
            if(pos<i||now.get(pos)<hull.back().F.get(pos)) break;
            hull.pop_back();
        }
        cur=max(0LL,min(cur,(ll)hull.size()-1));
        if(hull.empty()) hull.emplace_back(now,i);
        else if(hull.back().S<i&&now.get(i)>hull.back().F.get(i)) hull.emplace_back(now,i);
        else 
        {
            ll st=now.getpos(hull.back().F);
            if(st<INF) hull.emplace_back(now,st);
        }
    }
};

struct segtree
{
    CHull hull[(1<<22)];
    segtree(): hull() {}

    void update(ll i,ll x,ll v)
    {
       ll pos=x+(1<<20);
       while(pos>=1)
       {
           hull[pos].addfunc(i,v);
           pos/=2;
       }
    }
    
    ll query(ll k,ll l,ll r,ll x,ll y,ll i)
    {
        if(x>r||l>y) return -INF;
        if(l>=x&&r<=y) return hull[k].get(i);
        ll mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y,i),query(k*2+1,mid+1,r,x,y,i));
    }
}seg;

int main()
{
    scanf("%lld",&n);
    for(ll i=0;i<n;i++)
    {
        scanf("%lld",&a[i]);
        vv.push_back(a[i]);
    }
    sort(vv.begin(),vv.end());
    vv.erase(unique(vv.begin(),vv.end()),vv.end());
    for(ll i=0;i<n;i++) p[i]=lower_bound(vv.begin(),vv.end(),a[i])-vv.begin();
    seg.update(0,0,0);
    for(ll i=0;i<n;i++)
    {
        ll cur=seg.query(1,0,(1<<20)-1,0,p[i],i);
        //printf("%lld\n",cur);
        seg.update(i+1,p[i],cur+a[i]);
    }
    ll ans=seg.query(1,0,(1<<20)-1,0,(1<<20)-1,n);
    printf("%lld\n",ans);
    return 0;
}

