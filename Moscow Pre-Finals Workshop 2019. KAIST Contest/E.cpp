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
int a[512000], b[512000];
bool sel[512000];
vector<int> sa, sb;
priority_queue<int, vector<int>, greater<int>> qa, qb;
LL ans;

void pop_useless() {
    while (sel[sa.back()]) sa.pop_back();
    while (sel[sb.back()]) sb.pop_back();
}

void worka() {
    pop_useless();
    int pa = sa.back(), pb = sb.back();
    int c1 = a[pa], c2 = qb.top() + b[pb];
    if (c1 < c2) {  // select pa.a
        ans += a[pa];
        sel[pa] = true;
        qa.push(b[pa] - a[pa]);
    } else { // select pb.b and qb.top change to a
        ans += b[pb]; ans += qb.top();
        sel[pb] = true;
        qa.push(-qb.top()); qb.pop();
        qb.push(a[pb] - b[pb]);
    }
}

void workb() {
    pop_useless();
    int pa = sa.back(), pb = sb.back();
    int c1 = b[pb], c2 = qa.top() + a[pa];
    if (c1 < c2) { // select pb.b
        ans += b[pb];
        sel[pb] = true;
        qb.push(a[pb] - b[pb]);
    } else { // select pa.a and qa.top change to b
        ans += a[pa]; ans += qa.top();
        sel[pa] = true;
        qb.push(-qa.top()); qa.pop();
        qa.push(b[pa] - a[pa]);
    }
}

int main() {
    scanf("%d", &n);
    rep (i, n + n) scanf("%d%d", a + i, b + i);
    sa.resize(n + n); iota(range(sa), 0); sb = sa;
    sort(range(sa), [] (int x, int y) { return a[x] > a[y]; });
    sort(range(sb), [] (int x, int y) { return b[x] > b[y]; });
    qa.push(INT_MAX / 2); qb.push(INT_MAX / 2);
    rep (i, n) {
        worka(); workb();
        printf("%lld\n", ans);
    }
    return 0;
}
