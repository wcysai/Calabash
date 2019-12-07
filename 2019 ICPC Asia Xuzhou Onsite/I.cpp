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
int a[300005], b[300005];
set<pair<int, int>, greater<>> sa, sb;

int value(int i, int j) { if (i == j) return INT_MIN; else return a[i] - b[j]; }

pair<int, int> get_ans() {
    int aid = sa.begin()->second, bid = sb.begin()->second;
    int aid2 = next(sa.begin())->second, bid2 = next(sb.begin())->second;
    if (value(aid, bid) > value(bid, bid2)) return make_pair(aid, bid); 
    else return make_pair(bid, bid2);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", a + i, b + i);
        sa.emplace(a[i], i);
        sb.emplace(b[i], i);
    }
    int last = INT_MAX;
    for (int i = 0; i < n - 1; i++) {
        int aid, bid; tie(aid, bid) = get_ans();
        last = min(last, value(aid, bid));
        printf("%d\n", last);
        sa.erase(make_pair(a[aid], aid));
        sb.erase(make_pair(b[aid], aid));
    }
    return 0;
}