#include<bits/stdc++.h>
#define MAXN 250005
#define MAXLOGN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
int n,q,val[MAXN];
int pa[MAXLOGN][MAXN];
int depth[MAXN];
P res[MAXLOGN][MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
void dfs(int v,int p,int d)
{
    depth[v]=d;
    pa[0][v]=p;
    res[0][v]=P(val[v],1);
    for(auto to:G[v])
        if(to!=p) dfs(to,v,d+1);
}
P merge(P x,P y)
{
    if(x.F==y.F) return P(x.F,x.S+y.S);
    else if(x.S>=y.S) return P(x.F,x.S-y.S);
    else return P(y.F,y.S-x.S);
}
void init(int V)
{
    dfs(1,0,0);
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<0)
            {
                pa[k+1][v]=-1;
                res[k+1][v]=res[k][v];
            }
            else
            {
                pa[k+1][v]=pa[k][pa[k][v]];
                res[k+1][v]=merge(res[k][v],res[k][pa[k][v]]);
            }
        }
    }
}
pair<int,P> get_ans(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    P ans=P(1,0);
    int d=depth[v]-depth[u];
    for(int k=0;k<MAXLOGN;k++)
    {
        if((d>>k)&1)
        {
            ans=merge(ans,res[k][v]);
            v=pa[k][v];
        }
    }
    if(u==v) return make_pair(u,merge(ans,res[0][v]));
    for(int k=MAXLOGN-1;k>=0;k--)
    {
        if(pa[k][u]!=pa[k][v])
        {
            ans=merge(ans,res[k][v]);
            ans=merge(ans,res[k][u]);
            u=pa[k][u];
            v=pa[k][v];
        }
    }
    ans=merge(ans,res[0][u]); ans=merge(ans,res[1][v]);
    return make_pair(pa[0][u],ans);
}
int cnt[MAXN];
int u[MAXN],v[MAXN];
int dist[MAXN],ans[MAXN],candidate[MAXN];
vector<pair<int,P> > query[MAXN];
void dfs2(int v,int p)
{
    cnt[val[v]]++;
    for(auto tmp:query[v]) ans[tmp.S.F]+=tmp.F*cnt[tmp.S.S];
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs2(to,v);
    }
    cnt[val[v]]--;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    init(n);
    memset(ans,0,sizeof(ans));
    for(int i=0;i<q;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        pair<int,P> tmp=get_ans(u[i],v[i]);
        int z=tmp.F,node=tmp.S.F;
        candidate[i]=node;
        if(tmp.S.S==0) ans[i]=-1;
        else
        {
            dist[i]=depth[u[i]]+depth[v[i]]-2*depth[z]+1;
            query[u[i]].push_back(make_pair(1,P(i,node)));
            query[v[i]].push_back(make_pair(1,P(i,node)));
            query[z].push_back(make_pair(-1,P(i,node)));
            if(z!=1) query[pa[0][z]].push_back(make_pair(-1,P(i,node)));
        }
    }
    dfs2(1,0);
    for(int i=0;i<q;i++)
    {
        if(ans[i]==-1) puts("-1");
        else if(ans[i]*2>dist[i]) printf("%d\n",candidate[i]); else puts("-1");
    }
    return 0;
}
