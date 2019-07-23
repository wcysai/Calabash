#include<bits/stdc++.h>
#define MAXN 200005
#define INF 10000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
struct node
{
    ll x,y,cost;
};
bool cmp(node p,node q)
{
    if(p.x!=q.x) return p.x<q.x;
    return p.y>q.y;
}
vector<ll> disx,disy;
vector<node> v;
ll n;
struct segtree
{
    ll maxi[4*MAXN],lazy[4*MAXN];
    void pushup(ll k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void pushdown(ll k)
    {
        if(!lazy[k]) return;
        for(ll i=k*2;i<=k*2+1;i++)
        {
            lazy[i]+=lazy[k];
            maxi[i]+=lazy[k];
        }
        lazy[k]=0;
    }
    void build(ll k,ll l,ll r)
    {
        lazy[k]=0;
        if(l==r)
        {
            maxi[k]=0;
            return;
        }
        ll mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(ll k,ll l,ll r,ll x,ll y,ll v)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            lazy[k]+=v;
            maxi[k]+=v;
            return;
        }
        pushdown(k);
        ll mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    ll query(ll k,ll l,ll r,ll x,ll y)
    {
        if(l>y||x>r) return -INF;
        if(l>=x&&r<=y) return maxi[k];
        pushdown(k);
        ll mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
int main()
{
    while(scanf("%lld",&n)==1)
    {
        ll ans=0;
        v.clear(); disx.clear(); disy.clear();
        for(ll i=0;i<n;i++)
        {
            ll x,y,a,b;
            scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
            ans+=b;
            v.push_back((node){x,y,a-b});
            disx.push_back(x); disy.push_back(y);
        }
        sort(disx.begin(),disx.end());
        disx.erase(unique(disx.begin(),disx.end()),disx.end());
        sort(disy.begin(),disy.end());
        disy.erase(unique(disy.begin(),disy.end()),disy.end());
        for(auto &p:v)
        {
            p.x=lower_bound(disx.begin(),disx.end(),p.x)-disx.begin()+2;
            p.y=lower_bound(disy.begin(),disy.end(),p.y)-disy.begin()+2;
        }
        sort(v.begin(),v.end(),cmp);
        ll sz=(int)disy.size()+1;
        seg.build(1,1,sz);
        for(auto p:v)
        {
            ll y=p.y;
            ll v=seg.query(1,1,sz,1,y),val=seg.query(1,1,sz,y,y);
            seg.update(1,1,sz,1,y-1,p.cost); seg.update(1,1,sz,y,y,v-val);
        }
        printf("%lld\n",max(0LL,seg.query(1,1,sz,1,sz))+ans);
    }
    return 0;
}
