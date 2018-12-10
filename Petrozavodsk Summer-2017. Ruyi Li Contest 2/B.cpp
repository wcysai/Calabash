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

const int mod = 998244353;
const int MAXN = 8192;
const int CHARN = 2;

inline int id(char c) {
    return c - '0';
}

inline int madd(int& x, int y) {
    x += y;
    if (x >= mod) x-= mod;
    return x;
}

struct ACAM {
    int n;
    int tr[MAXN][CHARN];
    int tag[MAXN];
    unsigned mm[MAXN], em[MAXN];
    int dp[128][MAXN][1 << 6];

    ACAM() {
        n = 1;
    }

    void update(int l) {
        rep (i, n) {
            for (unsigned mask = 0; mask < (1 << 6); mask++) {
                madd(dp[l+1][tr[i][0]][mm[tr[i][0]]|mask], dp[l][i][mask]);
                madd(dp[l+1][tr[i][1]][mm[tr[i][1]]|mask], dp[l][i][mask]);
            }
        }
        /*
        rep (i, n) for (int m = 0; m <= 3; m++)
            _debug("dp[%d][%d][%d]=%d", l+1, i, m, dp[l+1][i][m]);
        _debug("");
        */
    }
    
    int work(int l, int strn) {
        unsigned totmask = (1 << strn) - 1;
        // _debug("totmask=%x", totmask);
        int ans = 0;
        dp[0][0][0] = 1;
        rep (i, l) update(i);
        rep (i, n) {
            for (unsigned mask = 0; mask <= totmask; mask++) {
           //     _debug("dp[l][%d][%x]=%d", i, mask, dp[l][i][mask]);
                if ((mask | em[i]) == totmask)
                    madd(ans, dp[l][i][mask]);
            }
        }
        return ans;
    }

    void add(const char* s, unsigned mmask, unsigned emask) { 
        _debug("str added: %s, mmask=%x, emask=%x", s, mmask, emask);
        int p = 0, c, len = strlen(s);
        rep (i, len) {
            c = id(s[i]);
            if (!tr[p][c]) {
                memset(tr[n], 0, sizeof(tr[0]));
                tag[n] = 0;
                tr[p][c] = n++;
            }
            p = tr[p][c];
        }
        tag[p] = 1;
        mm[p] |= mmask;
        em[p] |= emask;
    }

    int fail[MAXN];
    int last[MAXN];

    void construct() {
        queue<int> q;
        fail[0] = 0;
        rep (c, CHARN) {
           if (int u = tr[0][c]) {
                fail[u] = 0;
                q.push(u);
                last[u] = 0;
           }
        }
        while (q.size()) {
            int r = q.front();
            q.pop();
            rep (c, CHARN) {
                int u = tr[r][c];
                mm[r] |= mm[fail[r]];
                em[r] |= em[fail[r]];
                if (!u) {
                    tr[r][c] = tr[fail[r]][c];
                    continue;
                }
                q.push(u);
                int v = fail[r];
                while (v && !tr[v][c]) v = fail[v];
                fail[u] = tr[v][c];
                last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
            }
        }
    }
} acam;

int n, l;
int len[10];
char str[10][32];

bool is_antipal(const char *str, int len, int mid) {
    int lptr = mid - 1, rptr = mid;
    while (lptr >= 0 and rptr < len and str[lptr] != str[rptr]) {
        lptr--; rptr++;
    }
    if (lptr < 0 or rptr >= len) return true;
    return false;
}

int main() {
    scanf("%d%d", &n, &l);
    rep (i, n) {
        scanf("%s", str[i]);
        len[i] = strlen(str[i]);
        acam.add(str[i], (1 << i), 0);
        rep (j, len[i]) str[i][j] ^= 1;
        reverse(str[i], str[i] + len[i]);
        acam.add(str[i], (1 << i), 0);
        rep (j, len[i]) str[i][j] ^= 1;
        reverse(str[i], str[i] + len[i]);
        for (int mid = 1; mid < len[i]; mid++) {
            char tmp[32] = {0};
//            _debug("mid=%d, str[i]=%s, len[i]=%d", mid, str[i], len[i]);
            if (is_antipal(str[i], len[i], mid)) {
                if (mid > len[i] - mid) {
//                    _debug("type 1: mid=%d", mid);
                    memcpy(tmp, str[i], sizeof(tmp));
                    tmp[mid] = 0;
                    acam.add(tmp, 0, (1 << i));
                } else {
//                    _debug("type 2: mid=%d", mid);
                    for (int ii = 0, jj = len[i] - 1; jj >= mid; ii++, jj--) 
                        tmp[ii] = str[i][jj] ^ 1;
                    acam.add(tmp, 0, (1 << i));
                }
            }
        }
    }
    acam.construct();
    printf("%d\n", acam.work(l, n));
    return 0;
}
