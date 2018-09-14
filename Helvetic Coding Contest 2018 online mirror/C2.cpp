#include <bits/stdc++.h>
using namespace std;

#define DEBUG(fmt, ...) fprintf(stderr, "%s: " fmt "\n", __func__, ##__VA_ARGS__)
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int n, k, p;
int a[20005];
int dp[20005][52][102];

int main() {
  cin >> n >> k >> p;
  rep (i, n) {
    cin >> a[i];
    a[i] %= p;
  }
  for (int i=0; i<=n; i++)
  for (int kk=0; kk<=k; kk++)
  for (int pp=0; pp < p; pp++)
    dp[i][kk][pp] = (i == 0 && kk == 0 && pp == 0) ? 0 : INT_MIN;
  
  rep (i, n) {
    rep (kk, k) {
      rep (pp, p) {
        auto &cur = dp[i+1][kk][(pp+a[i])%p];
        cur = max(cur, dp[i][kk][pp]);
//        DEBUG("i=%d, kk=%d, pp=%d, a[i]=%d, cur=%d", i, kk, pp, a[i], cur);
        auto &cur2 = dp[i+1][kk+1][0];
        cur2 = max(cur2, dp[i][kk][pp] + (pp + a[i])%p);
      }
    }
  }
  cout << dp[n][k][0] << endl;
  return 0;
}
