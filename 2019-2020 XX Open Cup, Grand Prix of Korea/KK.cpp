#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 250005
#define MAXLOGN 19
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
struct edge{int to,cost;};
int n;
ll ans[MAXN];
vector<P> f[MAXN];
vector<P> tmp;
struct min2
{
    P val[2];
    init() {val[0]=val[1]=P(-1,INF);}
    void add(P p)
    {
        if(p.F!=val[0].F&&p.S<val[0].S)
        {
            val[1]=val[0];
            val[0]=p;
        }
        else if(p.F!=val[1].F&&p.S<val[1].S) val[1]=p;
    }
    ll get(int x)
    {
        if(val[0].F!=-1&&val[0].F!=x) return val[0].S;
        else if(val[1].F!=-1&&val[1].F!=x) return val[1].S;
        return INF;
    }
};
min2 mini[MAXN];
struct tree
{
    vector<edge> G[MAXN];
    bool centroid[MAXN];
    int sz[MAXN];
    void add_edge(int u,int v,int cost)
    {
         G[u].push_back((edge){v,cost});
         G[v].push_back((edge){u,cost});
    }
    void read()
    {
        for(int i=0;i<n-1;i++)
        {
            int u,v,cost;
            scanf("%d%d%d",&u,&v,&cost);
            add_edge(u,v,cost);
        }
    }
    P getroot(int v,int p,int t)
    {
        P res=P(INT_MAX,-1);
        int m=0;
        sz[v]=1;
        for(int i=0;i<(int)G[v].size();i++)
        {
            int to=G[v][i].to;
            if(to==p||centroid[to]) continue;
            res=min(res,getroot(to,v,t));
            m=max(m,sz[to]);
            sz[v]+=sz[to];
        }
        m=max(m,t-sz[v]);
        res=min(res,P(m,v));
        return res;
    }
    void getdeep(int v,int p,ll d)
    {
        tmp.push_back(P(v,d));
        for(auto e:G[v])
        {
            int to=e.to,cost=e.cost;
            if(to==p||centroid[to]) continue;
            getdeep(to,v,d+cost);
        }
    }
    void solve(int v,bool save)
    {
        centroid[v]=true;
        tmp.clear();
        getdeep(v,v,0);
        if(save)
        {
            for(auto p:tmp) f[p.F].push_back(P(v,p.S));
        }
        else
        {
            for(auto p:tmp) for(auto pp:f[p.F]) mini[pp.F].init();
            for(auto p:tmp) for(auto pp:f[p.F]) mini[pp.F].add(P(p.F,p.S+pp.S));
            for(auto p:tmp) for(auto pp:f[p.F]) ans[p.F]=min(ans[p.F],p.S+pp.S+mini[pp.F].get(p.F));
        }
        for(auto e:G[v])
        {
            int to=e.to;
            if(centroid[to]) continue;
            int rt=getroot(to,v,sz[to]).S;
            solve(rt,save);
        }
    }
    void go(bool save)
    {
        int rt=getroot(1,0,n).S;
        solve(rt,save);
    }
}T1,T2;
int main()
{
    scanf("%d",&n);
    T1.read(); T2.read();
    for(int i=1;i<=n;i++) ans[i]=INF;
    T1.go(true); T2.go(false);
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}
