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

typedef long long T;
typedef struct pt {
    T x, y;
    T operator , (pt a) { return x*a.x + y*a.y; }
    T operator * (pt a) { return x*a.y - y*a.x; }
    pt operator + (pt a) { return {x+a.x, y+a.y}; }
    pt operator - (pt a) { return {x-a.x, y-a.y}; }
    pt operator * (T k) { return {x*k, y*k}; }
    pt operator - () { return {-x, -y};}
    bool operator == (pt a) { return x == a.x and y == a.y; }
    bool operator != (pt a) { return x != a.x or y != a.y; }
    bool operator < (pt a) { if (x != a.x) return x < a.x; else return y < a.y; }
} vec;

ostream& operator << (ostream& lhs, pt& rhs){
    lhs << rhs.x << rhs.y;
    return lhs;
}

int n;
vector<pt> a[2];

vector<pt> hull(vector<pt> ps) {
    int n = ps.size();
    sort(range(ps));
    int k = 0;
    vector<pt> qs(n * 2);
    rep (i, n) {
        while(k>1&&(qs[k-1]-qs[k-2])*(ps[i]-qs[k-1])<=0) k--;
            qs[k++]=ps[i];
    }
    for(int i=n-2,t=k;i>=0;i--)
    {
        while(k>t&&(qs[k-1]-qs[k-2])*(ps[i]-qs[k-1])<=0) k--;
        qs[k++]=ps[i];
    }
    qs.resize(k-1);
    return qs;
}

bool test() {
    if (a[0].size() == 1) return false;
    auto h = hull(a[0]);
    for (int i = 0; i < h.size(); i++) {
        auto v = h[(i+1)%h.size()] - h[i];
        for (auto p : a[1]) 
            if ((p - h[i]) * v <= 0) goto cont;
        return true;
        cont:;
    }
    return false;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        a[0].clear(); a[1].clear();
        rep (i, n) {
            int x, y, z; scanf("%d%d%d", &x, &y, &z); if (z < 0) z = 0;
            a[z].push_back(pt{x, y});
        }
        rep (i, 2) {
            sort(range(a[i]));
            a[i].erase(unique(range(a[i])), a[i].end());
        }
        if (a[0].size() == 0 || a[1].size() == 0) {
            puts("Successful!");
            continue;
        }
        if (a[0].size() == 1 and a[1].size() == 1) {
            puts(a[0][0] != a[1][0] ? "Successful!" : "Infinite loop!");
            continue;
        }
        if (test() || (swap(a[0], a[1]), test())) {
            puts("Successful!");
        } else {
            puts("Infinite loop!");
        }
    }
    return 0;
}
