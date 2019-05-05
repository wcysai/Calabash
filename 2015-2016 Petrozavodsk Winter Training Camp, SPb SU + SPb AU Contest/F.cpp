#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 405
#define MAXC (1<<10)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,W;
int w[MAXN][MAXN],c[MAXN][MAXN];
int dp[MAXN][MAXN];
bool dir[MAXN][MAXN];
//false: up 
//true: left
void update(int &a,int b) {a=min(a,b);}
vector<int> ans;
vector<int> masks;
bool cmp(int x,int y)
{
    return __builtin_popcount(x)<__builtin_popcount(y);
}
bool solve(int mask)
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dp[i][j]=INF;
    if(!(mask&(1<<(c[1][1]-1)))) return false;
    dp[1][1]=w[1][1];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==1&&j==1) continue;
            if(!(mask&(1<<(c[i][j]-1)))) continue;
            if(i>1&&dp[i-1][j]+w[i][j]<dp[i][j])
            {
                dp[i][j]=dp[i-1][j]+w[i][j];
                dir[i][j]=false;
            }
            if(j>1&&dp[i][j-1]+w[i][j]<dp[i][j])
            {
                dp[i][j]=dp[i][j-1]+w[i][j];
                dir[i][j]=true;
            }
        }
    return dp[n][n]<=W;
}
void print(int mask)
{
    printf("%d\n",(int)__builtin_popcount(mask));
    int x=n,y=n;
    while(x>0&&y>0)
    {
        ans.push_back(y); ans.push_back(x);
        if(dir[x][y]) y--; else x--;
    }
    reverse(ans.begin(),ans.end());
    for(int i=0;i<(int)ans.size();i++) printf("%d ",ans[i]);
    puts("");
    exit(0);
} 
int main()
{
    scanf("%d%d%d",&n,&k,&W);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&w[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&c[i][j]);
    for(int i=1;i<(1<<k);i++) masks.push_back(i);
    sort(masks.begin(),masks.end(),cmp);
    for(int i=0;i<(int)masks.size();i++) if(solve(masks[i])) print(masks[i]);
    puts("-1");
    return 0;
}
