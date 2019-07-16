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

int n, maxn, thresh;
int x[1 << 17], y[1 << 17];
int cnt[1 << 17];
int psum[1 << 17];
int dp[1 << 17], pre[1 << 17];
int xmin, xmax, xn;

const int MAXN = 1 << 19;

vector<pair<int, int>> getans() {
    vector<pair<int, int>> vec;
    set<int> s;
    for (int i = xn; i; i = pre[i]) s.insert(i - 1 + xmin);
    rep (i, n) if (s.count(x[i])) vec.emplace_back(x[i], y[i]);
    return vec;
}

void printans(vector<pair<int, int>> ans) {
    printf("%d\n", int(ans.size()));
    for (auto p : ans) 
        printf("%d %d\n", p.first, p.second);
    exit(0);
}

int solve() {
    xmin = *min_element(x, x + n); xmax = *max_element(x, x + n);
    memset(cnt, 0, sizeof cnt);
    rep (i, n) cnt[x[i] - xmin + 1]++;
    partial_sum(cnt, cnt + n + 1, psum);
    int l = 0; 
    xn = xmax - xmin + 2;
    deque<int> q = {0};
    Rep (i, xn) {
        while (psum[i - 1] - psum[l] > maxn) l++;
        while (q.back() < l) q.pop_back();
        assert(q.size());
        dp[i] = dp[q.back()] + cnt[i];
        pre[i] = q.back();
        while (q.size() and dp[q.front()] >= dp[i]) q.pop_front();
        q.push_front(i);
    }
    return dp[xn];
}


int main() {
    scanf("%d", &n); maxn = (n + 1) / 2; thresh = ceil(1.5 * sqrt(n));
    rep (i, n) scanf("%d%d", x + i, y + i);
    vector<pair<int, int>> ans;
    if (solve() <= thresh) {
        ans = getans();
        printans(ans);
    }
    rep (i, n) swap(x[i], y[i]);
    if (solve() <= thresh) {
        ans = getans();
        for (auto& p : ans) swap(p.first, p.second);
        printans(ans);
    }
    assert(0);
    return 0;
}
