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

int n, m;
int qn;
int ans[200005];

struct bit_inner {
    int N;
    vector<int> val, tr;

    void insert(int x) {
        val.push_back(x);
    }

    void inflate() {
        sort(range(val));
        val.erase(unique(range(val)), val.end());
        tr.resize(val.size() + 1);
        N = tr.size();
    }

    int find(int x) { return upper_bound(range(val), x) - val.begin(); }

    int _sum(int n) {
        int ans = 0;
        while (n) { ans += tr[n]; n &= n - 1; }
        return ans;
    }

    int sum(int x, int y) {
        x = find(x - 1); y = find(y);
        return _sum(y) - _sum(x);
    }

    void add(int n, int x) {
        n = find(n);
        while (n < N) tr[n] += x, n += n & -n;
    }
};

struct bit_outer {
    int N;
    vector<bit_inner> tr;

    void init(int n) { tr.resize(N = n + 5); }

    void insert(int n, int y) {
        while (n < N) { tr[n].insert(y); n += n & -n; }
    }

    void inflate() { for (auto& b : tr) b.inflate(); }

    int query(int n, int x, int y) {
        int ans = 0;
        while (n) { ans += tr[n].sum(x, y); n &= n - 1; }
        return ans;
    }

    void add(int n, int y, int d) {
        while (n < N) { tr[n].add(y, d); n += n & -n; }
    }
} bit;

struct event {
    // 0: add point
    // 1: query
    bool type; int8_t dir;
    //     [l, r]
    int x, l, r, qid;

    event(int dir, int x, int y) : type(0), dir(dir), x(x), l(y) {};
    event(int dir, int x, int l, int r, int qid) :
        type(1), dir(dir), x(x), l(l), r(r), qid(qid) {};

    void dryrun() {
        if (type == 0) bit.insert(x, l);
    }

    void process() {
        if (type == 0) { // add point
            bit.add(x, l, dir);
        } else { // query
            if (dir > 0) ans[qid] += bit.query(x, l, r);
            else ans[qid] -= bit.query(x, l, r);
        }
    }

    void print() {
        if (type == 0)
            _debug("%c [ADD] (%d, %d)", dir > 0 ? '+' : '-', x, l);
        else
            _debug("%c [QUERY] %d [%d, %d] id=%d", dir > 0 ? '+' : '-', x, l, r, qid);

    }
};

vector<event> events;

namespace gen_seq {
    int a[200005];
    map<int, int> mp;

    void remove(int id) {
        auto it = mp.find(id);
        events.emplace_back(-1, it->first, it->second);
        mp.erase(it);
    }

    void enter(int id, int val) {
        mp[id] = val;
        events.emplace_back(1, id, val);
    }

    void enter2(int id, int val) {
        auto it = prev(mp.upper_bound(id)), nit = next(it);
        if (nit->first == it->first + 1) { // x
            remove(id);
            enter(id, val);
        } else if (it->first == id) { // x....
            enter(id + 1, it->second);
            remove(id);
            enter(id, val);
        } else if (id + 1 == nit->first) { // ....x
            enter(id, val);
        } else {    // ..x..
            enter(id + 1, it->second);
            enter(id, val);
        }
        // merge identical parts
        it = mp.find(id);
        while (prev(it)->second == it->second) remove(prev(it)->first);
        while (next(it)->second == it->second) remove(next(it)->first);
    }

    void run() {
        Rep (i, n) scanf("%d", a + i);
        mp[0] = -1; mp[n+1] = -1;
        Rep (i, n) if (i == 1 or a[i] != a[i-1]) enter(i, a[i]);
        while (true) {
            int tp; if (scanf("%d", &tp) != 1) break;
            if (tp == 1) {
                int pos, v; scanf("%d%d", &pos, &v);
                int ppos, pv; tie(ppos, pv) = *prev(mp.upper_bound(pos));
                if (pv == v) continue;
                enter2(pos, v);
            } else if (tp == 2) {
                qn++;
                int l, r, x, y;  scanf("%d%d%d%d", &l, &r, &x, &y);
                events.emplace_back(1, r, x, y, qn);
                events.emplace_back(-1, l - 1, x, y, qn);
                if (mp.count(l) == 0) {
                    auto it = prev(mp.lower_bound(l));
                    if (it->second >= x and it->second <= y)
                        ans[qn]++;
                }
            }
        }
        for (auto& r : events) r.print();
    }
}

int main() {
    scanf("%d%d", &n, &m);
    bit.init(n);
    gen_seq::run();
    for (auto& ev : events) ev.dryrun();
    bit.inflate();
    for (auto& ev : events) ev.process();
    Rep (i, qn) printf("%d\n", ans[i]);
    return 0;
}
