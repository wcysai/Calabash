#include <bits/stdc++.h>
#define MAXV 200055
#define MAXLOGV 22
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXV];
vector<int> vt[MAXV];
int pa[MAXLOGV][MAXV];
int depth[MAXV],dfn[MAXV],st[MAXV];
int n,m,q,tot;
void add_edge(int from,int to)
{
    vt[from].push_back(to);
}
bool cmp(int x,int y)
{
    return dfn[x]<dfn[y];
}
void dfs(int v,int p,int d)
{
    dfn[v]=++tot;
    pa[0][v]=p;
    depth[v]=d;
    for(int i=0;i<(int)G[v].size();i++)
        if(!dfn[G[v][i]]) dfs(G[v][i],v,d+1);
}
void init(int V){
    dfs(1,-1,0);
    for(int k=0;k+1<MAXLOGV;k++){
        for(int v=1;v<=V;v++){
            if(pa[k][v]<0) pa[k+1][v]=-1;
            else pa[k+1][v]=pa[k][pa[k][v]];
        }
    }
}
int get(int v,int x)
{
    for(int k=0;k<MAXLOGV;k++)
        if((x>>k)&1)
            v=pa[k][v];
    return v;
}
int lca(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    v=get(v,depth[v]-depth[u]);
    if(u==v) return u;
    for(int k=MAXLOGV-1;k>=0;k--)
    {
        if(pa[k][u]!=pa[k][v])
        {
            u=pa[k][u];
            v=pa[k][v];
        }
    }
    return pa[0][u];
}
int build_vtree(vector<int> &a)
{
    sort(a.begin(),a.end(),cmp);
    assert(a.size()>0);
    int t=0;
    st[t++]=a[0];
    vector<int> newly;
    for(int i=1;i<(int)a.size();i++)
    {
        if(t==0) {st[t++]=a[i]; continue;}
        int l=lca(a[i],st[t-1]);
        while(t>1&&dfn[st[t-2]]>=dfn[l]) add_edge(st[t-2],st[t-1]),t--; 
        if(l!=st[t-1]) {add_edge(l,st[t-1]),st[t-1]=l; newly.push_back(l);}
        st[t++]=a[i];
    }
    while(t>1) add_edge(st[t-2],st[t-1]),t--;
    for(auto it:newly) a.push_back(it);
    return st[0];
}
int color[MAXV];
vector<P> E;
vector<int> a;
void dfs2(int v,int p)
{
    color[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        if(color[to]==0) dfs2(to,v);
        else if(color[to]==1) {E.push_back(P(v,to)); a.push_back(v); a.push_back(to);}
    }
    color[v]=2;
}
int fa[MAXV],tag[MAXV];
int deg[MAXV];
bool f;
int root;
void dfs3(int v,int p)
{
    fa[v]=p;
    for(int i=0;i<(int)vt[v].size();i++)
    {
        int to=vt[v][i];
        if(to==p) continue;
        dfs3(to,v);
    }
}
void try_vertex(int v)
{
    while(v!=root)
    {
        tag[v]=1-tag[v];
        if(tag[v])
        {
            deg[v]++;
            deg[fa[v]]++;
        } else
        {
            deg[v]--;
            deg[fa[v]]--;
        }
        v=fa[v];
    }
}
int p[MAXV],r[MAXV];
void Init()
{
    for(auto it:a)
    {
        p[it]=it;
        r[it]=0;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) p[x]=y;
    else
    {
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
int main()
{
    //freopen("test.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    if(m==n-1)
    {
        puts("0");return 0;
    }
    memset(color,0,sizeof(color));
    a.push_back(1);
    dfs2(1,0);
    for(auto p:E)
    {
        for(int i=0;i<(int)G[p.F].size();i++)
        {
            if(G[p.F][i]==p.S)
            {
                G[p.F].erase(G[p.F].begin()+i);
                break;
            }
        }
        for(int i=0;i<(int)G[p.S].size();i++)
        {
            if(G[p.S][i]==p.F)
            {
                G[p.S].erase(G[p.S].begin()+i);
                break;
            }
        }
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    init(n);
    root=build_vtree(a);assert(root==1);
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    dfs3(root,root);
    int cnt=(int)E.size(),ans=0;
    for(int i=1;i<(1<<cnt);i++)
    {
        //printf("%d\n",i);
        f=true;
        for(int j=0;j<cnt;j++)
        {
            if(i&(1<<j))
            {
                int u=E[j].F,v=E[j].S;
                try_vertex(u);try_vertex(v);
                deg[u]++;deg[v]++;
            }
        }
        for(auto it:a)
        {
            if(deg[it]!=2&&deg[it]!=0) f=false;
        }
        Init();
        for(auto it:a)
        {
            if(tag[it]) unite(it,fa[it]);
        }
        for(int j=0;j<cnt;j++)
        {
            if(i&(1<<j))
            {
                int u=E[j].F,v=E[j].S;
                unite(u,v);
            }
        }
        int cur=-1;
        for(auto it:a)
        {
            if(deg[it]!=2) continue;
            if(cur==-1) cur=find(it);
            else if(cur!=find(it)) f=false;
        }
        //puts("");
        if(f) ans++;
        for(auto it:a) deg[it]=tag[it]=0;
    }
    printf("%d\n",ans);
    return 0;
}
/*
 7 9
 1 2
 1 3
 2 4
 2 5
 3 6
 3 7
 2 3
 4 5
 6 7
 */
