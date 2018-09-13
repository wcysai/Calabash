#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define PROBLEM_NAME  "stats"

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

constexpr double EPS = 1e-7;

int fcmp(double x, double y = 0.0) {
  if (fabs(x - y) < EPS) return 0;
  return x < y ? -1 : 1;
}

double m, s, h;
int n;
double x[20];

double cont(double x) { return (x - m) * (x - m); }

double qsolve(double a, double b, double c) {
//  assert(fcmp(b * b, 4 * a * c) >= 0);
  return (-b + sqrt(max(b*b - 4*a*c, 0.0))) / (2*a);
}

bool check() {
  rep (i, n) if (fcmp(x[i], 0.0) < 0 or fcmp(x[i], 100.0) > 0) return false;
  return true;
}

void print() {
//  assert(0);
//#ifdef __LOCAL_DEBUG__
  rep (i, n) cout << x[i] << ' ';
  cout << endl;
  double mean = 0.0, stdevn = 0.0;
  rep (i, n) mean += x[i] / n;
  rep (i, n) stdevn += pow(x[i] - m, 2);
  _debug("mean = %.8f, stdev * n = %.8f, tar = %.8f", mean, stdevn,
      s * s * n);
  rep (i, n-1) assert(fcmp(x[i], x[i+1]) <= 0);
  
  assert(fcmp(mean, m) == 0);
  assert(fcmp(x[n/2], h) == 0);
  assert(fcmp(s * s * n, stdevn) == 0);
 
//#endif
}

bool attempt() {
  rep (i, n) x[i] = h;
  double delta = n * (m - h) / (n / 2);
  if (delta < 0) for (int i = 0; i < n / 2; i++) x[i] += delta;
  else for (int i = n / 2 + 1; i < n; i++) x[i] += delta;
//  rep (i, n) printf("%.9f ", x[i]);
//  puts("");
//  assert(fcmp(accumulate(x, x+n, 0.0), n * m) == 0);
  if (check() == false) return false;
  int mid = n / 2, l = 0, r = n - 1;
  while (l < mid && fcmp(x[l], 0) <= 0) l++;
  while (r > mid && fcmp(x[r], 100.0) >= 0) r--;
  double se = 0.0, tar = s * s * n;
  rep (i, n) se += cont(x[i]);
//  _debug("se/n=%f, tar=%f", se/n, s*s);
  if (fcmp(se, tar) > 0) return false;
  if (fcmp(se, tar) == 0) return true;
// _debug("%d ~ %d", l, r);
  while (l < r) {
//    print();
    double news = se, delta;
    double ldec = x[l] - (l < mid ? 0 : h), rinc = (r <= mid ? h : 100) - x[r];
    delta = min(ldec, rinc);
    news -= cont(x[l]) + cont(x[r]);
    x[l] -= delta; x[r] += delta;
    news += cont(x[l]) + cont(x[r]);
    if (fcmp(news, tar) < 0) {
      se = news;
      if (ldec < rinc) l++; else r--;
    } else {
      news -= cont(x[l]) + cont(x[r]);
      x[l] += delta; x[r] -= delta;
      double sd = tar - news;
      delta = qsolve(2.0, 2 * (x[r] - x[l]), 
          pow(m - x[l], 2) + pow(m - x[r], 2) - sd);
      x[l] -= delta; x[r] += delta;
      return true;
    }
  }
  return false;
}

double ctots(int n) {
  double ans = 0.0;
  rep (i, n) ans += cont(x[i]);
  return ans;
}

pair<double, double> sbnd(int n) {
  double minv, maxv;
  rep (i, n) x[i] = h;
  double del = (m - h) * n / (n / 2);
  if (del < 0) rep (i, n / 2) x[i] += del;
  else for (int i = n / 2 + 1; i < n; i++) x[i] += del;

//  rep (i, n) cout << x[i] << ' ' ; cout << endl;
  rep (i, n) {
    if (x[i] < 0.0 || x[i] > 100.0) throw 0;
  }
  minv = ctots(n);  

  if (x[0] < 100.0 - x[n-1]) {
    double acc = 0;
    rep (i, n / 2) {
      acc += x[0];
      x[0] = 0;
    }
    for (int i = n - 1; fcmp(acc, 0) > 0; i--) {
      if (100.0 - x[i] <= acc) {
        x[i] += acc;
        break;
      } else {
        acc -= 100.0 - x[i];
        x[i] = 100.0;
      }
    }
  } else {
    double acc = 0;
    for (int i = n / 2 + 1; i < n; i++) {
      acc += 100.0 - x[i];
      x[i] = 100.0;
    }
    for (int i = 0; fcmp(acc, 0) > 0; i++) {
      if (x[i] >= acc) {
        x[i] -= acc;
        break;
      } else {
        acc -= x[i];
        x[i] = 0;
      } 
    } 
  }
  maxv = ctots(n);
  return {minv, maxv};
}

void checkbnd() {
  double minv = DBL_MAX, maxv = DBL_MIN;
  for (int i = 3; i < 20; i += 2) {
    try {
      double l, r; tie(l, r) = sbnd(i);
      minv = min(minv, l) / i;
      maxv = max(maxv, r) / i;
      _debug("%.8f ~ %.8f", l, r);
    } catch (...) {

    }
  }
  if (minv == DBL_MAX) return;
  if ((s * s >= minv && s * s  <= maxv)) {
    _debug("[%.8f, %.8f], but not found!", minv, maxv); 
    exit(0);
  }
}

int cnt = 0;
void work() {
  for (n = 3; n < 20; n += 2) {
    if (attempt()) { 
      printf("%d", n);
      rep (i, n) printf(" %.9f", x[i]);
      puts("");
    //  print();
      return;
    }
  }
  puts("-1");
//  checkbnd();
  cnt++;
}


int main() {
#ifndef __LOCAL_DEBUG__
  freopen(PROBLEM_NAME ".in", "r", stdin);
  freopen(PROBLEM_NAME ".out", "w", stdout);
#endif

#if 0 
  rep (mm, 101) rep (ss, 101) rep(hh, 101) {
    _debug("%d %d %d", mm, ss, hh);
//    memset(x, 0, sizeof x);
    m = mm; s = ss; h = hh;
    work();
  }
  cout << cnt << endl;
  return 0;
#endif
  int T; scanf("%d", &T);
  while (T--) {
    int mm, ss, hh; scanf("%d%d%d", &mm, &ss, &hh);
    m = mm; s = ss; h = hh;
    work();
  }
  return 0;
}
