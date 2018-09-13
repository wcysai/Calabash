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

int n;
int x[1024];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    memset(x, 0, sizeof x);
    x[0] = 1;
    while (n--) {
      rep (i, 1000) {
        x[i] <<= 1;
      }
      rep (i, 1000) {
        x[i+1] += x[i] / 10;
        x[i] %= 10;
      }
    }
    int ptr = 1023;
    while (x[ptr] == 0) ptr--;
    while (ptr >= 0) putchar('0'+x[ptr--]);
    puts("");
  }
  return 0;
}
