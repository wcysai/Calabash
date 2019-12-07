
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

const int MAXN = 200005;
struct {
    struct bit_inner {
        vector<LL> tr;
        vector<int> xv;
        void insert(int val) { xv.push_back(val); }

        void inflate() {
            sort(range(xv)); 
            xv.erase(unique(range(xv)), xv.end());
            tr.resize(xv.size() + 1);
        }

        void add(int n, LL x) {
            n = upper_bound(range(xv), n) - xv.begin();
            while (n < tr.size()) {
                tr[n] += x;
                n += n & -n;
            }
        }

        LL sum(int n) {
            n = upper_bound(range(xv), n) - xv.begin();
            LL ret = 0;
            while (n) {
                ret += tr[n];
                n &= n - 1;
            }
            return ret;
        }
    } tr[MAXN];
    
    void insert(int n1, int n2) {
        while (n1 < MAXN) {
            tr[n1].insert(n2);
            n1 += n1 & -n1;
        }
    }

    void inflate() { for (auto& t : tr) t.inflate(); }

    void add(int n1, int n2, LL x) {
        while (n1 < MAXN) {
            tr[n1].add(n2, x);
            n1 += n1 & -n1;
        }
    }

    LL sum(int n1, int n2) {
        LL ret = 0;
        while (n1) {
            ret += tr[n1].sum(n2);
            n1 &= n1 - 1;
        }
        return ret;
    }
} bit;

int n, q;
int a[MAXN];
tuple<int, int, int> qry[MAXN];

int main() {
    scanf("%d%d", &n, &q);
    Rep (i, n) {
        scanf("%d", a + i);
        bit.insert(i, a[i]);
    }
    rep (i, q) {
        int op, x, y; scanf("%d%d%d", &op, &x, &y);
        if (op == 1) bit.insert(x, y);
        qry[i] = make_tuple(op, x, y);
    }
    bit.inflate();
    Rep (i, n) bit.add(i, a[i], a[i]);
    rep (i, q) {
        int op, x, y; tie(op, x, y) = qry[i];
        _debug("#%d: %d %d %d", i, op, x, y);
        if (op == 1) {
            bit.add(x, a[x], -a[x]);
            a[x] = y;
            bit.add(x, a[x], a[x]); 
        } else if (op == 2) {
            LL ans = 0, newans = 0;
            do {
                ans = newans;
                newans = bit.sum(y, min((LL)INT_MAX, ans + 1))
                    - bit.sum(x - 1, min((LL)INT_MAX, ans + 1));
                _debug("op #%d: %lld %lld", i, ans, newans);
            } while (newans > ans);
            printf("%lld\n", ans + 1);
        }
    }
    return 0;
}