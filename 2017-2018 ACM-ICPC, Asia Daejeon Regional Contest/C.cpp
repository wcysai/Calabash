//
// Created by sy-chen on 18-5-20.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int deg[MAXN],color[MAXN],u[MAXM],v[MAXM],ans[MAXN];
int n,m;
vector<int> G[MAXN],order;
void dfs_visit(int v)
{
    color[v]=1;
    for(int i=0;i<G[v].size();i++)
    {
        int to=G[v][i];
        if(color[to]==0) dfs_visit(to);
    }
    color[v]=2;
    order.push_back(v);
}
void toposort()
{
    order.clear();
    memset(color,0,sizeof(color));
    for(int i=0;i<n;i++)
        if(color[i]==0) dfs_visit(i);
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(deg,0,sizeof(deg));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        deg[u[i]]++;deg[v[i]]++;
    }
    for(int i=1;i<=m;i++)
    {
        if(deg[u[i]]<deg[v[i]]) {G[u[i]].push_back(v[i]);}
        if(deg[v[i]]<deg[u[i]]) {G[v[i]].push_back(u[i]);}
    }
    toposort();
    //printf("%d\n",order.size());
    memset(ans,0,sizeof(ans));
    int res=0;
    for(int i=order.size()-1;i>=0;i--)
    {
        int v=order[i];
        //printf("%d\n",v);
        ans[v]=max(ans[v],1);
        res=max(res,ans[v]);
        for(int j=0;j<G[v].size();j++)
            ans[G[v][j]]=max(ans[G[v][j]],ans[v]+1);
    }
    printf("%d\n",res);
    return 0;
}
