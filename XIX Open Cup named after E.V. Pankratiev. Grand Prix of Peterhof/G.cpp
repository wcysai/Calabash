#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p[MAXN],dp[MAXN],mark[MAXN];
vector<int> G[MAXN];
int leaf;
int dfs(int v,int p)
{
    if(v!=1&&(int)G[v].size()==1) 
    {
        mark[v]=v;
        return dp[v]=1;
    }
    int res=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        int x=dfs(to,v);
        res+=x;
        if(x>0||mark[v]==0) mark[v]=mark[to];
    }
    return dp[v]=max(0,res-1);
}
    
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++) scanf("%d",&p[i]);
    for(int i=2;i<=n;i++)
    {
        G[p[i]].push_back(i);
        G[i].push_back(p[i]);
    }
    if(dfs(1,0)==0) 
    {
        puts("FIRST");
        printf("%d\n",mark[1]);
    }
    else puts("SECOND");
    return 0;
}
