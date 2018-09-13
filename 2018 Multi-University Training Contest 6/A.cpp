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

template <typename T>
double simpson(const T &f, double a, double b, int n) {
  const double h = (b - a) / n;
  double ans = f(a) + f(b);
  for (int i = 1; i < n; i += 2) ans += 4*f(a+i*h);
  for (int i = 2; i < n; i += 2) ans += 2*f(a+i*h);
  return ans * h / 3;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    double a, b; cin >> a >> b;
    double ans = (2 * b + a * acos(-1));
//    cout << ans << endl;
    ans = double(LL(ans * 1000000)) / 1000000;
    printf("%.6f\n", ans);
  }
  return 0;
}
