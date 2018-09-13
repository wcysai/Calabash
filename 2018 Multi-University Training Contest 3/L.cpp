#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int a, b, c;
char r[512][512];

int main() {
  int T; cin >> T;
  while (T--) {
    cin >> a >> b >> c;
    memset(r, '.', sizeof r);
    int totr = (b + c) * 2 + 1, totc = (a + b)*2 + 1;
    rep (i, totr) r[i][totc] = 0;
    rep (i, c) {
      rep (j, a) {
        r[i<<1][j<<1] = '+';
        r[i<<1|1][j<<1] = '|';
        r[i<<1][j<<1|1] = '-';
      }
    }
    for (int i = c + c; i <= c + c + b + b; i++) {
      for (int col = i - c - c; col <= i - c - c + a + a; col++) {
        if (i&1) {
          if (col&1) r[i][col] = '/';
        } else {
          if (col&1) r[i][col] = '-'; else r[i][col] = '+';
        }
      }
    }
    for (int j = a + a ; j <= a + a + b + b; j++) {
      for (int i = j - a - a; i <= j -a -a + c + c; i++) {
        if (j & 1) {
          if (i&1) r[i][j] = '/';
        } else {
          if (i&1) r[i][j] = '|'; else r[i][j] = '+';
        }
      }
    }
    for (int i = totr - 1; i >= 0; i--) {
      cout << r[i] << endl;
    }
  }
  return 0;
}
