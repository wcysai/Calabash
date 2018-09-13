// Code Header
// Created by calabash_boy on 18-7-6.
//
#include <bits/stdc++.h>
#define F first
#define S second
#define PB(x) push_back(x)
#define debug(x) cout<<"[debug] "<<#x<<":"<<x<<endl;
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
const int maxn = 1e5+100;
const int MOD = -1;
LL dp[maxn][2], fp[maxn], tdp[maxn];
const int INF = 0x3f3f3f3f;
int n;
char s[maxn], t[maxn], a[maxn], b[maxn];
inline void Min(LL &x,LL b) {
    x = min(x,b);
}
void pre_proc(){
    for(int i = 1; i <= n; ++i){
        if(a[i] == '0'){
            fp[i] = 1;
        } else {
            fp[i] = fp[i - 1] == -1? fp[i - 1]: (fp[i - 1] << 1);
            Min(fp[i], INF);
        }
        if(b[i] == '0'){
            tdp[i] = 1;
        }else{
            tdp[i] = tdp[i - 1] == -1? tdp[i - 1]: (tdp[i - 1] << 1);
            Min(tdp[i], INF);
        }
    }
}
void work_dp(){
    for(int i = 1;i <= n + 1; ++i) {
        dp[i][0] = dp[i][1] = INF;
    }
    for(int i = 1; i <= n; ++i){
        if(s[i] == '0') {
            Min(dp[i][0], dp[i - 1][0]);
            if(fp[i] != -1) {
                Min(dp[i][0], dp[i - 1][1] + fp[i]);
            }
        } else {
            if(fp[i] != -1) {
                Min(dp[i][0], dp[i - 1][0] + fp[i]);
            }
        }


        if(t[i] == '0') {
            Min(dp[i][1], dp[i - 1][1]);
            if(tdp[i] != -1){
                Min(dp[i][1], dp[i - 1][0] + tdp[i]);
            }
        } else {
            if(tdp[i] != -1) {
                Min(dp[i][1], dp[i - 1][1] + tdp[i]);
            }
        }
    }
}
void solve(){
    scanf("%d", &n);
    scanf("%s%s%s",s+1,a+1,b+1);
    for(int i = 1;i <= n; ++i) {
        t[i] = '1' + '0' - s[i];
    }
    t[1] ++;
    for(int i = 1;i <= n; ++i) {
        if(t[i] == '2') {
            t[i] = '0';
            t[i + 1] ++;
        }
    }
    t[n + 1] = 0;
    fp[0] = tdp[0] = -1;
    pre_proc();
    work_dp();
    printf("%lld\n", min(dp[n][0], dp[n][1] + 1));
}
int main(){
    int T;
    for (scanf("%d", &T); T;T--) {
        solve();
    }
    return 0;
}
