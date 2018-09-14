#include <bits/stdc++.h>
using namespace std;

#define DEBUG(fmt, ...) fprintf(stderr, "%s: " fmt "\n", __func__, ##__VA_ARGS__)
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int n;

struct obj {
  short x, y;
  short type, id;
} objs[20005];

int perm[20005];
int psum[20005];

void sol(int l, int r) {
  if (r - l == 2) {
    if (objs[l].type == 1) perm[objs[l].id] = objs[l+1].id;
    else perm[objs[l+1].id] = objs[l].id;
    return ;
  }
  
  swap(objs[l], *min_element(objs+l, objs+r,
        [] (const obj& lhs, const obj& rhs) {
          return lhs.x < rhs.x;
        }));

  sort(objs+l+1, objs+r, [=] (const obj& lhs, const obj& rhs) {
      return (lhs.y-objs[l].y) * (rhs.x - objs[l].x) < 
             (rhs.y-objs[l].y) * (lhs.x - objs[l].x);
    });

  psum[l] = objs[l].type;
  vector<int> pos;
  for (int i=l+1; i<r; i++) {
    psum[i] = psum[i-1] + objs[i].type;
    if (psum[i] == 0) pos.push_back(i+1);
  }
  int last = l;
  if (pos.size() == 1) {
    swap(objs[r-1], objs[l+1]);
    sol(l, l+2);
    sol(l+2, r);
  } else {
    for (int p : pos) {
      sol(last, p);
      last = p;
    }
  }
}

int main() {
  srand(time(NULL));
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> objs[i].x >> objs[i].y;
    objs[i].x += 10005; objs[i].y += 10005;
    objs[i].type = 1; objs[i].id = i + 1;
  }
  for (int i=n; i<n+n; i++) {
    cin >> objs[i].x >> objs[i].y;
    objs[i].x += 10005; objs[i].y += 10005;
    objs[i].type = -1; objs[i].id = i + 1 - n;
  }
  sol(0, n+n);
  for (int i=1; i<=n; i++) cout << perm[i] << endl;
  return 0;
}
