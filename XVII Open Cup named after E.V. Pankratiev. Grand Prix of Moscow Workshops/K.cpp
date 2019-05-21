#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cost;};
vector<edge> G[MAXN];
int n;
ll dp[MAXN][3];
bool iswhite[MAXN],isblack[MAXN];
void dfs(int v,int p)
{
    dp[v][0]=dp[v][1]=dp[v][2]=INF;
    if(isblack[v]) dp[v][1]=0;
    else if(iswhite[v]) dp[v][2]=0;
    else dp[v][0]=0;
    ll tmp[3];
    for(auto e:G[v])
    {
        int to=e.to,cost=e.cost;
        if(to==p) continue;
        dfs(to,v);
        tmp[0]=tmp[1]=tmp[2]=INF;
        for(int i=0;i<3;i++) 
            for(int j=0;j<3;j++)
                tmp[i]=min(tmp[i],dp[v][i]+cost+dp[to][j]);
        for(int i=1;i<3;i++) 
        {
            tmp[i]=min(tmp[i],dp[v][i]+dp[to][i]);
            tmp[i]=min(tmp[i],dp[v][0]+dp[to][i]);
            tmp[i]=min(tmp[i],dp[v][i]+dp[to][0]);
        }
        tmp[0]=min(tmp[0],dp[v][0]+dp[to][0]);
        for(int i=0;i<3;i++) dp[v][i]=tmp[i];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back((edge){v,w});
        G[v].push_back((edge){u,w});
    }
    memset(isblack,false,sizeof(isblack));
    memset(iswhite,false,sizeof(iswhite));
    int k;
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        int x;
        scanf("%d",&x);
        isblack[x]=true;
    }
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        int x;
        scanf("%d",&x);
        iswhite[x]=true;
    }
    dfs(1,0);
    printf("%lld\n",min(dp[1][1],dp[1][2]));
    return 0;
}
