#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll n;
ll a[MAXN],b[MAXN];
vector<P> v;
vector<ll> vv;
struct segtree
{
    ll sum[MAXN*4];
    ll cnt[4*MAXN];
    void pushup(ll k)
    {
        cnt[k]=cnt[k*2]+cnt[k*2+1];
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void add(ll k,ll l,ll r,ll p)
    {
        if(l==r)
        {
            cnt[k]++;
            sum[k]+=vv[l];
            return;
        }
        ll mid=(l+r)/2;
        if(p<=mid) add(k*2,l,mid,p); else add(k*2+1,mid+1,r,p);
        pushup(k);
    }
    ll query(ll k,ll l,ll r,ll s)
    {
        if(l==r) return (s-1)/vv[l]+1;
        ll mid=(l+r)/2;
        if(sum[k*2+1]>=s) return query(k*2+1,mid+1,r,s); 
        else return query(k*2,l,mid,s-sum[k*2+1])+cnt[k*2+1]; 
    }
}seg;
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) 
    {
        scanf("%lld%lld",&a[i],&b[i]);
        v.push_back(P(a[i]+b[i],a[i]));
        vv.push_back(a[i]);
    }
    sort(vv.begin(),vv.end());
    vv.erase(unique(vv.begin(),vv.end()),vv.end());
    ll sz=(ll)vv.size();
    sort(v.begin(),v.end());
    ll now=0,ans=INF;
    ll sum;
    while(now<(ll)v.size())
    {
        sum=v[now].F;
        ll pos=lower_bound(vv.begin(),vv.end(),v[now].S)-vv.begin();
        seg.add(1,0,sz-1,pos);
        while(now+1<(ll)v.size()&&v[now+1].F==sum)
        {
            now++;
            pos=lower_bound(vv.begin(),vv.end(),v[now].S)-vv.begin();
            seg.add(1,0,sz-1,pos);
        }
        if(seg.sum[1]>=sum) ans=min(ans,seg.query(1,0,sz-1,sum));
        now++;
    }
    if(ans==INF) puts("-1"); else printf("%lld\n",ans);
    return 0;
}
