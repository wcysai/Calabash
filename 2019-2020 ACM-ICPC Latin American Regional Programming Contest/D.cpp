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
typedef complex<double> point;

int n;
int b[5120], x[5120], y[5120];
vector<double> vec;

const double pi = acos(-1);

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d%d%d", x + i, y + i, b + i);
    rep (i, n) rep (j, n) if (b[i] < b[j]){
        if (y[i] == y[j] and x[i] == x[j]) while (1) free(0);
        vec.push_back(atan2(y[j] - y[i], x[j] - x[i]));
    }
    if (vec.size() <= 1) return puts("Y"), 0;
    sort(range(vec));
    for (int i = 0; i < vec.size(); i++) {
        double angd = vec[(i+1)%vec.size()] - vec[i];
        if (angd < 0) angd += pi + pi;
        if (angd > pi - 1e-10) return puts("Y"), 0;
    }
    puts("N");
    return 0;
}
