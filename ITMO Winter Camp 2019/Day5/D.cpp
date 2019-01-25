#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define left ddakod
#define right dioakod
using namespace std;
typedef long long ll;
typedef pair<char,char> P;
int T,n,m;
char str[MAXN][MAXN];
int a[MAXN][MAXN];
vector<int> G[MAXN*MAXN];
bool vis[MAXN*MAXN];
int up[6]={0,0,1,1,0,1};
int down[6]={0,1,0,0,1,1};
int left[6]={0,1,1,0,0,1};
int right[6]={0,0,0,1,1,1};
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
void dfs(int v)
{
    vis[v]=true;
    for(auto to:G[v])
    {
        if(vis[to]) continue;
        dfs(to);
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) 
            for(int j=1;j<=m;j++)
                G[(i-1)*m+j].clear();
        for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                a[i][j]=str[i][j]-'A';
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                int id=(i-1)*m+j;
                if(a[i][j]==0) {vis[id]=true; continue;}
                if(i>1&&up[a[i][j]]&&down[a[i-1][j]]) add_edge(id,(i-2)*m+j); 
                if(i<n&&down[a[i][j]]&&up[a[i+1][j]]) add_edge(id,i*m+j);
                if(j>1&&left[a[i][j]]&&right[a[i][j-1]]) add_edge(id,(i-1)*m+j-1);
                if(j<m&&right[a[i][j]]&&left[a[i][j+1]]) add_edge(id,(i-1)*m+j+1);
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                if(!vis[(i-1)*m+j])
                {
                    ans++;
                    dfs((i-1)*m+j);
                }
            }
        printf("%d\n",ans);
    }
    return 0;
}

