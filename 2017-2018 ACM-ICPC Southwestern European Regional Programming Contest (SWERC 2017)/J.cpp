#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;

int n;
ll w[3], h[3];

int main() {
  scanf("%d", &n);
  Rep (i, n) {
    int ww; scanf("%d", &ww);
    w[i%3] += ww;
  }
  Rep (i, n) {
    int hh; scanf("%d", &hh);
    h[i%3] += hh;
  }
  ll ans[3] = {0};
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      ans[(i+j)%3] += w[i] * h[j];
  for (int i=0; i<3; i++) cout << ans[i] << ' ';
  return 0;
}
