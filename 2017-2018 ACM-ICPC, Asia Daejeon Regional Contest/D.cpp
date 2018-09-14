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

int next(int x) {
  char buf[32];
  sprintf(buf, "%d", x);
  int ptr = 0;
  int ans = 0;
  while (buf[ptr]) {
    int val  = buf[ptr] - '0';
    ans += val * val;
    ptr++;
  }
  return ans;
}

set<int> ha;

int main() {
  cin >> n;
  ha.insert(n);
  while (1) {
    int nv = next(n);
    if (nv == 1) {
      cout << "HAPPY" << endl;
      return 0;
    } else {
      if (ha.find(nv) != ha.end()) {
        cout << "UNHAPPY" << endl;
        return 0;
      } else {
        ha.insert(nv);
      }
    }
    n = nv;
    _debug("%d", n);
  }
  return 0;
}
