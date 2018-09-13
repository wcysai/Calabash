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
int ans[100005];
pair<int, int> val[100005];

int main() {
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> val[i].first;
    val[i].second = i;
  }
  sort(val, val+n);
  for (int i=0; i<n; i++) {
    ans[val[i].second] = n-i;
  }
  for (int i=0; i<n; i++) cout << ans[i] << ' ';
  return 0;
}
