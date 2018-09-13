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

int n;
int x[50005], y[50005];
int t[50005];

inline int lowbit(int x) { return x & -x; }

struct bit_purq {
  int N;
  vector<int> tr;

  void init(int n) {
    tr.resize(N = n + 5);
  }

  LL query(int n) {
    n++;
    int ans = 0;
    while (n) {
      ans = max(ans, tr[n]);
      n -= lowbit(n);
    }
    return ans;
  }

  void update(int n, int x) {
    n++;
    while (n < N) {
      tr[n] = max(tr[n], x);
      n += lowbit(n);
    }
  }
};

LL workx() {
  sort(t, t + n, [] (int a, int b) { return y[a] > y[b]; });
  bit_purq bit; bit.init(n);
  LL ans = 0;
  rep (i, n) {
    int id = t[i];
    ans += y[id] - bit.query(id);
    bit.update(id, x[id]);
  }
  return ans;
}


LL worky() {
  sort(t, t + n, [] (int a, int b) { return x[a] > x[b]; });
  bit_purq bit; bit.init(n);
  LL ans = 0;
  rep (i, n) {
    int id = t[i];
    ans += x[id] - bit.query(id);
    bit.update(id, y[id]);
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  rep (i, n) scanf("%d%d", x+i, y+i);
  reverse(x, x+n); reverse(y, y+n);
  rep (i, n) t[i] = i;
  cout << workx() + worky() << endl; 
  return 0;
}
