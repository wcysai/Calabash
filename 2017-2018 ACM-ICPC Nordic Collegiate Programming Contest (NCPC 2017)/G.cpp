#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
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

typedef tuple<int, int, int> T;

using namespace __gnu_pbds;
tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>
rkt;

int sol[100005], pen[100005];
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  Rep (i, n) 
    rkt.insert(make_tuple(0, 0, i));
  rep (i, m) {
    int t, p; scanf("%d%d", &t, &p);
    rkt.erase(make_tuple(sol[t], pen[t], t));
    sol[t]--; pen[t] += p;
    rkt.insert(make_tuple(sol[t], pen[t], t));
    cout << rkt.order_of_key(make_tuple(sol[1], pen[1], 0)) + 1 << endl;
  }
  return 0;
}
