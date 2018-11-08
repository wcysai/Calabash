/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-08 17:57:42
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
struct edge{ll to,cost;};
ll N,K,L,tot;
vector<edge> G[MAXN];
bool centroid[MAXN];
ll sz[MAXN],d[MAXN],cnt[MAXN],cnt2[MAXN];
P deep[MAXN];
ll fact[MAXN],invf[MAXN];
ll dep[MAXN];
ll st[MAXN],ed[MAXN],flen[MAXN];
vector<ll> v;
struct q{ll v,l,r,flag;};
vector<q> query[MAXN];
ll upd[MAXN];
ll bit[10*MAXN+1];
void Add(ll &a,ll b) {a+=b; if(a>=MOD) a-=MOD; if(a<0) a+=MOD;}
ll sum(ll i)
{   
    ll s=0;
    while(i>0)
    {
        Add(s,bit[i]);
        i-=i&-i;
    }
    return s;
}
void add(ll i,ll x)
{
    while(i<=10*MAXN)
    {
        Add(bit[i],x);
        i+=i&-i;
    }
}
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
ll comb(ll n,ll k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
P getroot(ll v,ll p,ll t)//search_centroid
{
    P res=P(INT_MAX,-1);
	ll m=0;
    sz[v]=1;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to;
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void getdeep(ll v,ll p)//enumerate path
{
    deep[++deep[0].F].F=d[v];deep[deep[0].F].S=v;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to;
        if(to==p||centroid[to]) continue;
        d[to]=d[v]+G[v][i].cost;
        getdeep(to,v);
    }
}
void cal(ll v,ll cost,ll flag)
{
    d[v]=cost;deep[0].F=0;
    getdeep(v,0);
    sort(deep+1,deep+deep[0].F+1);
    ll r=deep[0].F;
    for(ll l=1;l<=deep[0].F;l++)
    {
        while(r>=1&&deep[l].F+deep[r].F>L) r--;
        cnt[deep[l].S]+=r*flag;
    }
}
void solve(ll v)
{
    cal(v,0,1);
    centroid[v]=true;
    for(ll i=0;i<(int)G[v].size();i++)
    {
        ll to=G[v][i].to,cost=G[v][i].cost;
        if(centroid[to]) continue;
        cal(to,cost,-1);
        ll rt=getroot(to,v,sz[to]).S;
        solve(rt);
    }
}
void ac()
{
    ll rt=getroot(1,0,N).S;
    solve(rt);
}
void dfs(ll v,ll p,ll d,ll f)
{
    dep[v]=d;st[v]=++tot;flen[v]=f;
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        dfs(e.to,v,d+e.cost,e.cost);
    }
    ed[v]=tot;
}
int main()
{
    fact[0]=invf[0]=1;
    for(ll i=1;i<=100000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100000]=pow_mod(fact[100000],MOD-2);
    for(ll i=99999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%lld%lld%lld",&N,&K,&L);
    for(ll i=0;i<N-1;i++)
    {
        ll x,y,z;
        scanf("%lld%lld%lld",&x,&y,&z);
        G[x].push_back((edge){y,z});
        G[y].push_back((edge){x,z});
    }
    memset(centroid,false,sizeof(centroid));
    memset(cnt,0,sizeof(cnt));
    ac();
    tot=0;dfs(1,0,0,0);
    for(ll i=1;i<=N;i++) {upd[st[i]]=dep[i]; v.push_back(dep[i]);}
    for(ll i=1;i<=N;i++) 
    {
        query[st[i]-1].push_back((q){i,dep[i]+L-flen[i],dep[i]+L,-1});
        query[ed[i]].push_back((q){i,dep[i]+L-flen[i],dep[i]+L,1});
        v.push_back(dep[i]+L-flen[i]);v.push_back(dep[i]+L);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    memset(bit,0,sizeof(bit));memset(cnt2,0,sizeof(cnt2));
    for(ll i=1;i<=N;i++)
    {
        ll x=lower_bound(v.begin(),v.end(),upd[i])-v.begin()+1;
        add(x,1);
        for(auto it:query[i])
        {
            ll l=lower_bound(v.begin(),v.end(),it.l)-v.begin()+1;
            ll r=lower_bound(v.begin(),v.end(),it.r)-v.begin()+1;
            cnt2[it.v]+=it.flag*(sum(r)-sum(l));
        }
    }
    ll ans=0;
    for(ll i=1;i<=N;i++)
    {
        if(i==1) Add(ans,comb(cnt[i],K));
        else 
        {
            assert(cnt[i]>=cnt2[i]);
            Add(ans,comb(cnt[i],K));
            Add(ans,-comb(cnt[i]-cnt2[i],K));
        }
    }
    ans=1LL*ans*fact[K]%MOD;
    printf("%lld\n",ans);
    return 0;
}
