#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int r, s, p;

int main() {
    scanf("%d%d%d", &r, &s, &p);
    vector<int> ts;
    while (p--) {
        int x, y; scanf("%d%d", &x, &y); swap(x, y);
        if (x <= s) x--;
        y = r - y;
        ts.push_back(abs(x - s) + y);
    //    cout << ts.back() << endl;
    }
    int ans = 0;
    sort(range(ts));
    for (int t : ts) {
        ans = max(ans + 1, t);
    }
    cout << ans  + 1 << endl;
    return 0;
}
