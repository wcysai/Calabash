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

int query(int a, int b, int c) {
  printf("? %d %d %d\n", a, b, c);
  fflush(stdout);
  int ret; scanf("%d", &ret);
  return ret;
}

int n;
int ord[5120];
int perm[5120], invp[5120];

int get_zero() {
  random_shuffle(ord, ord + n);
  set<int> cand;
  for (int i = 0; i < n; i += 2) {
    int u = i, v = (i + 1) % n;
    if (query(u, v, 0) == 0) {
      cand.insert(u);
      cand.insert(v);
    }
  }
  while (cand.size() > 1) {
    set<int> res;
    for (int x : cand) 
      if (query(x, rand() % n, 0) == 0)
        res.insert(x);
    cand = move(res);
  }
  return *(cand.begin());
}

int get_one() {
  random_shuffle(ord, ord + n);
  set<int> cand;
  for (int i = 0; i < n; i += 2) {
    int u = i, v = (i + 1) % n, res = query(u, v, invp[0]);
    if (res == u) cand.insert(v);
    if (res == v) cand.insert(u);
  }
  while (cand.size() > 1) {
    set<int> res;
    for (int x : cand) {
      int r = rand() % n;
      if (query(x, r, invp[0]) == r) res.insert(x);
    }
    cand = move(res);
  }
  return *(cand.begin());
}

int main() {
  srand(time(NULL));
  scanf("%d", &n);
  if (n == 1) {
    printf("! 0\n");
    return 0;
  }
  rep (i, n) ord[i] = i;
  invp[0] = get_zero();
  _debug("zero is at %d", invp[0]);
  invp[1] = get_one();
  _debug("one is at %d", invp[1]);
  for (int i = 2; i < n; i++) 
    invp[i] = query(invp[i-1], invp[1], invp[1]);
  rep (i, n) perm[invp[i]] = i;
  printf("!");
  rep (i, n) printf(" %d", perm[i]);
  puts("");
  return 0;
}
