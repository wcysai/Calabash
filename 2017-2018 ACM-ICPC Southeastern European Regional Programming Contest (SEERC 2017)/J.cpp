#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;

int n;
int c1, c2, cm;

int main() {
  cin >> n;
  while (n--) {
    int x; cin >> x;
    if (x == 1) c1++;
    if (x == 2) c2++;
    if (x >= 2) cm++;
  }
  c1 %= 3;
  if (cm == 0) {
    if (!c1) cout << "Lose" << endl;
    else cout << "Win" << endl;
  } else if (cm == 1) {
    cout << "Win" << endl;
  } else if (cm >= 3) {
    cout << "Lose" << endl;
  } else {
    if (c1) {
      if (c2) cout << "Win" << endl; else cout << "Lose" << endl;
    } else {
      cout << "Lose" << endl;
    }
  }
  return 0;
}
