#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int n,m;
bool dp[maxn][maxn][2];
char s[maxn];
char t[maxn];
int main(){
    cin>>s+1;
    cin>>t+1;
    n = strlen(s+1);
    m = strlen(t+1);
    dp[0][0][0] = dp[0][0][1] = 1;
    for (int i=0;i<=n;i++){
        for (int j=0;j<=m;j++){
            // 0 match with a.
            if (dp[i][j][0]){
                if (j + 1 <= m and i + 1 <= n and t[j+1] == s[i+1])dp[i+1][j+1][1] = 1;
            }
            // 1 match with a.
            if (dp[i][j][1]){
                if (i + 1 <= n)dp[i+1][j][0] = 1;
            }
            // b not used
            if (dp[i][j][0])dp[i][j+1][0] = 1;
        }
    }
    bool succ = false;
    for (int i=0;i<=m;i++){
        succ |= dp[n][i][0];
        succ |= dp[n][i][1];
    }
    if (succ)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}
