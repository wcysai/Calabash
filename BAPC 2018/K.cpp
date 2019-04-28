#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,h;
vector<int> G[MAXN];
int deg[MAXN],dfn[MAXN],tot;
vector<P> leaves;
void dfs(int v,int p)
{
    dfn[v]=++tot;
    if((int)G[v].size()==1) leaves.push_back(P(dfn[v],v-1));
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
    }
}
int main()
{
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        u++; v++;
        G[u].push_back(v); G[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    if(n==2)
    {
        printf("1\n");
        printf("0 1\n");
        return 0;
    }
    int root=-1;
    for(int i=1;i<=n;i++)
    {
        if(deg[i]>=2) {root=i; break;}
    }
    assert(root!=-1);
    dfs(root,0);
    int sz=(int)leaves.size();
    printf("%d\n",(sz+1)/2);
    for(int i=0;i<sz/2;i++) printf("%d %d\n",leaves[i].S,leaves[i+(sz+1)/2].S);
    if(sz&1) printf("%d %d\n",leaves[sz/2].S,root-1);
    return 0;
}
