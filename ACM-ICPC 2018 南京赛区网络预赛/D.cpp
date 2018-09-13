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

typedef complex<double> Point;

typedef pair<Point, Point> Halfplane;
const double EPS = 1e-9;
const double INF = 1e8;

inline int sgn(double n) {
  return fabs(n) < EPS ? 0 : (n < 0 ? -1 : 1);
}

inline double cross(Point a, Point b) {
  return (conj(a) * b).imag();
}

inline double dot(Point a, Point b) {
  return (conj(a) * b).real();
}

namespace halfplane {
  inline double satisfy(Point a, Halfplane p) {
    return sgn(cross(a - p.first, p.second - p.first)) <= 0;
  }

  Point crosspoint(const Halfplane &a, const Halfplane& b) {
    double k = cross(b.first - b.second, a.first - b.second);
    k = k / (k - cross(b.first - b.second, a.second - b.second));
    return a.first + (a.second - a.first) * k;
  }

  bool cmp(const Halfplane& a, const Halfplane &b) {
    int res = sgn(arg(a.second - a.first) - arg(b.second - b.first));
    return res == 0 ? satisfy(a.first, b) : res < 0;
  }

  vector<Halfplane> v;
  vector<Point> halfplaneIntersection() {
    sort(v.begin(), v.end(), cmp);
    deque<Halfplane> q;
    deque<Point> ans;
    q.push_back(v[0]);
    for (int i = 1; i < int(v.size()); ++i) {
      if (sgn(arg(v[i].second - v[i].first) - arg(v[i-1].second - v[i-1].first)
            ) == 0) continue;
      while (ans.size() > 0 && !satisfy(ans.back(), v[i])) {
        ans.pop_back();
        q.pop_back();
      }
      while (ans.size() > 0 && !satisfy(ans.front(), v[i])) {
        ans.pop_front();
        q.pop_front();
      }
      ans.push_back(crosspoint(q.back(), v[i]));
      q.push_back(v[i]);
    }
    while (ans.size() > 0 && !satisfy(ans.back(), q.front())) {
      ans.pop_back();
      q.pop_back();
    }
    while (ans.size() > 0 && !satisfy(ans.front(), q.back())) {
      ans.pop_front();
      q.pop_front();
    }
    ans.push_back(crosspoint(q.back(), q.front()));
    return vector<Point>(ans.begin(), ans.end());
  }
  
  double r;
  void add_hp(Point a, Point b) {
    Point tvec = (b - a) * Point(0.0, 1.0);
    tvec *= r / abs(tvec);
//    cout << tvec << endl;
    v.push_back({a + tvec, b + tvec});
  }

  vector<Point> init() {
    v.clear();
    int n, R; scanf("%d%d", &n, &R); r = R; 
    vector<pair<int, int>> pts(n);
    rep (i, n) scanf("%d%d", &pts[i].first, &pts[i].second);
    pts.push_back(pts[0]);
    reverse(range(pts));
    rep (i, n) {
      add_hp({(double)pts[i].first, (double)pts[i].second},
             {(double)pts[i+1].first, (double)pts[i+1].second});
    }
    return halfplaneIntersection();
  }
}

vector<Point> pts;

inline double area(Point s, Point t, Point p) {
  return cross(t - s, p - s);
}

double get_ans() {
  int n = pts.size();
  pts.resize(n+n);
  rep (i, n) pts[i+n] = pts[i];
  pts.insert(pts.end(), range(pts));
  pts.push_back(pts[0]);

  int l, p, cur, r;
  double ans = 0.0;
  for (l = 0; l < n; l++) {
    r = l + n;
    cur = l + 2;
    for (p = l + 1; p < r; p++) {
      while (cur <= l) cur++;
      while (cur < r && area(pts[l], pts[p], pts[cur]) < 
          area(pts[l], pts[p], pts[cur+1])) 
        cur++;
      ans = max(ans, area(pts[l], pts[p], pts[cur]));
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
     pts = halfplane::init();
//     cout << pts.size() << endl;
//     for (auto pt : pts) cout << pt << endl;
     printf("%.7f\n", get_ans());
  }
  return 0;
}
