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
 
const double EPS = 1e-10;
 
int dcmp(double x) {
  if (fabs(x) < EPS) return 0;
  if (x > 0) return 1;
  return -1;
}
 
const double PI = acos(-1);
 
struct point {
  double x, y;
   
  point operator + (point pt) const { return {x + pt.x, y + pt.y}; }
  point operator - (point pt) const { return {x - pt.x, y - pt.y}; }
  double operator , (point pt) const { return x * pt.x + y * pt.y; }
  double operator * (point pt) const { return x * pt.y - y * pt.x; }
  point operator * (double k) const { return {x*k, y*k}; }
  point operator / (double k) const { return {x/k, y/k}; }
  double abs() { return hypot(x, y); }
};
 
point crosspt(point a, point b, point p, point q) {
  double a1 = (b-a)*(p-a), a2 = (b-a)*(q-a);
  return (p*a2-q*a1)/(a2-a1);
}
 
point res[500];
double r;
int n;
 
inline double mysqrt(double x) { return sqrt(max(0.0, x)); }
 
double sector_area(point a, point b) {
  double theta = atan2(a.y, a.x) - atan2(b.y, b.x);
  while (theta <= 0) theta += 2*PI;
  while (theta > 2*PI) theta -= 2*PI;
  theta = min(theta, 2*PI-theta);
  return r*r*theta/2;
}
 
inline double sqr(double x) { return x*x;}
 
inline void circle_cross_line(point a, point b, point o, double r,
    point ret[], int& num) {
  double x0 = o.x, y0 = o.y;
  double x1 = a.x, y1 = a.y;
  double x2 = b.x, y2 = b.y;
  double dx = x2 - x1, dy = y2 - y1;
  double A  = dx*dx + dy*dy;
  double B  = 2*dx*(x1-x0) + 2*dy*(y1-y0);
  double C  = sqr(x1-x0)+sqr(y1-y0)-sqr(r);
  double delta = B*B-4*A*C;
  num = 0;
  if (dcmp(delta) >= 0) {
    double t1 = (-B-mysqrt(delta)) / (2*A);
    double t2 = (-B+mysqrt(delta)) / (2*A);
    if (dcmp(t1 - 1) <= 0 && dcmp(t1) >= 0) {
      ret[num++] = {x1+t1*dx, y1+t1*dy};
    }
    if (dcmp(t2 - 1) <= 0 && dcmp(t2) >= 0) {
      ret[num++] = {x1+t2*dx, y1+t2*dy};
    }
  }
}
 
double calc(point a, point b) {
  point p[2];
  int num = 0;
  int ina = dcmp(a.abs() - r) < 0;
  int inb = dcmp(b.abs() - r) < 0;
  if (ina) {
    if (inb) {
      return fabs(a*b)/2.0;
    } else {
      circle_cross_line(a, b, {0,0}, r, p, num);
      return sector_area(b, p[0]) + fabs(a * p[0]) / 2.0;
    }
  } else {
    if (inb) {
      circle_cross_line(a, b, {0,0}, r, p, num);
      return sector_area(p[0], a) + fabs(p[0]*b) / 2.0;
    } else {
      circle_cross_line(a, b, {0,0}, r, p, num);
      if (num == 2) {
        return sector_area(a, p[0]) + sector_area(p[1], b)
          + fabs(p[0] * p[1]) / 2.0;
      } else {
        return sector_area(a, b);
      }
    }
  }
}
 
double area() {
  double ret = 0.0;
  for (int i = 0; i < n; i++) {
    int sgn = dcmp(res[i] * res[i+1]);
    if (sgn != 0) {
      ret += sgn * calc(res[i], res[i+1]);
    }
  }
  return ret;
}
 
double polyarea;
point poly[500];
 
int main() {
  scanf("%d", &n);
  rep (i, n) scanf("%lf%lf", &(poly[i].x), &(poly[i].y));
  for (int i = 2; i < n; i++)
    polyarea += (poly[i-1] - poly[0]) * (poly[i] - poly[0]);
  polyarea /= 2.0;
  if (polyarea < 0.0) {
    reverse(poly, poly+n);
    polyarea = -polyarea;
  }
  poly[n] = poly[0];
  int m; scanf("%d", &m);
  rep (i, m) {
    double x, y, p, q; scanf("%lf%lf%lf%lf", &x, &y, &p, &q);
    p /= q;
     p = 1 - p;
    // translate the polygon
    for (int i = 0; i <= n; i++) {
      res[i] = poly[i] - point{x, y};
    }
 
 
    double lr = 0.0, rr = 1e7;
    while (rr - lr > 1e-7) {
      r = (lr + rr) / 2;
      double a = area();
      _debug("r=%f pa=%f ia=%f", r, polyarea, a);
      if (a / polyarea < p) {
        lr = r;
      } else {
        rr = r;
      }
    }
    printf("%.10f\n", r);
  }
  return 0;
}
