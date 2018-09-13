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

typedef complex<double> pt;
const double g = 9.8, pi = acos(-1);
double a, b, x, y, ang;
int cnt;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    cin >> a >> b >> x >> y; a = -a;
//    _debug("a=%f, b=%f, x=%f, y=%f", a, b, x, y);
    pt pos(x, x*b/a), v(0, -sqrt(2*g*(y-x*b/a)));
    ang = arg(pt(a, b)) - pi / 2;
    cnt = 1;
//    cerr << pos << ' ' << v << ' ' << ang << endl;
    do {
      // reflex the speed
      v = polar(abs(v), ang+ang-arg(v));
      double t = 2 * (imag(v) - b / a * real(v)) / g;
      double dy = imag(v) * t - g * t * t / 2;
      pos += pt(real(v) * t, dy);
      v -= pt(0, g * t);
      if (real(pos) < 0) cnt++;
    } while (real(pos) < 0);
    cout << cnt << endl;
  }
  return 0;
}
