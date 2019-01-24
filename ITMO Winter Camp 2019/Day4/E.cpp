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
const int maxn = 505;
int n;
vector<int> E[maxn];
bool vis[maxn];
void dfs(int u){
    vis[u] = 1;
    for (int v : E[u]){
        if (vis[v])continue;
        dfs(v);
        break;
    }
}
bool check_loop(){
    memset(vis,0,sizeof vis);
    dfs(1);
    for (int i=1;i<=n;i++){
        if (!vis[i])return false;
    }
    return true;
}
int a[maxn];
int b[maxn];
int dp[maxn][maxn];
int lcs(){
    //for (int i=1;i<=n;i++){
    //    printf("%d ",a[i]);
    //}
    //puts("");
    //for (int i=1;i<=n;i++){
    //    printf("%d ",b[i]);
   // }
   // puts("");
    memset(dp,0,sizeof dp);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            if (a[i] == b[j]){
                dp[i][j] = max(dp[i][j],dp[i-1][j-1] + 1);
            }else{
                dp[i][j] = max(dp[i][j],dp[i-1][j-1]);
            }
        }
    }
    return dp[n][n];
}
int work(int st){
    int now = st;
    int idx = 1;
    memset(vis,0,sizeof vis);
    while (idx <=n){
        a[idx++] = now;
        vis[now] = 1;
        for (int v : E[now]){
            if (vis[v])continue;
            now = v;
            break;
        }
    }
    for (int i=1;i<=n;i++){
        b[i] = st + i - 1;
        if (b[i] > n)b[i] -= n;
    }
    int ans = lcs();
    for (int i=1;i<=n;i++){
        b[i] = st -i +1;
        if (b[i] <=0)b[i] += n;
    }
    ans = max(ans,lcs());
    return n - ans;
}
void solve(){
    for (int i=1;i<=n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        E[i].clear();
        E[i].push_back(x);
        E[i].push_back(y);
    }
    if (!check_loop()){
        puts("Not solvable.");
        return;
    }
    puts("Knot solvable.");
    int ans = INT_MAX;
    for (int i=1;i<=n;i++){
        ans = min(ans,work(i));
    }
    printf("%d\n",ans);
}
int main()
{
    while (scanf("%d",&n)!= EOF && n){
        solve();
    }
    return 0;
}

