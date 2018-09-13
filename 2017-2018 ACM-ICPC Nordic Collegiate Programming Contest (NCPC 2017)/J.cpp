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

int main() {
  int l, r; cin >> l >> r;
  if (l == 0 && r == 0) {
    printf("Not a moose\n");
  } else if (l == r ) {
    printf("Even %d\n", l + r);
  } else {
    printf("Odd %d\n", 2*max(l, r));
  }
  return 0;
}
