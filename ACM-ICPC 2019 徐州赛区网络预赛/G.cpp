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
char s[300005];
int pre[300005][26], nxt[300005][26];
LL ans;

void prep() {
    rep (i, n) rep (ch, 26) {
        if (s[i] == ch + 'a') {
            pre[i][ch] = i;
        } else {
            pre[i][ch] = i ? pre[i-1][ch] : INT_MIN / 10;
        }
    }
    rep (ch, 26) nxt[n][ch] = INT_MAX / 10;
    for (int i = n - 1; i >= 0; i--) rep (ch, 26) {
        if (s[i] == ch + 'a') {
            nxt[i][ch] = i;
        } else {
            nxt[i][ch] = nxt[i+1][ch];
        }
    }
}

void update(int l, int r) {
    if (l > r) return;
    int nc = (r - l + 2) / 2;
    rep (ch, 26) {
        if (nxt[l][ch] > r) continue;
        int midl = (l + r) / 2, midr = (l + r + 1) / 2;
        int pv = pre[midl][ch], nv = nxt[midr][ch];
        ans += nc - min(midl - pv, nv - midr);
//        cout << l << ' ' << r << ' ' << ch << ' ' << nc - min(rl, rr) << endl;
    }
}

struct Manacher {
    int Len;
    vector<int> lc;
    string s;

    void work() {
        lc[1] = 1;
        int k = 1;
        for (int i = 2; i <= Len; i++) {
            int p = k + lc[k] - 1;
            if (i <= p) {
                lc[i] = min(lc[2 * k - i], p - i + 1);
            } else {
                lc[i] = 1;
            }
            while (s[i + lc[i]] == s[i - lc[i]]) lc[i]++;
            if (i + lc[i] > k + lc[k]) k = i;
        }
    }

    void init(const char *tt) {
        int len = strlen(tt);
        s.resize(len * 2 + 10);
        lc.resize(len * 2 + 10);
        s[0] = '*';
        s[1] = '#';
        for (int i = 0; i < len; i++) {
            s[i * 2 + 2] = tt[i];
            s[i * 2 + 1] = '#';
        }
        s[len * 2 + 1] = '#';
        s[len * 2 + 2] = '\0';
        Len = len * 2 + 2;
        work();
    }

    void solve(int n) {
//        cout << s << endl;
//        for (int x : lc) cout << x / 2 << endl;
        rep (i, n) {
            int r = lc[i * 2 + 2] / 2;
            update(i - r + 1, i + r - 1);
        }
        for (int i = 1; i < n; i++) {
            int r = lc[i * 2 + 1] / 2;
            update(i - r, i + r - 1);
        }
    }
} manacher;

int main() {
    scanf("%s", s); n = strlen(s);
    prep();
    manacher.init(s);
    manacher.solve(n);
    cout << ans << endl;
    return 0;
}
