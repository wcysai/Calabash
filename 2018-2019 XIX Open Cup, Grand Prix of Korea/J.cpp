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

const int MAXN = 300005;

int n;
int a[MAXN];

struct Heap {
    LL n, m, v, x, y;
    bool empty = 0; 
    vector<LL> psum;

    void init(int N, int M, int V) {
        tie(n, m) = minmax(N, M);
        v = V;
        for (int i = 0; i <= n; i++) psum.push_back(i);
        partial_sum(range(psum), psum.begin());
    }
    
    LL count(LL x) {
        x = (x - 1) / v;
        if (x <= n) return x * (x + 1) / 2;
        if (x <= m) return (x + x - n + 1) * n / 2;
        if (x >= n + m - 1) return n * m;
        return n * m - (m + n - x) * (m + n - x - 1) / 2;
    }

    void seek(LL cnt) {
        if (cnt == n * m) {
            empty = true;
            return;
        } else if (cnt < psum.back()) {
            int pos = prev(upper_bound(range(psum), cnt)) - psum.begin();
            cnt -= psum[pos];
            y = pos; x = cnt; y -= x;
        } else if (cnt < n * m - psum.back()) {
            cnt -= psum.back();
            x = cnt % n; y = cnt / n;
            y += n - x;
        } else {
            cnt = n * m - cnt - 1;
            int pos = prev(upper_bound(range(psum), cnt)) - psum.begin();
            cnt -= psum[pos];
            y = pos; x = cnt; y -= x;
            x = n - 1 - x; y = m - 1 - y;
        }
    }
    
    LL peek() { return (x + y + 1) * v; }
    
    LL pop() {
        LL ret = peek();
        x++; y--;
        if (y < 0 || x == n) { y += x + 1; x = 0; }
        if (y >= m) { x = y - m + 1; y = m - 1; }
        if (x + y > n + m - 2) empty = true;
        return ret;
    }
} heaps[MAXN];

namespace control {
    
    LL countall(LL x) {
        LL ans = 0;
        rep (i, n) ans += heaps[i].count(x);
        return ans;
    }

    LL bsearch(LL cnt) {
        LL l = 0, r = 1e15;
        while (r > l) {
            LL mid = (l + r) / 2;
            if (countall(mid) <= cnt) l = mid + 1;
            else r = mid;
        }
        return l ;
    }
    
    bool cmp(int lhs, int rhs) { return heaps[lhs].peek() > heaps[rhs].peek(); }

    priority_queue<int, vector<int>, bool(*)(int, int)> pq(cmp);
    
    LL pump() {
        int x = pq.top(); pq.pop();
        LL ret = heaps[x].pop();
        if (!heaps[x].empty) pq.push(x);
        return ret;
    }

    void pushall() {
        rep (i, n) if (!heaps[i].empty) pq.push(i);
    }

    LL cnt[MAXN];

    void setpos(LL pos, LL val) {
        rep (i, n) pos -= (cnt[i] = heaps[i].count(val - 1));
        assert(pos >= 0);
        rep (i, n) {
            if (pos == 0) {
                heaps[i].seek(cnt[i]);
            }
            LL over = heaps[i].count(val) - cnt[i];
            if (over <= pos) {
                pos -= over;
                heaps[i].seek(over + cnt[i]);
            } else {
                heaps[i].seek(cnt[i] + pos);
                pos = 0;
            }
        }
        assert(pos == 0);
    }
    
}

namespace cartesian_tree {
    pair<int, int> st[MAXN][30];
    
    void init() {
        int l = log2(n);
        rep (i, n) st[i][0] = {a[i], i};
        rep (j, l) rep (i, 1+n-(1<<j))
            st[i][j+1] = min(st[i][j], st[i+(1<<j)][j]);
    }

    int rmq(int l, int r) {
        int k = log2(r - l);
        return min(st[l][k], st[r-(1<<k)][k]).second;
    }
     
    void work(int l, int r) {
        if (l == r) return;
        int mid = rmq(l, r);
        heaps[mid].init(mid - l + 1, r - mid, a[mid]);
        work(l, mid); work(mid + 1, r);
    }

    void main() {
        init();
        work(0, n);
    }
};

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i);
    cartesian_tree::main();
    LL l, r; scanf("%lld%lld", &l, &r); l--;
    LL x = control::bsearch(l);
    control::setpos(l, x);
    control::pushall();
    rep (_, r - l) printf("%lld ", control::pump());
    puts("");
    return 0;
}
