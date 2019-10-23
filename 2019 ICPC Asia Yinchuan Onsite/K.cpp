#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 100;
int A1[maxn][maxn];
int A2[maxn][maxn];
pair<int,int> diff1[maxn * maxn], diff2[maxn*maxn];
int n,m;
inline int read(){
    int ret = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9')ret = ret * 10 + ch - '0',ch = getchar();
    return ret;
}
int a[maxn][maxn];
int dp[maxn][maxn];
int L[maxn];
int R[maxn];
// 1 * x
int gao1(){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            a[i][j] = diff2[A2[i][j]].first == diff1[A2[i][j]].first;
        }
    }
    int ans = 1;
    memset(dp,0,sizeof dp);
    for (int i=1;i<=n;i++){
        for (int j=m;j>=1;j--){
            if (a[i][j] == 1){
                dp[i][j] = 1 + dp[i][j+1];
            }else{
                dp[i][j] = 0;
            }
            ans = max(ans,dp[i][j] + 1);
        }
    }
    return ans;
}
// x * 1
int gao2(){
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            a[i][j] = diff2[A2[i][j]].second == diff1[A2[i][j]].second;
        }
    }
    int ans = 1;
    memset(dp,0,sizeof dp);
    for (int j=1;j<=m;j++){
        for (int i=n;i>=1;i--){
            if (a[i][j] == 1){
                dp[i][j] = 1 + dp[i+1][j];
            }else{
                dp[i][j] = 0;
            }
            ans = max(ans,dp[i][j] + 1);
        }
    }
    return ans;
}
int gao3(){
    int ans = 1;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            a[i][j] = diff1[A2[i][j]] == diff2[A2[i][j]];
        }
    }
    memset(dp,0,sizeof dp);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (a[i][j] == 1){
                dp[i][j] = 1 + dp[i-1][j];
            }else{
                dp[i][j] = 0;
            }
        }
    }
/*    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
  */
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            L[j] = 0;
            R[j] = m + 1;
        }
        stack<int> stk;
        for (int j=1;j<=m;j++){
            while (!stk.empty() && dp[i][stk.top()] >= dp[i][j])stk.pop();
            if (!stk.empty())L[j] = stk.top();
            stk.push(j);
        }
        while (!stk.empty())stk.pop();
        for (int j=m;j>=1;j--){
            while (!stk.empty() && dp[i][stk.top()] >= dp[i][j])stk.pop();
            if (!stk.empty()) R[j] = stk.top();
            stk.push(j);
        }
        for (int j=1;j<=m;j++){
            R[j] --;L[j] ++;
            if (dp[i][j])
            ans = max(ans,(R[j] - L[j] + 1 + 1) * (dp[i][j] + 1));
        }
    }
    return ans;
}
int main(){
    //scanf("%d%d",&n,&m);
    n = read();
    m = read();
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            A1[i][j] = read();
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            A2[i][j] = read();
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            int diff_l = (j == 1?INT_MAX: A1[i][j-1]);
            int diff_t = (i == 1?INT_MAX: A1[i-1][j]);
            diff1[A1[i][j]] = make_pair(diff_l,diff_t);
            diff_l = (j == 1?-INT_MAX: A2[i][j-1]);
            diff_t = (i == 1?-INT_MAX: A2[i-1][j]);
            diff2[A2[i][j]] = make_pair(diff_l,diff_t);
        }
    }
    int ans = 1;
    // 1 * x
    ans = max(ans,gao1());
    // x * 1
    ans = max(ans,gao2());
    // x * y
    ans = max(ans,gao3());
    cout<<ans<<endl;
    return 0;
}
