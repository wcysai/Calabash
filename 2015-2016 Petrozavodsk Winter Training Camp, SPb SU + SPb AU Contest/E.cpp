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

#define MAXN 50005
#define MAXM 200005
int n, m;

// symbol property
int mask[MAXN];
vector<pair<int, int>> contained[MAXN];

// rule property
int refcnt[MAXM];
vector<int> used[MAXM], symmask[MAXM];
int offset[MAXM], rmask[MAXM], sid[MAXM];

void update_symbol(int id, int smask);
void update_rule(int rid, int lid, int smask);

void update_symbol(int id, int smask) {
    _debug("lid=%d, mask=%d", id, smask);
    if ((mask[id] | smask) == mask[id]) return;
    mask[id] |= smask;
    for (auto p : contained[id]) update_rule(p.first, p.second, mask[id]);
}

inline int mask_combine(int mask1, int mask2) {
    if (mask1 == 3 || mask2 == 3) return 3;
    return (mask2 == 1) ? (mask1) : (3 ^ mask1);
}

void compute_rule(int rid) {
    rmask[rid] = (offset[rid] ? 2 : 1);
    rep (i, used[rid].size())
        rmask[rid] = mask_combine(rmask[rid], symmask[rid][i]);
}

void update_rule(int rid, int lid, int smask) {
    int prev_untouched = refcnt[rid];
    if (not (used[rid][lid]++)) refcnt[rid]--;
    symmask[rid][lid] |= smask;
    if (refcnt[rid] == 0 and smask == 3) rmask[rid] = 3;
    if (prev_untouched and refcnt[rid] == 0) compute_rule(rid);
    if (refcnt[rid] == 0) update_symbol(sid[rid], rmask[rid]);
}

void clean() {
    Rep (i, n) {
        mask[i] = 0;
        contained[i].clear();
    }
    Rep (i, m) {
        refcnt[i] = offset[i] = rmask[i] = sid[i] = 0;
        used[i].clear(); symmask[i].clear();
    }
}

int main() {
    while (scanf("%d%d", &n, &m), n) {
        clean();
        Rep (i, m) {
            int k; scanf("%d%d", sid + i, &k);
            rep (j, k) {
                char str[32]; int buf; scanf("%s", str);
                if (isalpha(str[0])) {
                    offset[i] ^= 1; 
                } else {
                    buf = atoi(str);
                    contained[buf].emplace_back(i, used[i].size());
                    used[i].push_back(0); symmask[i].push_back(0);
                    refcnt[i]++;
                }
            }
        }
        for (int i = 1; i <= m; i++) if (refcnt[i] == 0) {
            compute_rule(i);
            update_symbol(sid[i], rmask[i]);
        }
        if (mask[1] & 2) puts("YES"); else puts("NO");
    }
    return 0;
}
