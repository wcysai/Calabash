#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define Rep(i, n) for (int i = 1; i <=n; i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

vector<int> vy;
int n, l, r;
int x[100005], y[100005], s[100005];

struct segtree
{
    int val[6*800005],lzy[6*800005];
    void Lazy(int k)
    {
        if(!lzy[k]) return;
        lzy[k*2]+=lzy[k];lzy[k*2+1]+=lzy[k];
        val[k*2]+=lzy[k];val[k*2+1]+=lzy[k];
        lzy[k]=0;
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            lzy[k]+=v;val[k]+=v;
            return;
        }
        Lazy(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v);update(k*2+1,mid+1,r,x,y,v);
        val[k]=max(val[k*2],val[k*2+1]);
    }
    int query()
    {
        return val[1];
    }
}seg;

struct event {
    int x;
    int yl, yr;
    int delta;

    event(int x, int yl, int yr, int delta) :
    x(x), yl(yl), yr(yr), delta(delta) {}

    bool operator < (const event& rhs) const {
        return x < rhs.x;
    }

    void process()
    {
        // TODO: Implement event process
        // add [yl, yr] with delta
        seg.update(1,1,12*n,yl,yr,delta);
    }
};


int getId(int x) {
    return lower_bound(range(vy), x) - vy.begin();
}

vector<event> events;

int main() {
    scanf("%d%d%d", &n, &l, &r);
    rep (i, n) {
        scanf("%d%d%d", x+i, y+i, s+i);
        x[i] -= 1000000000;
        vy.push_back(y[i]-r);
        vy.push_back(y[i]+r);
        vy.push_back(y[i]-(l-1));
        vy.push_back(y[i]+(l-1));

        vy.push_back(y[i]-r+1);
        vy.push_back(y[i]+r-1);
        vy.push_back(y[i]-(l-1)+1);
        vy.push_back(y[i]+(l-1)-1);

        vy.push_back(y[i]-r-1);
        vy.push_back(y[i]+r+1);
        vy.push_back(y[i]-(l-1)-1);
        vy.push_back(y[i]+(l-1)+1);
    }
    sort(range(vy));
    vy.resize(unique(range(vy)) - vy.begin());
    rep (i, n) {
        int y1 = getId(y[i]-r),     y2 = getId(y[i]+r);
        int y3 = getId(y[i]-(l-1)), y4 = getId(y[i]+(l-1));
        events.emplace_back(x[i],       y1+1, y2 + 1, s[i]);
        events.emplace_back(x[i]+r-l+1, y3+1, y4 + 1, -s[i]);
        events.emplace_back(x[i]+r+l,   y3+1, y4 + 1, s[i]);
        events.emplace_back(x[i]+r+r+1, y1+1, y2 + 1, -s[i]);
    }
    sort(range(events));
    int ans = 0;
    auto lptr = events.begin(), rptr = lptr;
    while (rptr != events.end()) {
        lptr = rptr;
        while (rptr != events.end() && rptr->x == lptr->x) {
            rptr->process();
            rptr++;
        }
        ans = max(ans, seg.query());    // TODO: implement query
    }
    cout << ans << endl;
    return 0;
}
