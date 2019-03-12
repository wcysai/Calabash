#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 18
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge
{
    int to,cost;
};
vector<edge> G[MAXN];
int pa[MAXLOGN][MAXN];
int depth[MAXN];
vector<int> s[MAXN];
int res[MAXLOGN][MAXN];
int n,m;
void add_edge(int u,int v,int w)
{
    G[u].push_back((edge){v,w});
    G[v].push_back((edge){u,w});
}
struct E
{
    int u,v,w,x;
};
vector<E> e1,e2;
bool cmp1(E p,E q)
{
    return p.x>q.x;
}
bool cmp2(E p,E q)
{
    return p.w>q.w;
}
int p[MAXN],r[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
        s[i].push_back(i);
    }
}
int find(int x)
{
    while(x!=p[x]) x=p[x]; 
    return x;
}
void merge(vector<int> &p,vector<int> &q)
{
    if(p.size()<q.size()) swap(p,q);
    p.insert(p.end(),q.begin(),q.end());
    q.clear();
}
void unite(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) {p[x]=y; merge(s[y],s[x]);}
    else
    {
        p[y]=x;
        merge(s[x],s[y]);
        if(r[x]==r[y]) r[x]++;
    }
}
void die(int v)
{
    s[find(v)].clear();
}
void dfs(int v,int p,int d,int w)
{
    res[0][v]=w;
    pa[0][v]=p;
    depth[v]=d;
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        dfs(e.to,v,d+1,e.cost);
    }
}
void init2(int n)
{
    dfs(1,0,0,INF+1);
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=n;v++)
        {
            if(pa[k][v]<=0) {pa[k+1][v]=0; res[k+1][v]=res[k][v];}
            else {pa[k+1][v]=pa[k][pa[k][v]]; res[k+1][v]=min(res[k][v],res[k][pa[k][v]]);}
        }
    }
}
int get_min(int u,int v)
{
    if(depth[u]>depth[v]) swap(u,v);
    int need=depth[v]-depth[u];
    int ans=INF+1;
    for(int k=0;k<MAXLOGN;k++)
    {
        if(need&(1<<k))
        {
            ans=min(ans,res[k][v]);
            v=pa[k][v];
        }
    }
    if(u==v) return ans;
    for(int k=MAXLOGN-1;k>=0;k--)
    {
        if(pa[k][u]!=pa[k][v])
        {
            ans=min(ans,res[k][u]);
            ans=min(ans,res[k][v]);
            u=pa[k][u];v=pa[k][v];
        }
    }
    ans=min(ans,res[0][u]);ans=min(ans,res[0][v]);
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int t,u,v,w;
        scanf("%d%d%d%d",&t,&u,&v,&w);
        if(t==1) 
        {
            e1.push_back((E){u,v,w,0});
            add_edge(u,v,w);
        } else e2.push_back((E){u,v,w,0});
    }
    init(n);init2(n);
    for(auto &e:e2) e.x=get_min(e.u,e.v);
    sort(e2.begin(),e2.end(),cmp1);
    sort(e1.begin(),e1.end(),cmp2);
    int now=0;
    for(auto e:e2)
    {
        while(now<(int)e1.size()&&e1[now].w>e.x) {unite(e1[now].u,e1[now].v); now++;}
        if(e.x>=e.w) continue;
        die(e.u); die(e.v);
    }
    vector<int> ans;
    for(int i=1;i<=n;i++)  
        for(auto v:s[i])
            ans.push_back(v);
    sort(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for(auto v:ans) printf("%d ",v);
    return 0;
}
