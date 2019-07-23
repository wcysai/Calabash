#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int MOD = 1e9+7;
typedef long long LL;
LL dp[maxn][2];
LL sum[maxn];
int k,q;
int main(){
    scanf("%d%d",&q,&k);
    dp[0][0]=1;
    for (int i=1;i<maxn;i++){
        dp[i][0] = (dp[i-1][0]+dp[i-1][1])%MOD;
        if (i>=k){
            dp[i][1] = dp[i-k][0];
        }
        sum[i] = sum[i-1]+dp[i][0]+dp[i][1];
        sum[i]%=MOD;
    }
    while (q--){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",(sum[r]-sum[l-1]+MOD)%MOD);
    }
    return 0;
}
