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

constexpr int MAXN = 1 << 17, ARRSZ = MAXN / 64;

typedef ULL bs[ARRSZ];

inline void bs_flip(ULL* b, int bit) {
    int id = bit / 64, x = bit % 64;
    b[id] ^= (1ull << x);
}

constexpr int BLOCKN = 512, BLOCKSZ = MAXN / BLOCKN;
int arr[MAXN];

bs block[BLOCKN + 1];

void flip_val(int pos, int x) {
    for (int i = (pos / BLOCKSZ) + 1; i <= BLOCKN; i++)
        bs_flip(block[i], x);
}

bs query_buf;

int query(int l, int r) {
    int bl = l / BLOCKSZ, br = r / BLOCKSZ;
    int bls = bl * BLOCKSZ, brs = br * BLOCKSZ;
    rep (i, ARRSZ) query_buf[i] = block[bl][i] ^ block[br][i];
    for (int i = bls; i < l; i++) bs_flip(query_buf, arr[i]);
    for (int i = brs; i < r; i++) bs_flip(query_buf, arr[i]);
    rep (i, ARRSZ) {
        if (query_buf[i]) {
            int pos = i * 64;
            while (!(query_buf[i] & 1)) {
                query_buf[i] >>= 1;
                pos++;
            }
            return pos;
        }
    }
    return -1;
}

int main() {
    int n; scanf("%d", &n);
    Rep (i, n) scanf("%d", arr + i);
    rep (i, MAXN) flip_val(i, arr[i]);
    int q;
    while (scanf("%d", &q), q) {
        while (q--) {
            int op, x, y; scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                flip_val(x, arr[x]);
                arr[x] = y;
                flip_val(x, arr[x]);
            } else if (op == 2) {
                int ans = query(x, y + 1);
                printf("%d\n", ans);
                fflush(stdout);
            } else assert(0);
        }
    }
    return 0;
}
