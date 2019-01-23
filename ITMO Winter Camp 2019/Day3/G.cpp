#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define maxn 605
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
const int BLOCK = 16;
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
char s[maxn];
int dig[maxn];
int dig_t[maxn];
int n,m;
int cnt[maxn][2];
int ans = INT_MAX;
void gen(int mask){
    for (int i=1;i<=m;i++){
        dig_t[i] = mask & 1;
        mask >>= 1;
    }
    for (int i=m+1;i<=n;i++){
        dig_t[i] = dig_t[i-m];
    //    dig_t[i] ^= dig[i];
    }
    for (int i=1;i<=n;i++){
        dig_t[i] ^= dig[i];
    }

}
int dp[maxn][2];
int dp_job(){
    //memset(dp,inf,sizeof dp);
    dp[n+1][0] = dp[n+1][1] = 0;
    for (int i=n;i>=1;i--){
        // not fiip
        dp[i][0] = dp[i+1][0];
        dp[i][1] = dp[i+1][1];
        if (dig_t[i]){
            dp[i][0] ++;
        }else{
            dp[i][1] ++;
        }
        // flip
        if (i % m == 0 || i == n){
            if (dig_t[i]){
                dp[i][0] = min(dp[i][0],1 + dp[i+1][1] +1);
                dp[i][1] = min(dp[i][1],1 + dp[i+1][0]);
            }else{
                dp[i][0] = min(dp[i][0],1 + dp[i+1][1]);
                dp[i][1] = min(dp[i][1],1 + dp[i+1][0] + 1);
            }
        }
    }
    return min(dp[1][0],dp[1][1]);
}
void work_short(){
    for (int i=0;i< (1<< m);i++){
        gen(i);
        ans = min(ans,dp_job());
    }
}
void long_job(int mask,int seg_num){
    for (int i=1;i<=n;i++){
        dig_t[i] = dig[i];
    }
    int temp_ans = __builtin_popcount(mask);
    for (int i=1;i<=seg_num;i++){
        int flag = mask & 1;
        mask >>= 1;
        if (flag){
            for (int j=1;j<=min(n,m * i);j++){
                dig_t[j] ^=1;
            }
        }
    }
    memset(cnt,0,sizeof cnt);
    for (int i=1;i<=n;i++){
        //temp_ans += dig_t[i];
        cnt[i%m][dig_t[i]] ++;
    }
    for (int i=0;i<m;i++){
        temp_ans += min(cnt[i][0],cnt[i][1]);
    }
    ans = min(ans,temp_ans);
}
void work_long(){
    int seg_num = (n+m-1) / m;
    for (int mask = 0;mask < (1 << seg_num); mask ++){
        long_job(mask,seg_num);
    }
}
int main()
{
    scanf("%s",s+1);
    n = strlen(s+1);
    scanf("%d",&m);
    for (int i=1;i<=n;i++){
        dig[i] = s[i] == '1';
    }
    if (m <= BLOCK){
        work_short();
    }else{
        work_long();
    }
    cout<<ans<<endl;
    return 0;
}

