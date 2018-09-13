#include <bits/stdc++.h>
using namespace std;

#define PROBLEM_NAME  "equal-squares"

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

typedef LL T;
typedef struct pt {
  T x, y;
  T operator,(pt a) { return x * a.x + y * a.y; }  // inner product
  T operator*(pt a) { return x * a.y - y * a.x; }  // outer product
  pt operator+(pt a) { return {x + a.x, y + a.y}; }
  pt operator-(pt a) { return {x - a.x, y - a.y}; }

  pt operator*(T k) { return {x * k, y * k}; }
  pt operator-() { return {-x, -y}; }

  bool operator == (pt a) {
    return x == a.x and y == a.y;
  }
} vec;

typedef pair<pt, pt> seg;

bool ptOnSeg(pt p, seg s) {
  vec v1 = s.first - p, v2 = s.second - p;
  return (v1, v2) <= 0 and v1 * v2 == 0;
}

// -1 outside the polygon
// 0  on the border of the polygon
// 1  inside the polygon
int ptOnPoly(pt p, pt* poly, int n) {
  int wn = 0;
  for (int i = 0; i < n; i++) {
    if (ptOnSeg(p, {poly[i], poly[i + 1]})) return 0;
    T k, d1 = poly[i].y - p.y, d2 = poly[i + 1].y - p.y;
    k = (poly[i + 1] - poly[i]) * (p - poly[i]);
    if (k > 0 && d1 <= 0 && d2 > 0) wn++;
    if (k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  return wn ? 1 : -1;
}

istream& operator>>(istream& lhs, pt& rhs) {
  lhs >> rhs.x >> rhs.y;
  return lhs;
}

istream& operator>>(istream& lhs, seg& rhs) {
  lhs >> rhs.first >> rhs.second;
  return lhs;
}

ostream& operator<<(ostream& lhs, pt& rhs) {
  lhs << rhs.x << ' ' << rhs.y;
  return lhs;
}

pt pts1[8], pts2[8];

bool identical(seg s, seg t) {
  return ((t.first - s.first) * (s.first - s.second) == 0) &&
         ((t.second - s.first) * (s.first - s.second) == 0);
}

bool test(seg s, pt poly[]) {
  bool pos = false, neg = false;
  LL val;
  rep (i, 4) {
    val = (s.first - s.second) * (poly[i] - s.first);
    if (val < 0) neg = true;
    if (val > 0) pos = true;
  }
  if (pos and neg) return false;
  return true;
}

bool same_dir(seg s1, seg s2) {
  return (s1.first - s1.second) * (s2.first - s2.second) == 0 and 
         ( (s1.second - s1.first), (s2.second - s2.first) ) > 0;
}

void special_test(int id1, int id2) {
  seg s11 { pts1[id1], pts1[(id1+1)%4] },
      s12 { pts1[id1], pts1[(id1+3)%4] },
      s21 { pts2[id2], pts2[(id2+1)%4] },
      s22 { pts2[id2], pts2[(id2+3)%4] };
  _debug("%d %d", id1, id2);
  if (same_dir(s11, s21) || same_dir(s11, s22) || 
      same_dir(s12, s21) || same_dir(s12, s22)) {
    return;
  } else throw 0;
}

void getRect(pt pts[]) {
  cin >> pts[0] >> pts[2];
  pt dif = pts[2] - pts[0], mid = pts[2] + pts[0];
  pts[0] = pts[0] * 2;
  pts[2] = pts[2] * 2;
  dif = pt{dif.y, -dif.x};
  pts[1] = mid + dif;
  pts[3] = mid - dif;
  pts[4] = pts[0];
}

vector<seg> segs;

int pa[10005];

int find(int x) {
  if (pa[x] == x) return x;
  return pa[x] = find(pa[x]);
}

void unite(int u, int v) {
  u = find(u); v = find(v);
  pa[u] = v;
}

int main() {
#ifndef __LOCAL_DEBUG__
  freopen(PROBLEM_NAME ".in", "r", stdin);
  freopen(PROBLEM_NAME ".out", "w", stdout);
#endif
  getRect(pts1);
  getRect(pts2);
  try {
    rep (i, 4) rep (j, 4) {
      if (pts1[i] == pts2[j]) special_test(i, j);
      else {
        seg s { pts1[i], pts2[j] };
        if (test(s, pts1) and test(s, pts2)) 
          segs.push_back(s);
      } 
    }
    int sz = segs.size();
    rep (i, sz) pa[i] = i;
    rep (i, sz) rep (j, sz) if (identical(segs[i], segs[j])) unite(i, j);
    int cnt = 0;
    rep (i, sz) if (pa[i] == i) cnt++;
    cout << cnt << endl;
  } catch (...) {
    cout << "Infinity" << endl;
  }
  return 0;
}
