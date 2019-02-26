#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot,t,bcc_cnt,mcnt;
vector<int> G[MAXN],bcc[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN],bccno[MAXN];
bool art[MAXN];
vector<int> tree[MAXN];
int id[MAXN];
int N;
//block-cut tree:
//vertex-biconnected components are connected by their shared articulation point
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
void dfs(int v,int p,int &tot)
{
    dfn[v]=low[v]=++tot;
    st[t++]=v;
    for(auto to:G[v])
    {
        if(!dfn[to])
        {
            dfs(to,v,tot);
            low[v]=min(low[v],low[to]);
            if(low[to]>=dfn[v])
            {
                art[v]=(dfn[v]>1||dfn[to]>2);
                bcc_cnt++;
                bcc[bcc_cnt].push_back(v); bccno[v]=bcc_cnt;
                while(bcc[bcc_cnt].back()!=v)
                {
                    bccno[st[t-1]]=bcc_cnt;
                    bcc[bcc_cnt].push_back(st[t-1]),t--;
                }
            }
        }
        else low[v]=min(low[v],dfn[to]);
    }
}
int tarjan()
{
    bcc_cnt=t=0;
    memset(dfn,0,sizeof(dfn));
    memset(art,false,sizeof(art));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,-1,tot=0);
    return bcc_cnt;
}
void build_block_cut_tree()
{
    tarjan();N=0;
    for(int i=1;i<=n;i++) if(art[i]) id[i]=++N;
    for(int i=1;i<=bcc_cnt;i++)
    {
        N++;
        for(auto v:bcc[i])
        {
            if(!art[v]) id[v]=N;
            else 
            {
                tree[id[v]].push_back(N);
                tree[N].push_back(id[v]);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        n++;add_edge(n,u);add_edge(n,v);add_edge(n,w);
    }
    tarjan();
    vector<int> ans;
    for(int i=n-m+1;i<=n;i++) if(art[i]) ans.push_back(i-(n-m));
    printf("%d\n",(int)ans.size());
    for(auto v:ans) printf("%d\n",v);
    return 0;
}

