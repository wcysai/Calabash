#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 300005;
struct {
    int tr[MAXN];

    void init() { memset(tr, 0, sizeof tr);  }
    
    int sum(int n) {
        int ans = 0;
        while (n) { ans += tr[n]; n &= n - 1; }
        return ans;
    }

    void inc(int n) {
        while (n < MAXN) { tr[n]++; n += n & -n; }
    }
} bit;

void print(vector<int> x) {
    for (int xx  : x) cout << xx << ' '; cout << endl;
}

unsigned invp(vector<int> vec) {
    int tot = 0;
    unsigned ans = 0;
    bit.init();
    for (int x : vec) {
        ans += tot - bit.sum(x);
        bit.inc(x);
        tot++;
    }
    return ans;
}

int ident(vector<int> a, vector<int> b) {
    sort(range(a)); sort(range(b));
    if (a != b) return -1;
    if (unique(range(a)) != a.end()) return 1;
    return 0;
}

bool check(vector<int> a, vector<int> b) {
//    print(a); print(b);
    return (invp(a) & 1) == (invp(b) & 1);    
}

int main() {
    int n; scanf("%d", &n);
    vector<int> a[2], b[2];
    int res[2];
    rep (i, n) {
        int x; scanf("%d", &x);
        a[i&1].push_back(x);
    }
    rep (i, n) {
        int x; scanf("%d", &x);
        b[i&1].push_back(x);
    }
    rep (i, 2) res[i] = ident(a[i], b[i]);
//    cout << res[0] << ' ' << res[1] << endl;
    if (res[0] < 0 || res[1] < 0) {
        cout << 0 << endl;
    } else if (res[0] > 0 || res[1] > 0) {
        cout << 1 << endl;
    } else {
        cout << int(check(a[0], b[0]) == check(a[1], b[1])) << endl;
    }   
    return 0;
}
