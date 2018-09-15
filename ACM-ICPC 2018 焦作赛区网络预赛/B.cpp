#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, m, k;

typedef LL (*func)(LL, LL);
map<char, func> mp = {
        {'+', [](LL a, LL b) -> LL {return a + b;}},
        {'-', [](LL a, LL b) -> LL {return a - b;}},
        {'*', [](LL a, LL b) -> LL {return a * b;}},
        {'/', [](LL a, LL b) -> LL {return a / b;}},
};

LL dpu[1024][6], dpd[1024][6];
LL a[1024];
func funcs[6];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        Rep (i, n) {
            int x; scanf("%d", &x);
            a[i] = x;
        }
        char ops[12];
        scanf("%s", ops);
        Rep (i, m) funcs[i] = mp[ops[i - 1]];
        memset(dpu, 0, sizeof dpu);
        memset(dpd, 0, sizeof dpd);
        dpu[0][0] = dpd[0][0] = k;
        Rep (i, n) {
            Rep (j, min(m, i)) {
                if (j < i) {
                    dpu[i][j] =
                            max({
                                        dpu[i - 1][j],
                                        funcs[j](dpu[i - 1][j - 1], a[i]),
                                        funcs[j](dpd[i - 1][j - 1], a[i])
                                });
                    dpd[i][j] =
                            min({
                                        dpd[i - 1][j],
                                        funcs[j](dpu[i - 1][j - 1], a[i]),
                                        funcs[j](dpd[i - 1][j - 1], a[i])
                                });
                } else {
                    dpu[i][j] =
                            max({
                                        funcs[j](dpu[i - 1][j - 1], a[i]),
                                        funcs[j](dpd[i - 1][j - 1], a[i])
                                });
                    dpd[i][j] =
                            min({
                                        funcs[j](dpu[i - 1][j - 1], a[i]),
                                        funcs[j](dpd[i - 1][j - 1], a[i])
                                });
                }
                assert(dpu[i][j] >= dpd[i][j]);
            }
            dpu[i][0] = dpu[i - 1][0];
            dpd[i][0] = dpd[i - 1][0];
        }
        cout << dpu[n][m] << endl;
    }
    return 0;
}
