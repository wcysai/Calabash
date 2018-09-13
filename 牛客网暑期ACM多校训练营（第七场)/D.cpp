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
 
vector<pair<int, int>> ans = {
  {      3,     1 },
  {      7,     3 },
  {     23,    11 },
  {     71,    35 },
  {    311,   155 },
  {    479,   239 },
  {   1559,   779 },
  {   5711,  2855 },
  {  10559,  5279 },
  {  18191,  9095 },
  {  31391, 15695 },
  { 100005,     0 }
};
 
int main() {
  LL m; cin >> m;
  LL p, n;
  pair<int, int> cur;
  for (auto &pa : ans) {
    if (pa.first <= m) {
      cur = pa;
    }
  }
  tie(p, n) = cur;
  while (n % p) n += p - 1;
  LL x = 2, t = 1;
  cout << x << ' ' << n << ' ' << t << ' ' << p << endl;
  return 0;
}
