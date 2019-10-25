#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 100;
int n,m;
int w[maxn];
int sum[maxn];
int r[maxn];
//int dp[maxn][maxn][maxn];
const int inf = 0x3f3f3f3f;
/*
int gao(int dep, int people, int leaf){
    if (dp[dep][people][leaf] != -1)return dp[dep][people][leaf];
    int &ans = dp[dep][people][leaf] = inf;
    if (n - people +1 <= leaf){
        ans = 0;
        for (int i = people;i <= n;i ++){
            ans += w[i];
        }
        ans *= dep;
        return ans;
    }
    if (people == n+1)return ans = 0;
    if (leaf == 0)return ans = inf;
    if (dep == m)return ans = inf;
    // this person put at this dep
    if (leaf >= 1)ans = min(ans,w[people] * dep + gao(dep,people+1,leaf - 1));
    // this person not put at this dep
    ans = min(ans,gao(dep+1,people,min(500,leaf * r[dep+1])));
    return ans;
}
*/
int dp[2][maxn][maxn];
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;i++)cin>>w[i];
    for (int i=1;i<=m;i++)cin>>r[i];
    sort(w + 1,w + 1 + n,[](int x,int y){
        return x > y;
    });
    for (int i=1;i<=n;i++){
        sum[i] = sum[i-1] + w[i];
    }
    for (int i=0;i<2;i++)for (int j=0;j<maxn;j++)for (int k=0;k<maxn;k++)dp[i][j][k] = inf;
    int now = 0;
    for (int dep= m ;dep >= 1;dep--,now ^= 1){
        for (int people = n;people >=1;people --){
            for (int leaf = 1;leaf <= n;leaf ++){
                int &dp_val = dp[now][people][leaf] = inf;
                if (n - people + 1 <= leaf){
                    dp_val = sum[n] - sum[people-1];
                    dp_val *= dep;
                    continue;
                }
                // this person put at this dep
                if (leaf >= 1)dp_val = min(dp_val,w[people] * dep + dp[now][people+1][leaf-1]);
                // this person not put at this dep
                dp_val = min(dp_val, dp[now ^ 1][people][min(n,leaf * r[dep+1])]);
            }
        }
    }
    cout<<dp[now^1][1][r[1]]<<endl;
    return 0;
}
