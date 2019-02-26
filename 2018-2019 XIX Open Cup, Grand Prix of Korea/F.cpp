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

LL n;
map<LL, int> code;
vector<pair<int, int>> mem;

int create(LL val, int l, int r) {
    mem.emplace_back(l, r);
    return code[val] = mem.size() - 1;
}

int construct(LL x) {
    if (code.find(x) != code.end()) return code[x];
    if (x == 1) {
        return create(x, -1, -1);
    } else {
        return create(x, construct((x + 1) / 2), construct(x / 2));
    }
}

int main() {
    int T;  scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        code.clear(); mem.clear();
        construct(n);
        printf("%d\n", int(mem.size()));
        for (auto p : mem) printf("%d %d\n", p.first, p.second);
        printf("%d\n", int(mem.size() - 1));
    }
    return 0;
}
