#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int deg[MAXN];
bool a[MAXN][MAXN];
vector<int> G[MAXN];
vector<int> rG[MAXN];
vector<P> as;
void add_edge(int u,int v,bool flag=false)
{
    a[u][v]=a[v][u]=true;
    G[u].push_back(v);G[v].push_back(u);
    deg[u]++;deg[v]++;
    if(flag) as.push_back(P(u,v));
}
void add_comp_edge(int u,int v)
{
    rG[u].push_back(v);
    rG[v].push_back(u);
}
vector<int> vert[MAXN];
int tot;
bool vis[MAXN];
int color[MAXN];
void dfs1(int v,int p)
{
    vis[v]=true;
    for(auto to:rG[v])
    {
        if(to==p) continue;
        if(!vis[to])
        {
            dfs1(to,v);
            if(deg[to]&1) add_edge(v,to,true);
        }
    }
}
void dfs2(int v,int c)
{
    color[v]=c;
    vert[c].push_back(v);
    for(auto to:G[v])
    {
        if(color[to]) continue;
        dfs2(to,c);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(a,false,sizeof(a));
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);   
    } 
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(!a[i][j]) add_comp_edge(i,j);
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) if(!vis[i]) dfs1(i,0);
    for(int i=1;i<=n;i++) 
    {
        if(deg[i]&1)
        {
            puts("-1");
            return 0;
        }
    }
    /*for(int i=1;i<=n;i++)
    {
        for(auto to:G[i]) printf("%d ",to);
        puts("");
    }*/
    tot=0;
    memset(color,0,sizeof(color));
    for(int i=1;i<=n;i++) if(!color[i]) dfs2(i,++tot);
    if(tot==2)
    {
        if(vert[1].size()>vert[2].size()) swap(vert[1],vert[2]);
        if(vert[1].size()==1)
        {
            bool f=false;
            int sz=(int)vert[2].size();
            for(int i=0;i<sz;i++)
            {
                if(f) break;
                for(int j=i+1;j<sz;j++)
                {
                    int u=vert[2][i];
                    int v=vert[2][j];
                    if(!a[u][v])
                    {
                        f=true;
                        add_edge(u,v,true);add_edge(vert[1][0],v,true);add_edge(vert[1][0],u,true);
                        break;
                    }
                }
            }
            if(!f) 
            {
                if(as.size()==0)
                {
                    puts("-1"); return 0;
                }
                else
                {
                    P p=as.back();as.pop_back();
                    int u=p.F,v=p.S;
                    add_edge(vert[1][0],v,true);add_edge(vert[1][0],u,true);
                }
            }
        }
        else
        {
            add_edge(vert[1][0],vert[2][0],true);add_edge(vert[1][0],vert[2][1],true);
            add_edge(vert[1][1],vert[2][0],true);add_edge(vert[1][1],vert[2][1],true);
        }
    }
    else if(tot>=3) for(int i=1;i<=tot;i++) add_edge(vert[i][0],vert[i%tot+1][0],true);
    printf("%d\n",(int)as.size());
    for(auto p:as) printf("%d %d\n",min(p.F,p.S),max(p.F,p.S));
    return 0;
}

