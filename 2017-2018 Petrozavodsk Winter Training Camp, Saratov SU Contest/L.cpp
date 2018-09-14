#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
struct edge
{
    ll to,cost;
};
vector<edge> M[MAXN];
vector<ll> G[MAXN],rG[MAXN],dt[MAXN],bucket[MAXN];
ll d[MAXN],sdom[MAXN],idom[MAXN],arr[MAXN],rev[MAXN],par[MAXN],dsu[MAXN],label[MAXN];
ll E[MAXN][3],ans[MAXN],sz[MAXN];
ll n,m,t;
ll find(ll u,ll x=0)
{
    if(u==dsu[u]) return x?-1:u;
    ll v=find(dsu[u],x+1);
    if(v<0) return u;
    if(sdom[label[dsu[u]]]<sdom[label[u]])
        label[u]=label[dsu[u]];
    dsu[u]=v;
    return x?v:label[u];
}
void unite(ll u,ll v)
{
    dsu[v]=u;
}
void dfs(ll v)
{
    t++;arr[v]=t;rev[t]=v;
    for(ll i=0;i<G[v].size();i++)
    {
        ll to=G[v][i];
        if(!arr[to]) dfs(to),par[arr[to]]=arr[v];
        rG[arr[to]].push_back(arr[v]);
    }
}
void dijkstra(ll s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d+1,d+n+1,INF);
    d[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top();que.pop();
        ll v=p.S;
        if(d[v]<p.F) continue;
        for(ll i=0;i<M[v].size();i++)
        {
            edge e=M[v][i];
            if(d[e.to]>d[v]+e.cost)
            {
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}
void dfs2(ll v,ll p)
{
    ll res=v>n?0:1;
    for(ll i=0;i<dt[v].size();i++)
    {
        if(dt[v][i]==p) continue;
        dfs2(dt[v][i],v);
        res+=sz[dt[v][i]];
    }
    sz[v]=res;
    for(ll i=0;i<dt[v].size();i++)
    {
        if(dt[v][i]==p) continue;
        if(v>n) ans[v-n]=res;
    }
}
int main()
{
    scanf("%I64d%I64d",&n,&m);
    for(ll i=1;i<=m;i++)
    {
        scanf("%I64d%I64d%I64d",&E[i][0],&E[i][1],&E[i][2]);
        M[E[i][0]].push_back((edge){E[i][1],E[i][2]});M[E[i][1]].push_back((edge){E[i][0],E[i][2]});
    }
    dijkstra(1);
    for(ll i=1;i<=m;i++)
    {
        if(d[E[i][0]]+E[i][2]==d[E[i][1]]) {G[E[i][0]].push_back(n+i); G[n+i].push_back(E[i][1]);}
        if(d[E[i][1]]+E[i][2]==d[E[i][0]]) {G[E[i][1]].push_back(n+i); G[n+i].push_back(E[i][0]);}
    }
    for(ll i=1;i<=n+m;i++)
        sdom[i]=i,idom[i]=0,label[i]=i,dsu[i]=i,arr[i]=0,rev[i]=0;
    t=0;dfs(1);
    for(ll i=t;i>=1;i--)
    {
        for(ll j=0;j<rG[i].size();j++)
            sdom[i]=min(sdom[i],sdom[find(rG[i][j])]);
        if(i>1) bucket[sdom[i]].push_back(i);
        for(ll j=0;j<bucket[i].size();j++)
        {
            ll w=bucket[i][j],v=find(w);
            if(sdom[v]==sdom[w]) idom[w]=sdom[w];
            else idom[w]=v;
        }
        if(i>1) unite(par[i],i);
    }
    for(ll i=2;i<=t;i++)
    {
        if(idom[i]!=sdom[i]) idom[i]=idom[idom[i]];
        dt[rev[idom[i]]].push_back(rev[i]);
        //printf("%lld %lld\n",rev[i],rev[idom[i]]);
    }
    memset(ans,0,sizeof(ans));
    dfs2(1,-1);
    for(ll i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
