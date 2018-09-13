#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
char s[N];
int n;
int dp[N][15], L, R;
int ans, l, r;
inline int read(){
    int ret =0;
    char ch = getchar();
    while (ch<'0'||ch>'9')ch = getchar();
    while (ch>='0'&&ch<='9')ret = ret*10+ch-'0',ch = getchar();
    return ret;
}
void find(int &l, int &r, int u, int mx) {
    if(u == 0)return;
    int pos = (mx <= L)? (mx): (mx <= R + 1? (R - (mx - L - 1)): mx - 2);
    if (s[u] == pos) {
        if(dp[u][mx] == dp[u - 1][mx] + 1){
            find(l, r, u - 1, mx);
        } else {
            if (mx == 2 + R){
                r = u;
            }else if (mx == L + 1){
                l = u + 1;
            }
            find(l, r, u, mx - 1);
        }
    }
    else {
        if (dp[u][mx] == dp[u - 1][mx]) {
            find(l, r, u - 1, mx);
        } else {
            if (mx == 2 + R){
                r = u;
            }else if (mx == L + 1){
                l = u + 1;
            }

            find(l, r, u, mx - 1);
        }
    }
}
void work() {
    for(int i = 1; i <= n; i++) {
        for (int j = 0; j <= 11; j++) {
            int temp = 0;
            if (j <= L) temp = j;
            else if (j <= R + 1) temp = R - (j - L - 1);
            else temp = j - 2;
            if (s[i] == temp)
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j] + 1);
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    }
    int l = 1,r = 1;
    find(l, r, n, 11);
    if (dp[n][11] > ans) {
        ans = dp[n][11];
        ::l = l;
        ::r = r;
    }
}
void solve(){
    n = read();
//        scanf("%d",&n);
    scanf("%s",s + 1);
    for(int i=1;i<=n;i++)s[i]-='0';
    ans = 0;
    for (L = 0; L <=8; ++L) {
        for (R = L + 1; R <=9; ++R) {
            work();
        }
    }
    printf("%d %d %d\n", ans, l, r);
}
int main() {
    for(int T=read(); T; T--) {
        solve();
    }
    return 0;
}
