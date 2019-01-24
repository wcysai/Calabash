#include <bits/stdc++.h>
using namespace std;
  
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
  
int n;
LL k;
int p[300005], q[300005];
int a[300005], b[300005];
  
int main() {
    scanf("%d%lld", &n, &k);
    Rep (i, n) scanf("%d", p + i);
    Rep (i, n) scanf("%d", q + i);
    Rep (i, n) if (i < n + 1 - i) swap(q[i], q[n+1-i]);
    Rep (i, n) b[q[i]] = i;
    Rep (i, n) {
        if (k == 0) {
            a[p[i]] = n;
        } else if (k < n - p[i]) {
            vector<int> v;
            for (int j = p[i] + 1; j <= n; j++) v.push_back(b[j]);
            sort(range(v), greater<int>());
            a[p[i]] = v[k];
            k = 0;
        } else {
            k -= n - p[i];
        }
    }
    assert(!k);
    Rep (i, n - 1) assert(a[p[i]] <= a[p[i+1]] and -b[q[i]] >= -b[q[i+1]]);
    Rep (i, n) assert(abs(a[i]) <= n and abs(b[i]) <= n);
    puts("Yes");
    Rep (i, n) printf("%d%c", a[i], i == n ? '\n' : ' ');
    Rep (i, n) printf("%d%c",-b[i], i == n ? '\n' : ' ');
    return 0;
}
