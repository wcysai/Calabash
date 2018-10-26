#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug() ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, m, mod;
int c[1 << 20];
int last_pos;

struct matrix {
    int a[5][5];

    void set_identity() {
        rep (i, m) rep (j, m) a[i][j] = (i == j);
    }

    matrix operator * (const matrix& rhs) {
        LL tmp[5][5] = {0};
        matrix ans;
        rep (i, m) rep (j, m) rep (k, m) {
            tmp[i][k] += LL(a[i][j]) * rhs.a[j][k];
        }
        rep (i, m) rep (j, m) ans.a[i][j] = tmp[i][j] % mod;
        return ans;
    }

    void print() {
        rep (i, m) {
            rep (j, m) {
                printf("%d%c", a[i][j], j == m - 1 ? '\n' : ' ');
            }
        }
    }
} A, B, I;

matrix pref[1 << 20], suf[1 << 20], res[1 << 20];

void commit(int pos) {
    suf[pos] = I;
    for (int i = pos - 1; i > last_pos; i--)
        suf[i] = res[i] * suf[i + 1];
    last_pos = pos;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &mod) != EOF) {
        last_pos = 0;
        I.set_identity();
        rep (i, m) rep (j, m) scanf("%d", &(A.a[i][j]));
        rep (i, m) rep (j, m) scanf("%d", &(B.a[i][j]));
        Rep (i, n) scanf("%d", c + i);
        res[0] = pref[0] = A;
        suf[0] = I;
        Rep (i, n) {
            if (c[i] > last_pos) {
                commit(i);
                pref[i] = res[i] = suf[c[i]] * B;
            } else {
                res[i] = suf[c[i]] * pref[i - 1] * B;
                pref[i] = pref[i - 1] * res[i];
            }

        }
        /*
        rep (i, n) {
            printf("matrix  %d\n", i);
            res[i].print();
        }
         */
        res[n].print();
    }
    return 0;
}

/*
2 2 1000000000
1 1
0 1
1 0
0 1
0 0

 5 2 1000000000
1 1
0 1
1 0
0 1
0 1 2 3 4

 */
