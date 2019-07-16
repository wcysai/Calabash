#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
int n,m;
bool dp[MAXN][3];
bool isleaf[MAXN];
int color[MAXN];
int ans[MAXN];
void dfs(int v)
{
    if(isleaf[v])
    {
        dp[v][color[v]]=true;
        return;
    }
    if(v!=1)
    {
        dfs(G[v][0]); dfs(G[v][1]);
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    if(dp[G[v][0]][j]&&dp[G[v][1]][k]&&i!=j&&i!=k) dp[v][i]=true;
    }
    else
    {
        dfs(G[v][0]); dfs(G[v][1]); dfs(G[v][2]);
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    for(int l=0;l<3;l++)
                        if(dp[G[v][0]][j]&&dp[G[v][1]][k]&&dp[G[v][2]][l]&&i!=j&&i!=k&&i!=l) dp[v][i]=true;
    }
}
void dfs2(int v,int c)
{
    ans[v]=c+1;
    if(isleaf[v]) return;
    if(v!=1)
    {
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                if(dp[G[v][0]][j]&&dp[G[v][1]][k]&&c!=j&&c!=k) 
                {
                    dfs2(G[v][0],j);
                    dfs2(G[v][1],k);
                    return;
                }
        assert(0);
    }
    else
    {
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                for(int l=0;l<3;l++)
                    if(dp[G[v][0]][j]&&dp[G[v][1]][k]&&dp[G[v][2]][l]&&c!=j&&c!=k&&c!=l) 
                    {
                        dfs2(G[v][0],j);
                        dfs2(G[v][1],k);
                        dfs2(G[v][2],l);
                        return;
                    }
        assert(0);
    }
}
int main()
{
    freopen("coloring.in","r",stdin);
    freopen("coloring.out","w",stdout);
    while(scanf("%d",&n)==1)
    {
        if(!n) break;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=2;i<=n;i++)
        {
            int p;
            scanf("%d",&p);
            G[p].push_back(i); 
        }
        for(int i=1;i<=n;i++) isleaf[i]=dp[i][0]=dp[i][1]=dp[i][2]=false;
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            int v,c;
            scanf("%d%d",&v,&c);
            isleaf[v]=true;
            color[v]=c-1;
        }
        dfs(1);
        int c=-1;
        for(int i=0;i<3;i++) if(dp[1][i]) c=i;
        if(c==-1) {puts("NO"); continue;}
        puts("YES");
        dfs2(1,c);
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        puts("");
    }
}
