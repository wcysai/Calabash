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

int n;
int x[100005], y[100005];

struct bit_purq {
    int N; 
    vector<int> tr;
    void init(int n) { tr.assign(N = n + 5, 0); }
    int sum(int n) {
        int ans = 0;
        while (n) {
            ans += tr[n];
            n &= n - 1;
        }
        return ans;
    }
    void add(int n, int x = 1) {
        while (n < N) {
            tr[n] += x;
            n += n & -n;
        }
    }
} bit;

vector<int> ys;
int getid(int x) {
    return lower_bound(range(ys), x) - ys.begin() + 1;
}

LL check(double theta) {
    double k = 1.0 / tan(theta);
    bit.init(n);
    vector<int> id(n); iota(range(id), 0); 
    sort(range(id), [k] (int i, int j) { 
        return x[i] - k * y[i] > x[j] - k * y[j];
    });
    LL ans = 0;
    int cur = 0;
    for (int i : id) {
        int yid = getid(y[i]);
        ans += cur - bit.sum(yid - 1);
        bit.add(yid);
        cur++;
    }
    return ans;
}

double findn(LL n) {
    double l = 0, r = acos(-1);
    while (r - l > 1e-10) {
        double mid = (l + r) / 2;
        if (check(mid) > n) r = mid; else l = mid;
    }
    return (l + r) / 2;
}

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d", x + i, y + i);
    rep (i, n) ys.push_back(y[i]); sort(range(ys)); ys.erase(unique(range(ys)), ys.end());
    LL tot = 1ll * n * (n - 1) / 2;
    double ans;
    if (tot & 1) {
        ans = findn(tot / 2);
    } else {
        ans = findn(tot / 2) + findn(tot / 2 - 1);
        ans /= 2;
    }
    printf("%.12f\n", ans);
    return 0;
}
