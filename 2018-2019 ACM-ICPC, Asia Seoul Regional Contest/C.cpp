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
vector<int> x, x1, x2;
deque<int> a;

int main() {
    scanf("%d", &n); x.resize(n);
    rep (i, n) scanf("%d", &x[i]);
    sort(range(x), greater<>());
    for (int xx : x) a.push_back(xx);
    
    while (true) {
        if (a.empty()) break;
        x1.push_back(a.back()); a.pop_back(); 
        if (a.empty()) break;
        x2.push_back(a.front()); a.pop_front();
        if (a.empty()) break;
        x1.push_back(a.front()); a.pop_front();
        if (a.empty()) break;
        x2.push_back(a.back()); a.pop_back();
    }
    reverse(range(x2));
    x = x1;
    for (int xx : x2) x.push_back(xx);
    
    long double ans = DBL_MAX;
    rep (_, n) {
        long double tot = x.front() + x.back();
        for (int i = 0; i < n - 1; i++) 
            tot += 2 * sqrt((long double)(x[i]) * x[i+1]);
        ans = min(ans, tot);
        rotate(x.begin(), x.begin() + 1, x.end());
    }
    printf("%.7Lf\n", ans);
    return 0;
}
