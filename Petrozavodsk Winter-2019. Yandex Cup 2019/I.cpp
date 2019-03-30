#include<bits/stdc++.h>
#define MAXN 105
#define MAXV 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXV];
int match[MAXV];
bool used[MAXV];
int n,m,V;
int grid[MAXN][MAXN];
char str[3];
int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
bool dfs(int v)
{
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int u=G[v][i],w=match[u];
        if(w<0||!used[w]&&dfs(w))
        {
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}
int bipartite_matching()
{
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=1;v<=V;v++)
    {
         if(match[v]<0)
         {
             memset(used,0,sizeof(used));
             if(dfs(v)) res++;
         }
    }
    return res;
}
int main()
{
    scanf("%d%d",&n,&m);
    V=n*m;
    int sum=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%s",str);
            if(str[0]=='L') grid[i][j]=0; else grid[i][j]=1;
            if(str[1]=='>') sum++;
            else if(str[1]=='v') sum+=2;
            else if(str[1]=='<') sum+=3;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            int x=i,y=j,id1=(x-1)*m+j;
            for(int k=0;k<4;k++)
            {
                int nx=x+dx[k],ny=y+dy[k];
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&grid[nx][ny]+grid[x][y]==1)
                {
                    int id2=(nx-1)*m+ny;
                    add_edge(id1,id2);
                }
            }
        }
    int ans=bipartite_matching();
    if(ans*2==V) 
    {
        if(sum&1) ans--;
        else
        {
            int rem=0;
            if(m%2==0) rem=0;
            else if(n%4==0) rem=0;
            else rem=2;
            if(sum%4!=rem) ans--;
        }
    }
    printf("%d\n",ans);
    return 0;
}

