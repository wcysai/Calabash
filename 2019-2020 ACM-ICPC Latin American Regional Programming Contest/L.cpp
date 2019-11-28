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

int n, m;
char g[1024][1024];
int ps[1024][1024];
bool seq[1024];

bool check(int sz) {
    for (int pos = 0; pos + sz <= m; pos++) {
        int cnt = 0;
        Rep (i, n) if (abs(ps[i][pos+sz] - ps[i][pos]) == sz) {
            cnt++;
            if (cnt >= sz) return true;
        } else {
            cnt = 0;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) scanf("%s", g[i] + 1);
    Rep (i, n) Rep (j, m) ps[i][j] = (g[i][j] == 'G' ? 1 : -1);
    Rep (i, n) partial_sum(ps[i] + 1, ps[i] + m + 1, ps[i] + 1);
    int l = 1, r = min(n, m) + 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (check(m)) l = m + 1;
        else r = m;
    }
    printf("%d\n", (l - 1) * (l - 1));
    return 0;
}
}
