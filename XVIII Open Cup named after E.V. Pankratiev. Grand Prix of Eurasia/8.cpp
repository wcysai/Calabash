#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 20;
const int MAXV = 1 << (MAXN + 1);

int n;
map<pair<int, int>, int> cache;

int query(int x, int y) {
    x -= 1 << MAXN; y -= 1 << MAXN;
    auto ptr = cache.find({x, y});
    if (ptr != cache.end()) return ptr->second;
    printf("? %d %d\n", x, y);
    fflush(stdout);
    int res; scanf("%d", &res);
    cache[{x, y}] = res;
    return res;
}

vector<pair<int, int>> ans;

vector<int> ycords;
vector<int> next_ycords;
map<int, int> xs;

int yleq(int y) {
    int ans = 0;
    for (int yv : ycords) if (yv <= y) ans++;
    return ans;
}

void searchx(int l, int r, int ln, int rn) {
    if (ln == rn) return;
    if (r == l + 1) {
        xs[r] += rn - ln;
        return;
    }
    int mid = (l + r) / 2, midn = query(mid, MAXV);
    searchx(l, mid, ln, midn);
    searchx(mid, r, midn, rn);
}

void searchy(int x, int l, int r, int ln, int rn) {
    _debug("x=%d, (%d, %d], n: %d, %d", x, l, r, ln, rn);
    if (ln == rn) return;
    if (r == l + 1) {
        ans.emplace_back(x - MAXV / 2, r - MAXV / 2);
        next_ycords.push_back(r);
        return;
    }
    int mid = (l + r) / 2, midn = query(x, mid) - yleq(mid);
    searchy(x, l, mid, ln, midn);
    searchy(x, mid, r, midn, rn);
}

int main() {
    scanf("%d", &n);
    searchx(0, MAXV, 0, n);
    for (auto p : xs) {
        searchy(p.first, 0, MAXV, 0, p.second);
        ycords.insert(ycords.end(), range(next_ycords));
        next_ycords.clear();
    }

    printf("!");
    for (auto x : ans)
        printf(" %d %d", x.first, x.second);
    puts("");
    return 0;
}
