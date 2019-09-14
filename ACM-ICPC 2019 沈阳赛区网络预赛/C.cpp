#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const int maxn = 1e3 + 100;
const int maxm = 1e4 + 100;
int n,m;
int p[maxn];
int c[maxn];
ll dp[maxm];
void solve(){
    for (int i=1;i<=n;i++){
        scanf("%d%d",p+i,c+i);
    }
    for (int i=1;i<maxm;i++)dp[i] = inf;
    dp[0] = 0;
    for (int i=1;i<=n;i++){
        for (int j=c[i];j<maxm;j++){
            dp[j] = min(dp[j],dp[j-c[i]] + p[i]);
        }
    }
    int b = maxm-1;
    for (int i=maxm-1;i>=m;i--){
        if (dp[i] < dp[b]){
            b = i;
        }
    }
    cout<<dp[b]<<" "<<b<<endl;
}
int main(){
    while (scanf("%d%d",&n,&m) != EOF){
        solve();
    }
    return 0;
}
