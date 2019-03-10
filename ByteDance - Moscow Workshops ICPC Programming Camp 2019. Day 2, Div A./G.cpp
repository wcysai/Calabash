#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 10005
#define MAXK 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,k;
vector<int> G[MAXN];
int sz[MAXN];
int dp[MAXN][MAXK][5];
int tmp[MAXK][5];
//dp[i][j][0/1/2/3/4]:
//maximum total length
//in the subtree of i
//with j paths
//last dimension:
//0: not path passing i
//1: a chain ending at i
//2: a passing crossing i
//3: a single point
//4: maximum of all above
void upd(int &a,int b) {a=max(a,b);}
void dfs(int v,int p)
{
    sz[v]=1;
    dp[v][1][3]=dp[v][1][4]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        memset(tmp,0,sizeof(tmp));
        for(int i=0;i<=min(k,sz[v]);i++)
            for(int j=0;j<=min(k-i+1,sz[to]);j++)
            {
                if(i+j==0) continue;
                if(i+j<=k)
                {
                    upd(tmp[i+j][0],dp[v][i][0]+dp[to][j][4]);
                    if(dp[v][i][1]) upd(tmp[i+j][1],dp[v][i][1]+dp[to][j][4]);
                    if(dp[v][i][2]) upd(tmp[i+j][2],dp[v][i][2]+dp[to][j][4]);
                    if(dp[v][i][3]) upd(tmp[i+j][3],dp[v][i][3]+dp[to][j][4]);
                    if(dp[to][j][1]) upd(tmp[i+j][1],dp[v][i][0]+dp[to][j][1]+1);
                    if(dp[to][j][3]) upd(tmp[i+j][1],dp[v][i][0]+dp[to][j][3]+1);
                }
                if(dp[v][i][1]&&dp[to][j][1]) upd(tmp[i+j-1][2],dp[v][i][1]+dp[to][j][1]);
                if(dp[v][i][1]&&dp[to][j][3]) upd(tmp[i+j-1][2],dp[v][i][1]+dp[to][j][3]);
            } 
        sz[v]+=sz[to];
        for(int i=0;i<=min(k,sz[v]);i++) dp[v][i][0]=tmp[i][0],dp[v][i][1]=tmp[i][1],dp[v][i][2]=tmp[i][2],dp[v][i][3]=tmp[i][3],dp[v][i][4]=max(max(tmp[i][0],tmp[i][1]),max(tmp[i][2],tmp[i][3]));
    }
}
int main()
{
    while(scanf("%d%d",&n,&k)==2)
    {
        if(!n&&!k) break;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++) memset(dp[i],0,sizeof(dp[i]));
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);G[v].push_back(u);
        }
        dfs(1,0);
        printf("%d\n",dp[1][k][4]);
    }
    return 0;
}

