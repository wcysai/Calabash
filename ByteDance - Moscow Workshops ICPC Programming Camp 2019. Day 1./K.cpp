#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) ((void) 0)
#endif

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <=(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

typedef double _double;

int n;
LL mat[512][512];
_double arr[512];

int l1, r1, l2, r2;

double compute() {
    LL tot = mat[r1][r2] - mat[r1][l2] - mat[l1][r2] + mat[l1][l2];
    LL len = r1 - l1 + r2 - l2;
    return double(tot) / len / 2.0;
}

bool check2(_double th) {
    _double minv = arr[0];
    int minpos = 0;
    for (int i = 1; i <= n; i++) {
        if (arr[i] - minv >= th) {
            r2 = i;
            l2 = minpos;
            return true;
        }
        if (arr[i] < minv) {
            minv = arr[i];
            minpos = i;
        }
    }
    return false;
}

bool check(_double p) {
    for (int ll = 0; ll < n; ll++) {
        for (int rr = ll + 1; rr <= n; rr++) {
            for (int i = 0; i <= n; i++)
                arr[i] = (mat[rr][i] - mat[ll][i]) - p * i;
            if (check2(p * (rr - ll))) {
                l1 = ll;
                r1 = rr;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int kase = 0;
    while (scanf("%d", &n), n) {
        kase++;
        LL maxv = LLONG_MIN;
        int m1 = 0, m2 = 0;
        Rep (i, n) Rep (j, n) {
            scanf("%lld", &mat[i][j]);
            if (mat[i][j] > maxv) {
                maxv = mat[i][j];
                m1 = i;
                m2 = j;
            }
        }
        if (maxv <= 0) {
            printf("Case #%d: The maximal value is %.7f, rectangle corners are (%d, %d) and (%d, %d).\n",
                   kase,  maxv / 4.0, m2, m1, m2, m1);
            continue;
        }
        Rep (i, n) Rep (j, n)
            mat[i][j] += mat[i-1][j] + mat[i][j-1] - mat[i-1][j-1];
        _double l = maxv / 4.0 - 0.0001, r = maxv * n * 5.0;

        int cnt = 0;
        while (r - l >= 0.000005 and cnt <= 20) {
            cnt++;
            _double mid = (l + r) / 2;
            if (check(mid)) l = mid;
            else r = mid;
        }
        check(l);
        printf("Case #%d: The maximal value is %.7f, rectangle corners are (%d, %d) and (%d, %d).\n",
            kase, compute(), l2 + 1, l1 + 1, r2, r1);
    }
    return 0;
}
