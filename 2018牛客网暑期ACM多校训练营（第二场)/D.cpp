#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int MOD = 1e9+7;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
typedef long long LL;
typedef pair<LL,LL> pll;
pll dp[maxn][3];
//0 not has 1 has
int n,a[maxn];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        for (int i=1;i<=n;i++){
            scanf("%d",a+i);
            dp[i][0] = {-INF,0LL};
            dp[i][1] = {-INF,0LL};
        }
        dp[0][0] = {0LL,0LL};
        dp[0][1]={-INF,0LL};
//        memset(dp,0,sizeof dp);
//        pll maxChoise={0,0};
        for (int i=1;i<=n;i++){
            if (dp[i-1][0].first>dp[i-1][1].first+a[i]){
                dp[i][0].first = dp[i-1][0].first;
                dp[i][0].second = dp[i-1][0].second;
            }else if (dp[i-1][0].first<dp[i-1][1].first+a[i]){
                dp[i][0].first = dp[i-1][1].first+a[i];
                dp[i][0].second = dp[i-1][1].second+1;
            }else{
                dp[i][0].first = dp[i-1][0].first;
                dp[i][0].second = min(dp[i-1][0].second,dp[i-1][1].second+1);
            }
            if (dp[i-1][1].first>dp[i-1][0].first-a[i]){
                dp[i][1].first = dp[i-1][1].first;
                dp[i][1].second = dp[i-1][1].second;
            }else if (dp[i-1][1].first<dp[i-1][0].first-a[i]){
                dp[i][1].first = dp[i-1][0].first-a[i];
                dp[i][1].second = dp[i-1][0].second +1;
            }else{
                dp[i][1].first = dp[i-1][1].first;
                dp[i][1].second = min(dp[i-1][1].second,dp[i-1][0].second +1);
            }
        }
        printf("%lld %lld\n",dp[n][0].first,dp[n][0].second);
    }
    return 0;
}
