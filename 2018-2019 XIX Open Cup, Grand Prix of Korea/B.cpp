#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,m,tot;
char str[MAXN][MAXN];
struct node 
{
    int l,r,id;
};
vector<node> row[MAXN],col[MAXN];
node findrow(int x,int y)
{
    for(auto p:row[x]) if(p.l<=y&&p.r>=y) return p;
    return (node){-1,-1,-1};
}
node findcol(int x,int y)
{
    for(auto p:col[y]) if(p.l<=x&&p.r>=x) return p; 
    return (node) {-1,-1,-1};
}
bool isrowborder(int x,int y,node p)
{
    return (y==p.l)||(y==p.r);
}
bool iscolborder(int x,int y,node p)
{
    return (x==p.l)||(x==p.r);
}
vector<int> G[2*MAXN*MAXN];
vector<int> rG[2*MAXN*MAXN];
vector<int> vs;
bool used[2*MAXN*MAXN];
int cmp[2*MAXN*MAXN];
void add_edge(int from,int to)
{
    G[from].push_back(to);
    rG[to].push_back(from);
}
void dfs(int v)
{
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++)
        if(!used[G[v][i]]) dfs(G[v][i]);
    vs.push_back(v);
}
void rdfs(int v,int k)
{
    used[v]=true;
    cmp[v]=k;
    for(int i=0;i<(int)rG[v].size();i++)
        if(!used[rG[v][i]]) rdfs(rG[v][i],k);
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=1;v<=2*tot;v++) if(!used[v]) dfs(v);
    int k=0;
    memset(used,0,sizeof(used));
    for(int i=vs.size()-1;i>=0;i--) if(!used[vs[i]]) rdfs(vs[i],k++);
    return k;
}
vector<int> g[MAXN*MAXN];
bool reach[MAXN*MAXN][MAXN*MAXN];
bool vis[MAXN*MAXN];
vector<int> possible;
vector<P> constraints;
void dfs2(int s,int v)
{
    reach[s][v]=true;
    vis[v]=true;
    for(auto to:g[v])
    {
        if(vis[to]) continue;
        dfs2(s,to);
    }
}
void transitive_closure()
{
    for(int i=1;i<=tot;i++)
    {
        memset(vis,false,sizeof(vis));
        dfs2(i,i);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
    for(int i=1;i<=n;i++)
    {
        int last=-1;
        for(int j=1;j<=m;j++)
        {
            if(str[i][j]!='#') {if(last==-1) last=j;}
            else
            {
                if(last!=-1)
                {
                    node newnode=(node){last,j-1,++tot};
                    row[i].push_back(newnode);
                }
                last=-1;
            }
        }
        if(last!=-1)
        {
            node newnode=(node){last,m,++tot};
            row[i].push_back(newnode);
        }
    }
    for(int i=1;i<=m;i++)
    {
        int last=-1;
        for(int j=1;j<=n;j++)
        {
            if(str[j][i]!='#') {if(last==-1) last=j;}
            else
            {
                if(last!=-1)
                {
                    node newnode=(node){last,j-1,++tot};
                    col[i].push_back(newnode);
                }
                last=-1;
            }
        }
        if(last!=-1)
        {
            node newnode=(node){last,n,++tot};
            col[i].push_back(newnode);
        }
    }
    //printf("%d\n",tot);
    memset(reach,false,sizeof(reach));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(str[i][j]=='#') continue;
            node r=findrow(i,j); node c=findcol(i,j);
            if(isrowborder(i,j,r)) g[r.id].push_back(c.id); 
            if(iscolborder(i,j,c)) g[c.id].push_back(r.id); 
            if(str[i][j]=='*') constraints.push_back(P(c.id,r.id));
            if(str[i][j]=='O') {possible.push_back(c.id); possible.push_back(r.id);}
        }
    transitive_closure();
    //1..tot clause is true
    //tot+1.. 2*tot clause is false
    //unreachable constraints
    for(int i=1;i<=tot;i++)
        for(int j=i+1;j<=tot;j++)
        {
            if(!reach[i][j]&&!reach[j][i])
            {
                add_edge(i,tot+j);
                add_edge(j,tot+i);
            }
        }
    //unreachable by starting point
    for(int i=1;i<=tot;i++)
        if(!reach[possible[0]][i]&&!reach[possible[1]][i])
            add_edge(i,tot+i);
    //stars constraint
    for(auto p:constraints)
    {
        int u=p.F,v=p.S;
        add_edge(tot+u,v);
        add_edge(tot+v,u);
    }
    scc();
    bool f=true;
    for(int i=1;i<=tot;i++) {if(cmp[i]==cmp[tot+i]) f=false;}
    if(f) puts("YES"); else puts("NO");
    return 0;
}

