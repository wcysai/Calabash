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

int n, m;

typedef pair<int, int> pii;

pii solve(int n, int m) {
  if (n == 1) return {0, 0};
  int nn = n >> 1;
  int next = m % (nn * nn);
  pii ans = solve(nn, next);
  switch (m / (nn * nn)) {
    case 0 :
      swap(ans.first, ans.second);
      break;
    case 1 :
      ans.second += nn;
      break;
    case 2 :
      ans.first += nn; ans.second += nn;
      break;      
    case 3 :
      ans = {nn - 1 - ans.second, nn - 1 - ans.first};
      ans.first += nn;
      break;
  }
  _debug("n=%d, m=%d, x=%d, y=%d", n, m, ans.first, ans.second);
  return ans;
}

int main() {
  cin >> n >> m;
  pii ans = solve(n, m-1);
  cout << ans.first + 1 << ' ' << ans.second + 1 << endl;
  return 0;
}
