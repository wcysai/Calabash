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
 
#define x1 wisfueis
#define x2 auewuekus
#define y1 seufwgf
#define y2 fewufuwo
 
struct bit_rupq {
    vector<LL> ys;
    vector<int> tr;
 
    bit_rupq(vector<LL>&& _ys) : ys(move(_ys)) {
        sort(range(ys)); ys.erase(unique(range(ys)), ys.end());
        tr.resize(ys.size() + 1);
    }
 
    void add(int n, int x) {
        while (n) { tr[n] += x; n &= n - 1; }
    }
    
    void add(LL l, LL r, int x) {
        l = upper_bound(range(ys), l) - ys.begin();
        r = upper_bound(range(ys), r) - ys.begin();
 
        add(l - 1, -x); add(r, x);
    }
 
    int query(LL n) {
        int ans = 0;
        n = upper_bound(range(ys), n) - ys.begin();
        while (n < tr.size()) { ans += tr[n]; n += n & -n; }
        return ans;
    }
};
 
const int MAXN = 100005;
int n;
LL X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN];
LL x1[MAXN], y1[MAXN], x2[MAXN], y2[MAXN];
 
struct event { 
    LL x, y, y2; 
    int type;
    event(LL x, int type, LL y, LL y2 = 0) : x(x), y(y), y2(y2), type(type) {}
    bool operator < (const event& ev) const {
        return make_pair(x, type) < make_pair(ev.x, ev.type);
    }
};
 
template <typename T>
LL getans(T fn) {
    LL minx = LLONG_MAX, maxx = LLONG_MIN;
    rep (i, n) {
        LL xx1 = fn(X1[i], Y1[i]).first;
        LL xx2 = fn(X1[i], Y2[i]).first;
        LL xx3 = fn(X2[i], Y1[i]).first; 
        LL xx4 = fn(X2[i], Y2[i]).first;
        minx = min({minx, xx1, xx2, xx3, xx4});
        maxx = max({maxx, xx1, xx2, xx3, xx4});
        tie(x1[i], y1[i]) = fn(X1[i], Y1[i]);
        tie(x2[i], y2[i]) = fn(X2[i], Y2[i]);
    }
    return (minx + maxx) / 2;
}
 
template <typename T>
bool check(LL val, T fn) {
    vector<event> events;
    vector<LL> ys;
    rep (i, n) {
        events.emplace_back(X1[i], -1, Y1[i], Y2[i]);
        events.emplace_back(X2[i], 1, Y1[i], Y2[i]);
        ys.push_back(Y1[i]);
        ys.push_back(Y2[i]);
    }
    rep (i, n) {
        tie(x1[i], y1[i]) = fn(2 * val - x1[i], y1[i]); 
        tie(x2[i], y2[i]) = fn(2 * val - x2[i], y2[i]);
        events.emplace_back(x1[i], 0, y1[i]);
        events.emplace_back(x1[i], 0, y2[i]);
        events.emplace_back(x2[i], 0, y1[i]);
        events.emplace_back(x2[i], 0, y2[i]);
        ys.push_back(y1[i]); 
        ys.push_back(y2[i]);
    }
     
    bit_rupq bit(move(ys));
 
    sort(range(events));
 
    for (auto e : events) {
        if (e.type == 0) {
            if (!bit.query(e.y)) return false; 
        } else if (e.type == -1) {
            bit.add(e.y, e.y2, 1);
        } else if (e.type == 1) {
            bit.add(e.y, e.y2, -1);
        }
    }
    return true;
}
 
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        vector<tuple<LL, LL, LL>> axes;
 
        scanf("%d", &n); axes.clear();
        rep (i, n) {
            scanf("%lld%lld%lld%lld", X1 + i, Y1 + i, X2 + i, Y2 + i);
            X1[i] *= 2; Y1[i] *= 2;
            X2[i] *= 2; Y2[i] *= 2;
        }
        
        LL val;
        
        _debug("(x, y)"); 
        val = getans([](LL x, LL y) { return make_pair(x, y); }); 
        if (check(val, [] (LL x, LL y) { return make_pair(x, y); })) {
            if (val & 1) axes.emplace_back(2, 0, val); 
            else axes.emplace_back(1, 0, val / 2);
        }
 
        _debug("(y, x)"); 
        val = getans([] (LL x, LL y) { return make_pair(y, x); });
        if (check(val, [] (LL x, LL y) { return make_pair(y, x); })) {
            if (val & 1) axes.emplace_back(0, 2, val);
            else axes.emplace_back(0, 1, val / 2);
        }
 
        _debug("(x+y, x-y)"); 
        val = getans([] (LL x, LL y) { return make_pair(x+y, x-y); });
        if (check(val, [] (LL x, LL y) { return make_pair((x+y)/2, (x-y)/2); })) {
            if (val & 1) axes.emplace_back(2, 2, val);
            else axes.emplace_back(1, 1, val / 2);
        }
         
        _debug("(x-y, x+y)"); 
        val = getans([] (LL x, LL y) { return make_pair(x-y, x+y); });
        if (check(val, [] (LL x, LL y) { return make_pair((x+y)/2, (y-x)/2); })) {
            if (val & 1) axes.emplace_back(2, -2, val);
            else axes.emplace_back(1, -1, val / 2);
        }
 
        printf("%d\n", int(axes.size()));
        sort(range(axes), greater<>());
        for (auto pr : axes) {
            LL a, b, c; tie(a, b, c) = pr;
            printf("%lld %lld %lld ", a, b, c); 
        }
        puts("");
    } 
    return 0;
}