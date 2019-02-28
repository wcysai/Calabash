#pragma GCC optimize(3)
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

int n1, n2;
char s1[4096], s2[4096];
int next1[4096][2], next2[4096][2];
int dp[4096][4096];
bool can[4096][4096];

inline void maketrans(int fi, int fj, int ti, int tj) {
    dp[ti][tj] = min(dp[ti][tj], dp[fi][fj] + 1); 
}

void compute_next(int n, char s[], int next[][2]) {
    rep (i, n) {
        rep (_, 2) {
            int cur = i;
            while (s[cur] - '0' == (_ ^ 1)) cur++;
            next[i][_] = cur + 1;
        }
    }
    next[n][0] = next[n][1] = next[n+1][0] = next[n+1][1] = n+1;
}

int main() {
    scanf("%s%s", s1, s2);
    n1 = strlen(s1); n2 = strlen(s2);
    compute_next(n1, s1, next1); compute_next(n2, s2, next2);
    memset(dp, 0x7f7f7f7f, sizeof dp); dp[0][0] = 0;
    rep (i, n1 + 2) rep (j, n2 + 2) rep (_, 2) 
        maketrans(i, j, next1[i][_], next2[j][_]);
    for (int i = n1 + 1; i >= 0; i--) {
        for (int j = n2 + 1; j >= 0; j--) {
            if (i == n1 + 1 and j == n2 + 1) {
                can[i][j] = true; 
            } else {
                rep (_, 2) {
                    if (dp[next1[i][_]][next2[j][_]] == dp[i][j] + 1 and
                        can[next1[i][_]][next2[j][_]]) can[i][j] = true;
                }
            }
        }
    }
    int i = 0, j = 0;
    while ((i != n1 + 1) or (j != n2 + 1)) {
        rep (_, 2) {
            if (can[next1[i][_]][next2[j][_]] and
                dp[next1[i][_]][next2[j][_]] == dp[i][j] + 1) {
                putchar('0' + _);
                i = next1[i][_];
                j = next2[j][_];
                break;
            }
        }
    }
    putchar('\n');
    return 0;
}
