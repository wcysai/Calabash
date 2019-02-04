#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
int ans[MAXN],deg[MAXN];
void dfs(int v,int p)
{
    int cnt=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        if(!ans[to]) cnt++;
        ans[v]+=ans[to];
    }
    if(cnt) ans[v]+=cnt-1;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);u++;v++;
        G[u].push_back(v);G[v].push_back(u);
        deg[u]++;deg[v]++;
    }
    int root=-1;
    for(int i=1;i<=n;i++)
    {
        if(deg[i]>=3)
        {
            root=i;
            break;
        }
    }
    if(root==-1)
    {
        puts("1");
        return 0;
    }
    dfs(root,0);
    printf("%d\n",ans[root]);
    return 0;
}

