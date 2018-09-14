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

int n;
pt pts[1024];

double dist(pt p, int m) {
  static const double pi = acos(-1);
  double pol = arg(p);
  if (pol < 0.0) pol += 2 * pi;
  _debug("(%f, %f) pol=%f", real(p), imag(p), pol);
  double step = 2 * pi / m;
  double cur = 0.0;
  while (pol >= cur) cur += step;
  pt cpdir = polar(1.0, cur) - polar(1.0, cur - step);
//  pt cpsrc = polar(1.0, cur);
  return fabs(imag(p * conj(cpdir)) / abs(cpdir));
}

double fit[10];

int main() {
  cin >> n;  
  rep (i, n) {
    double x, y; cin >> x >> y;
    pts[i] = pt(x, y);
  }
  for (int m = 3; m <= 8; m++) {
    double dmin = 1e10, dmax = 0; 
    rep (i, n) {
      double dcur = dist(pts[i], m);
      dmin = min(dmin, dcur);
      dmax = max(dmax, dcur);
      _debug("m=%d, i=%d, d=%.7f", m, i, dcur);
    }    
    fit[m] = (dmin / dmax) * (dmin / dmax);
  }
  int cur = 0; double best = 0.0;
  for (int m = 3; m <=8; m++) {
    if (fit[m] > best) {
      best = fit[m];
      cur = m;
    }
  }
  printf("%d %.8f\n", cur, best);
  return 0;
}
