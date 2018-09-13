#include <bits/stdc++.h>
using namespace std;

#define PROBLEM_NAME  "powersum"

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

typedef bitset<5120> bs;

int n;
bs g[5120];
int sz[5120], ord[5120];
int val[5120], t[5120];
bool done[5120];

int main() {
#ifndef __LOCAL_DEBUG__
  freopen(PROBLEM_NAME ".in", "r", stdin);
  freopen(PROBLEM_NAME ".out", "w", stdout);
#endif
  scanf("%d", &n);
  rep (i, n) {
    char buf[5120]; scanf("%s", buf);
    rep (j, n) g[j][i] = (buf[j] == '1');
    ord[i] = i;
  }
  rep (i, n) sz[i] = g[i].count();
  sort(ord, ord + n, [] (int a, int b) { return sz[a] < sz[b]; });
//  rep (i, n) cout << g[i] << endl;
  for (int i = 1; i < n; i++) {
    if ((g[ord[i-1]] & g[ord[i]]) != g[ord[i-1]]) {
      puts("NO");
      return 0;
    }
  }
  rep (i, n) {
    t[ord[i]] = i;
    rep (j, n) {
      if (!done[j] && g[ord[i]][j]) {
        val[j] = -i;
        done[j] = true;
        _debug("fill %d with %d", j, i);
      }
    }
  }
  rep (j, n) {
    if (!done[j]) {
      val[j] = -n;
      done[j] = true;
    }
  }
  puts("YES");
  rep (i, n) 
    printf("%d %d\n", val[i], t[i]);
  puts("0");
  return 0;
}
