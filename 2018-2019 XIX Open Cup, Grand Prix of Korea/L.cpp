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

int n;
int a[100005], to[100005];
int num[100005], bad[100005];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i);
    int l = 0;
    while (l < n) {
        if (l == n - 1) to[l++] = n;
        else {
            int r = max(is_sorted_until(a + l, a + n),
                        is_sorted_until(a + l, a + n, greater_equal<int>())) - a;
            for (; l < r - 1; l++) to[l] = r;
        }
    }
    int q; scanf("%d", &q);
    while (q--) {
        int mr; scanf("%d", &mr);
        if (num[mr]) {
            printf("%d %d\n", num[mr], bad[mr]);
            continue;
        }
        int ptr = 0, cnum = 0, cbad = 0;
        while (ptr < n) {
            int next = to[ptr];
            cnum++;
            if (next - ptr < mr) next = min(ptr + mr, n);
            cbad += max(0, next - to[ptr]);
            ptr = next;
        }
        num[mr] = cnum; bad[mr] = cbad;
        printf("%d %d\n", cnum, cbad);
    }
    return 0;
}
