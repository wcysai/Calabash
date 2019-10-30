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

const int MAXN = 250000, CHARN = 26;

struct ACAM {
    int n;
    int tr[MAXN][CHARN];

    ACAM() {
        memset(tr[0], 0, sizeof(tr[0]));
        n = 1;
    }
    
    void print() {
        rep (i, n) {
            printf("%d:", i);
            rep (c, 26) if (tr[i][c]) printf(" '%c' -> %d,", c + 'A', tr[i][c]);
            puts("");
        }
    }

    void add(const char *s, int len, int id[]) {
        int p = 0, c;
        rep (i, len) {
            id[i] = p;
            c = s[i] - 'A';
            if (!tr[p][c]) {
                memset(tr[n], 0, sizeof(tr[n]));
                tr[p][c] = n++;
            }
            p = tr[p][c];
        }
        id[len] = p;
    }
    
    int fail[MAXN];
    //  left-closed right-closed
    int lv[MAXN], rv[MAXN], idx;
    vector<int> adj[MAXN];

    void dfs(int u) {
        lv[u] = ++idx;
        for (int v : adj[u]) dfs(v);
        rv[u] = idx;
    }
    
    void construct() {
        queue<int> q;
        fail[0] = 0;
        rep (c, CHARN) {
            if (int u = tr[0][c]) {
                fail[u] = 0;
                q.push(u);
            }
        }
        while (!q.empty()) {
            int r = q.front();
            q.pop();
            rep (c, CHARN) {
                int u = tr[r][c];
                if (!u) {
                    tr[r][c] = tr[fail[r]][c];
                    continue;
                }
                q.push(u);
                int v = fail[r];
                while (v and !tr[v][c]) v = fail[v];
                fail[u] = tr[v][c];
            }
        }

        for (int i = 1; i < n; i++) adj[fail[i]].push_back(i);
        dfs(0);
    }
} PrefAC, SufAC;

int n, m, q;
char g[512][512];
int id1[512][512], id2[512][512];
int np;
int x[200005], y[200005], ansid[200005];

struct {
    int tr[MAXN];

    void add(int n) {
        while (n < MAXN) {
            tr[n]++;
            n += n & -n;
        }
    }
    
    int sum(int n) {
        int ans = 0;
        while (n) { 
            ans += tr[n];
            n &= n - 1;
        }
        return ans;
    }
} bit;

int ans[200005];

struct query {
    // op == 1 : add point (x, y)
    // op == 2 : query <= x, <= y 
    int op; 
    int x, y, qid;

    bool operator < (const query& a) const {
        return make_pair(x, op) < make_pair(a.x, a.op);
    }

    void deal() {
        if (op == 1) {
            bit.add(y);
        } else {
            int ans = bit.sum(y);
            if (qid > 0) ::ans[qid] += ans; else ::ans[-qid] -= ans; 
        }
    }
};

vector<query> qs;

int main() {
    scanf("%d%d%d", &n, &m, &q);
    rep (i, n) scanf("%s", g[i]);
    Rep (qid, q) {
        static char qs[200005];
        static int prefid[200005], sufid[200005];
        scanf("%s", qs);
        int len = strlen(qs);
        PrefAC.add(qs, len, prefid);
        reverse(qs, qs + len);
        SufAC.add(qs, len, sufid);
        for (int i = 0; i < len; i++) {
            x[np] = prefid[i+1];
            y[np] = sufid[len- i];
            ansid[np] = qid;
            np++;
        }
    }
    PrefAC.construct(); SufAC.construct();
    rep (i, n) {
        int p = 0;
        rep (j, m) {
            p = PrefAC.tr[p][g[i][j] - 'A'];
            id1[i][j] = PrefAC.lv[p];
        }
    }
    rep (j, m) {
        int p = 0;
        for (int i = n - 1; i >= 0; i--) {
            p = SufAC.tr[p][g[i][j] - 'A'];
            id2[i][j] = SufAC.lv[p];
        }
    }
    rep (i, n) rep (j, m) qs.push_back(query{1, id1[i][j], id2[i][j], 0});
    rep (i, np) {
        int l1 = PrefAC.lv[x[i]], r1 = PrefAC.rv[x[i]];
        int l2 = SufAC.lv[y[i]], r2 = SufAC.rv[y[i]];
        qs.push_back(query{2, r1, r2, ansid[i]}); 
        qs.push_back(query{2, l1-1, r2, -ansid[i]}); 
        qs.push_back(query{2, r1, l2-1, -ansid[i]}); 
        qs.push_back(query{2, l1-1, l2-1, ansid[i]});
    }
    sort(range(qs));
    for (auto& qr : qs) qr.deal();
    Rep (qid, q) printf("%d\n", ans[qid]);
    return 0;
}

