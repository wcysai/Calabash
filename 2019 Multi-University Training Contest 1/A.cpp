#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
vector<P> pos[MAXN];
int dp[2][MAXN][MAXN][MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
bool check(int i,int j,int k,int l)
{
    for(auto p:pos[i])
    {
        int cnt=1;
        if(j>=p.F) cnt++;
        if(k>=p.F) cnt++;
        if(l>=p.F) cnt++;
        if(cnt!=p.S) return false;
    }
    return true;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) pos[i].clear();
        for(int i=0;i<m;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            pos[y].push_back(P(x,z));
        }
        memset(dp[0],0,sizeof(dp[0]));
        dp[0][0][0][0]=1;
        for(int i=0;i<n;i++)
        {
            int now=i&1,nxt=now^1;
            for(int j=0;j<=i+1;j++)
                for(int k=0;k<=j+1;k++)
                    for(int l=0;l<=k+1;l++)
                        dp[nxt][j][k][l]=0;
            for(int j=0;j<=i;j++)
            {
                for(int k=0;k<=j;k++)
                {
                    for(int l=0;l<=k;l++)
                    {
                        if(!dp[now][j][k][l]) continue;
                        if(!check(i,j,k,l)) continue;
                        add(dp[nxt][j][k][l],dp[now][j][k][l]);
                        add(dp[nxt][i][k][l],dp[now][j][k][l]);
                        add(dp[nxt][i][j][l],dp[now][j][k][l]);
                        add(dp[nxt][i][j][k],dp[now][j][k][l]);
                    }
                }
            }
        }
        int ans=0;
        for(int j=0;j<=n;j++)
            for(int k=0;k<=j;k++)
                for(int l=0;l<=k;l++)
                    if(check(n,j,k,l)) add(ans,dp[n&1][j][k][l]);
        printf("%d\n",ans);
    }
    return 0;
}
