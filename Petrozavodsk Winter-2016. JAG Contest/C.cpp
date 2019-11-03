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

vector<int> val;
bool del[1024];

void add_len(char tp, int v) {
    if (tp == 'y') {
        if (val.size() & 1) val.push_back(v);
        else val.back() = min(val.back(), v);
    } else {
        if (val.size() & 1) val.back() = max(val.back(), v);
        else val.push_back(v);
    }
}

map<tuple<int, int, int>, int> mem;
map<pair<int, int>, int> maxpos;
                      //    > dlen deleted
int solve(int l, int r, int dlen) {
    if (l == r) return 0;
    if (r - l == 2) return val[l + 1] > dlen ? 0 : 1;

    if (mem.count(make_tuple(l, r, dlen))) return mem[make_tuple(l, r, dlen)];

    int maxd = INT_MIN, pos;
    if (maxpos.count(make_pair(l, r))) {
        pos = maxpos[make_pair(l, r)];
        maxd = val[pos];
    } else {
        for (int i = l + 2; i < r; i += 2) {
            if (val[i] > maxd) {
                maxd = val[i];
                pos = i;
            }
        }
        maxpos[make_pair(l, r)] = pos;
    }
    assert(maxd <= dlen);

    return mem[make_tuple(l, r, dlen)] = min(
        solve(l, pos, dlen) + solve(pos, r, dlen),
        1 + solve(l, pos, maxd) + solve(pos, r, maxd)
    );
}

int main() {
    add_len('n', INT_MAX);
    int n;
    scanf("%d", &n);
    Rep (i, n) {
        char buf[4];
        int l; scanf("%s%d", buf, &l);
        add_len(buf[0], l);
    }
    add_len('n', INT_MAX);
    assert(val.size() & 1);
    cout << solve(0, val.size() - 1, INT_MAX) << endl;
    return 0;
}
