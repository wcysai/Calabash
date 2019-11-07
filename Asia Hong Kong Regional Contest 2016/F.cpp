#include<bits/stdc++.h>
#define MAXN 100005
#define MAXD 20
#define MAXK 6
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
vector<int> G[MAXN];
int n,k,ans;
int cnt[MAXN],fa[MAXN][MAXD];
vector<int> pre[MAXK][MAXD],suf[MAXK][MAXD];
int dp[MAXN][MAXD];
//dp[i][j]: number of ways to form a perfect k-ary tree rooted at i with depth j
void build_prefix(int v,int p)
{
    for(int i=0;i<=k;i++)
        for(int j=0;j<MAXD;j++)
            pre[i][j].clear(),pre[i][j].resize(cnt[v]+2);
    int tot=1;
    for(int j=0;j<MAXD;j++) pre[0][j][0]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        for(int i=0;i<=k;i++) //chosen
        {
            for(int j=0;j<MAXD;j++) //depth
            {
                pre[i][j][tot]=pre[i][j][tot-1];
                if(i) add(pre[i][j][tot],1LL*pre[i-1][j][tot-1]*dp[to][j]%MOD);
            }
        }
        tot++;
    }
}
void build_suffix(int v,int p)
{
    for(int i=0;i<=k;i++)
        for(int j=0;j<MAXD;j++)
            suf[i][j].clear(),suf[i][j].resize(cnt[v]+2);
    int tot=cnt[v];
    for(int j=0;j<MAXD;j++) suf[0][j][cnt[v]+1]=1;
    for(int t=(int)G[v].size()-1;t>=0;t--)
    {
        int to=G[v][t];
        if(to==p) continue;
        for(int i=0;i<=k;i++) //chosen
        {
            for(int j=0;j<MAXD;j++) //depth
            {
                suf[i][j][tot]=suf[i][j][tot+1];
                if(i) add(suf[i][j][tot],1LL*suf[i-1][j][tot+1]*dp[to][j]%MOD);
            }
        }
        tot--;
    }
}
void dfs(int v,int p)
{
    dp[v][0]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        cnt[v]++;
    }
    build_prefix(v,p);
    for(int j=1;j<MAXD;j++) dp[v][j]=pre[k][j-1][cnt[v]];
   // for(int j=0;j<MAXD;j++) printf("%d %d %d\n",v,j,dp[v][j]);
}
void dfs2(int v,int p)
{
    for(int i=0;i<MAXD;i++) add(ans,dp[v][i]);
    int tot=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        tot++;
        for(int j=0;j<MAXD;j++)
        {
            int tmp=0;
            if(j==0) tmp=1;
            else
            {
                for(int prechosen=0;prechosen<=k;prechosen++)
                {
                    add(tmp,1LL*pre[prechosen][j-1][tot-1]*suf[k-prechosen][j-1][tot+1]%MOD);
                    if(prechosen!=k) add(tmp,1LL*pre[prechosen][j-1][tot-1]*suf[k-1-prechosen][j-1][tot+1]%MOD*fa[v][j-1]%MOD);
                }
            }
            fa[to][j]=tmp;
        }
    }
    tot=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        tot++;
        build_prefix(to,v); build_suffix(to,v);
        for(int j=1;j<MAXD;j++)
        {
            dp[to][j]=pre[k][j-1][cnt[to]];
            add(dp[to][j],1LL*fa[to][j-1]*pre[k-1][j-1][cnt[to]]%MOD);
        }
        dfs2(to,v);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1,0);
    ans=0;
    build_prefix(1,0); build_suffix(1,0);
    dfs2(1,0);
    printf("%d\n",ans);
    return 0;
}
