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

int xx;
map<int, int> d;
map<int, int> pre;
queue<int> q;

void closure(int x) {
    if (x == 1) throw d[x];
    q.push(x + 1);
    if (x % 2 == 0 and d.count(x / 2) == 0) {
        d[x / 2] = d[x];
        pre[x / 2] = x;
        closure(x / 2);
    }
    if (x % 3 == 0 and d.count(x / 3) == 0) {
        d[x / 3] = d[x];
        pre[x / 3] = x;
        closure(x / 3);
    }
}

int main() {
    cin >> xx;
    try {
        d[xx] = 0;
        closure(xx);
        while (q.size()) {
            int x = q.front(); q.pop();
            if (d.count(x)) continue;
            d[x] = d[x - 1] + 1;
            pre[x] = x - 1;
            closure(x);
        }
    } catch (int ans) {
        printf("%d\n", ans);
        vector<int> out = {1};
        int cur = 1;
        while (cur != xx) {
            cur = pre[cur];
            out.push_back(cur);
        }
        reverse(range(out));
        for (int x : out) printf("%d ", x);
    }
    return 0;
}
