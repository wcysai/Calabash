#pragma GCC optimize(3)
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

int w, h, n;
#define logf dahui
double logi[1 << 20], logf[1 <<  20];

int main() {
    cin >> w >> h >> n;
    Rep (i, n + 1) logi[i] = log2(i);
    partial_sum(logi, logi + n + 2, logf);
    vector<double> pval;
    pval.reserve(n + 1);
    for (int i = 0; i <= n; i++) { 
        pval.push_back(logf[n] - logf[n-i] - logf[i] - 2 * (logi[i+1] + logi[n-i+1]) - 
            n * logi[2]); 
    }
    sort(range(pval));
    double ans = 0.0;
    for (double x : pval) ans += pow(2.0, x);
    ans *= h * w;
    cout << setprecision(12) << ans << endl;
    return 0;
}
