#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
const int MAXN = 256 * 2048;
const int CHARN = 26;
const LL mod = 1000000007;

inline int id(char c) { return c - 'a'; }

int tot, m;

inline int addmod(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}

    
vector<LL> conv(const vector<LL>& lhs, const vector<LL>& rhs) {
    vector<LL> res(min(m + 1, int(lhs.size() + rhs.size() - 1)));
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j <= i; j++) {
            if (j >= lhs.size()) break;
            int k = i - j;
            if (k >= rhs.size()) continue;
            res[i] += lhs[j] * rhs[k] % mod;
        }
        res[i] %= mod;
    }
    return res;
}

struct Trie {
    int n;
    int tr[MAXN][CHARN];
    int tag[MAXN];
    vector<LL> dp[MAXN];
    vector<vector<LL>> f[MAXN];
    int cur = 0;
    
    vector<string> construct(int n, int m) {
        if (m == 1) {
            if (n) {
                return {""};
            } else {
                rep (i, CHARN) if (tr[n][i]) { 
                    string s;
                    s.push_back('a' + i);
                    return {s};
                }
            }
        }
        vector<string> res;
        f[n].pop_back();
        for (int i = CHARN - 1; i >= 0; i--) {
            int ch = tr[n][i];
            if (ch == 0) continue;
            vector<string> cur;
            if (f[n].empty()) {
                cur = construct(tr[n][i], m);
            } else {
                vector<LL> num = f[n].back(); f[n].pop_back();
                for (int i = 1; i < m; i++) {
                    if (num.size() > m - i and num[m - i] and 
                        dp[ch].size() > i and dp[ch][i]) {
                        cur = construct(ch, i);
                        m -= i;
                        break;
                    }
                }
            }
            for (string& s : cur) res.push_back(s + char('a' + i));
        }
//        _debug("n=%d, res.size()=%d\n", n, int(res.size()));
        return res;
    }

    void dfs(int n) {
        if (tag[n]) {
            dp[n] = {0, 1};
            return;       
        }
        rep (i, CHARN) {
            if (tr[n][i] == 0) continue;
            dfs(tr[n][i]);
            if (dp[n].empty()) dp[n] = dp[tr[n][i]];
            else dp[n] = conv(dp[n], dp[tr[n][i]]);
            f[n].push_back(dp[n]); 
        }
        if (n) dp[n][1] = (dp[n][1] + 1) % mod;
//        printf("n = %d\n", n);
//        for (int x : dp[n]) cout  << x << ' ' ;cout << endl;
    }

    void work() {
        dfs(0);
        int ans = 0;
        if (dp[0].size() > m) ans = dp[0][m];
        printf("%d\n", ans);
        if (ans) { 
            vector<string> sol = construct(0, m);
            assert(sol.size() == m);
            for (string& s : sol) {
                reverse(range(s));
                cout << s << endl;
            }
        }
    }

    Trie() {
        memset(tr[0], 0, sizeof(tr[0]));
        tag[0] = 0;
        n = 1;
    }

    void insert(const char* s, int t = 1) {
        int p = 0, c, len = strlen(s);
        rep (i, len) {
            c = id(s[i]);
            if (!tr[p][c]) {
                memset(tr[n], 0, sizeof (tr[n]));
                tag[n] = 0;
                tr[p][c] = n++;
            }
            p = tr[p][c];
        }
        tag[p] = t;
    }
} trie;

int n;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        char buf[256]; scanf("%s", buf);
        trie.insert(buf);
    }
    trie.work();
    return 0;
}
