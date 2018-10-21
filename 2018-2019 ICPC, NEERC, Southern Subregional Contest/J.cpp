#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)

typedef long long LL;
typedef unsigned long long ULL;

char ch[200005];
int cnt[32];
bool dp[32][32768];
bool touched[32768];
int n, m, k;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        _debug("t=%d", t);
        scanf("%d%d%d", &n, &m, &k);
        LL ans = 1ll * n * m;
        assert(n <= 30000);
        scanf("%s", ch);
        memset(cnt, 0, sizeof cnt);
        rep (i, k) cnt[ch[i] - 'A' + 1]++;

        Rep (tt, 26) {
            for (int j = 0; j <= n + 2; j++) touched[j] = false;
            touched[0] = true;

            for (int i = 0; i <= 26; i++)
                for (int j = 0; j <= n + 2; j++)
                    dp[i][j] = false;
            dp[0][0] = true;

            Rep (i, 26) {
                rep (j, n) {
                    if (dp[i - 1][j]) {
                        dp[i][j] = true;
                        if (i == tt) continue;
                        int next = j + cnt[i];
                        if (next <= n) {
                            touched[next] = true;
                            dp[i][next] = true;
                        }
                    }
                }
            }

            int num = cnt[tt];
            for (int i = 0; i <= n; i++) {
                if (!touched[i]) continue;
                int tot = i + num;
                if (tot < n) continue;
                int a = n - i, b = tot - n - (k - n - m);
                _debug("tt=%d, i=%d, a=%d, b=%d", tt, i, a, b);
                if (b < 0) ans = 0;
                else ans = min(ans, 1ll * a * b);
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}
