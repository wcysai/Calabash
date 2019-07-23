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
 
int n, mod;
int x[100005];
 
int main() {
  while (scanf("%d%d", &n, &mod) != EOF) {
    if (mod == 1) {
      puts("0");
      continue;
    }
    x[0] = 1; x[1] = 0; x[2] = 1;
    for (int i = 3; i <= n; i++) {
      x[i] = (1ll * (i-1) * (x[i-1] + x[i-2]) + mod -
              1ll * (i-1) * (i-2) / 2 % mod * x[i-3] % mod) % mod;
//      x[i] %= mod;
    }
    printf("%d\n", x[n] % mod);
  }
  return 0;
}
