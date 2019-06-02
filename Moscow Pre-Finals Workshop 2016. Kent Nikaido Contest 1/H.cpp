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

int l, n;
bool ans;

int highbit(int x) {
    if (__builtin_popcount(x) == 1) return x / 2;
    while (__builtin_popcount(x) > 1) x &= x - 1;
    return x;
}

bool calc(int x, int y, int l) {
    if (l == 1) return true;
    int hb = highbit(l);
    if (x >= hb) x -= hb;
    if (y >= hb) y -= hb;
    l -=  hb;
    if (x + y >= l) return false;
    return calc(x, y, l);
}

int main() {
    cin >> l >> n;
    ans = l & 1; ans = !ans;
    rep (i, n) {
        int x, y; cin >> x >> y;
        x = l - x; y--;
        bool cur = calc(x, y, l);
        _debug("x=%d y=%d l=%d ans=%d", x, y, l, cur);
        ans ^= cur;
    }
    puts(ans ? "Iori" : "Yayoi");
    return 0;
}
