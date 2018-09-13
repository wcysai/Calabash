//
// Created by calabash_boy on 18-6-8.
//
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge
{
    int to,id;
};
vector<edge> G[2][MAXN];
int t,n,m;
int u[MAXN],v[MAXN];
bool used[MAXN],ans[MAXN];
void dfs(int type,int v,int p)
{
    used[v]=true;
    for(int i=0;i<G[type][v].size();i++)
    {
        int to=G[type][v][i].to,id=G[type][v][i].id;
        if(to==p) continue;
        if(!used[to])
        {
            ans[id]=true;
            dfs(type,to,v);
        }
    }
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[0][i].clear(),G[1][i].clear();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&u[i],&v[i]);
            G[0][u[i]].push_back((edge){v[i],i});G[1][v[i]].push_back((edge){u[i],i});
        }
        for(int i=1;i<=n;i++) used[i]=false;
        for(int i=1;i<=m;i++) ans[i]=false;
        int cnt=2*n;
        dfs(0,1,0);
        for(int i=1;i<=n;i++) used[i]=false;
        dfs(1,1,0);
        for(int i=1;i<=m;i++) if(ans[i]) cnt--;
        for(int i=1;i<=m;i++)
            if(!ans[i])
            {
                if(cnt) cnt--;
                else printf("%d %d\n",u[i],v[i]);
            }
    }
    return 0;
}
