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

int n;
typedef tuple<double, double, int> tp;
vector<tp> objs;
double h[100005], area;
double w[100005], x[100005], len;
int id[100005];
int lptr, rptr;
double parl, parr;

bool check(double s) {
    for (lptr = 0; x[lptr + 1] < s; lptr++);
    for (rptr = lptr; rptr < n and x[rptr + 1] < s + len; rptr++);
    double a = 0.0;
    for (int i = lptr; i < rptr; i++) a += h[i] * w[i];
    a -= (s - x[lptr]) * h[lptr];
    a += (s + len - x[rptr]) * h[rptr];
    parr = (s + len - x[rptr]) / w[rptr];
    parl = (s - x[lptr]) / w[lptr];
    return a >= area / 2.0;
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        int x, y; scanf("%d%d", &x, &y);
        area += y;
        objs.emplace_back(x, double(y) / x, i + 1);
    }
    sort(range(objs), [] (const tp& lhs, const tp& rhs) {
        return get<1>(lhs) < get<1>(rhs);
    });
    rep (i, n) tie(w[i], h[i], id[i]) = objs[i];
    partial_sum(w, w + n, x + 1);
    len = x[n] / 2.0;

#ifdef __LOCAL_DEBUG__
    printf("x: ");
    for (int i = 0; i <= n; i++) printf("%.5f ", x[i]); puts("");
    printf("w: ");
    for (int i = 0; i <= n; i++) printf("%.5f ", w[i]); puts("");
    printf("h: ");
    for (int i = 0; i <= n; i++) printf("%.5f ", h[i]); puts("");
    printf("id: ");
    for (int i = 0; i <= n; i++) printf("%d       ", id[i]); puts("");
#endif 
    double l = 0.0, r = len, mid;
    rep (_, 60) {
        mid = (l + r) / 2;
        // cout << mid << endl;
        if (check(mid)) r = mid;
        else l = mid;
    }
    mid = (l + r) / 2; check(mid);
    
#ifdef __LOCAL_DEBUG__
    cout << mid << endl; 
    cout << lptr << ' ' << rptr << endl;
    cout << parr << ' ' << parl << endl;
#endif

    if (lptr == rptr) {
        puts("1");
        printf("%d %.15f\n", id[lptr], parr - parl);
        printf("%d %d\n", 1, id[lptr]); 
    } else {
        puts("2");
        printf("%d %.15f\n", id[lptr], parl);
        printf("%d %.15f\n", id[rptr], parr);
        vector<int> bin;
        for (int i = 0; i < n; i++) {
            if (i > lptr and i <= rptr) bin.push_back(id[i]);
        }
        bin.push_back(n+1);
        printf("%d ", int(bin.size()));
        for (int x : bin) printf("%d ", x); puts("");
    }
    return 0;
}
