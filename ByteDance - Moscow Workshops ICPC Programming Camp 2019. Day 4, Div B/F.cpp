#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
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
int n,m;
vector<int> G[MAXN];
int dep[MAXN];
vector<vector<int> > ears;
vector<int> path[MAXN];
vector<int> back[MAXN];
int low[MAXN];
int vis[MAXN];
bool f=true;
void cmin(int &a,int b)
{
    if(dep[b]<dep[a]) a=b; 
}
void add_ear(int to,vector<int> &a)
{
    reverse(a.begin(),a.end());
    a.push_back(to);
    ears.push_back(a);
}
void dfs(int v,int p,int d)
{
    if(!f) return;
    vis[v]=1;dep[v]=d;low[v]=v;
    int used=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(!vis[to])
        {
            dfs(to,v,d+1);
            path[to].push_back(v);
            if(!used||dep[low[to]]<dep[low[v]])
            {
                if(used) add_ear(low[v],path[v]);
                swap(path[v],path[to]);
                low[v]=low[to];
                used=1;
            }
            else add_ear(low[to],path[to]);
        }
        else if(vis[to]==1) back[v].push_back(to);
    }
    vis[v]=2;
    for(int i=0;i<(int)back[v].size();i++)
    {
        int u=back[v][i];
        if(!used||dep[u]<dep[low[v]])
        {
            if(used) add_ear(low[v],path[v]);
            path[v].clear();path[v].push_back(v);
            low[v]=u;
            used=1;
        }
        else ears.emplace_back((vector<int>){v,u});
    }
   /* printf("%d %d %d\n",v,dep[v],low[v]);
    printf("chain %d\n",v);
    for(auto x:path[v]) printf("%d ",x);
    puts(""); */
    if(dep[low[v]]==dep[v]&&v!=1) f=false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1,0,0);
    if(!f) puts("-1");
    else
    {
        add_ear(1,path[1]);
        printf("%d\n",(int)ears.size());
        for(int i=0;i<(int)ears.size();i++)
        {
            printf("%d ",(int)ears[i].size()-1);
            for(int j=0;j<(int)ears[i].size();j++)
                printf("%d ",ears[i][j]);
            puts("");
        }
    }
    return 0;
}

