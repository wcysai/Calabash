#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
using namespace std;
int n,m,k,tot,t,bcc_cnt,mcnt;
set<int> G[MAXN];
vector<int> GG[MAXN];
vector<int> bcc[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN],bccno[MAXN];
int a[MAXN];
int U[MAXM],V[MAXM];
bool isbridge[MAXM],mark[MAXN];
int cnt[MAXN];
void add_edge(int u,int v)
{
    U[++mcnt]=u;V[mcnt]=v;
    GG[u].push_back(mcnt);GG[v].push_back(mcnt);
}
int adj(int u,int e)
{
    return U[e]==u?V[e]:U[e];
}
void dfs1(int v,int edge)
{
    dfn[v]=low[v]=++tot;
    st[t++]=v;
    for(auto e:GG[v])
    {
        int to=adj(v,e);
        if(!dfn[to])
        {
            dfs1(to,e);
            low[v]=min(low[v],low[to]);
        }
        else if(e!=edge) low[v]=min(low[v],dfn[to]);
    }
    if(low[v]==dfn[v]&&edge!=-1) isbridge[edge]=true;
}
void dfs2(int v)
{
    dfn[v]=1;
    bccno[v]=bcc_cnt;
    bcc[bcc_cnt].push_back(v);
    for(auto e:GG[v])
    {
        int to=adj(v,e);
        if(isbridge[e]) continue;
        if(!dfn[to]) dfs2(to);
    }
}

int tarjan()
{
    bcc_cnt=tot=0;
    memset(dfn,0,sizeof(dfn));
    memset(isbridge,false,sizeof(isbridge));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i,-1);
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs2(i);
        }
    }
    return bcc_cnt;
}
vector<int> ans;
bool vis[MAXN];
bool flag;
void dfs(int v)
{
    vis[v]=true;
    if(cnt[bccno[v]]>=k) flag=true;
    ans.push_back(v);
    for(auto to:G[v]) if(!vis[to]) dfs(to);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].insert(v); G[v].insert(u);
    }
    for(int i=1;i<=n;i++)
    {
        for(auto to:G[i])
        {
            if(to<i) continue;
            add_edge(i,to);
        }
    }
    int p=tarjan();
    for(int i=1;i<=n;i++) cnt[bccno[i]]++;
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        scanf("%d",&a[i]);
        if(i>0)
        {
            for(auto to:G[a[i]]) G[to].erase(a[i]);
            G[a[i]].clear();
        }
    }
    flag=false;
    memset(vis,false,sizeof(vis));
    dfs(a[0]);
    if(flag)
    {
        printf("%d\n",n);
        for(int i=1;i<=n;i++) printf("%d ",i);
        puts("");
        return 0;
    }
    sort(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for(auto x:ans) printf("%d ",x);
    puts("");
    return 0;
}
