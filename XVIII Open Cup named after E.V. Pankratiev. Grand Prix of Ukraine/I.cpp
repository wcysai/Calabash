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

int n;
int sz[100005];
set<int> box[100005];
multiset<int> msz[100005];
int ans = INT_MAX;

int main() {
    scanf("%d", &n);
    rep (i, n) {
        scanf("%d", sz + i);
        rep (j, sz[i]) {
            int c; scanf("%d", &c);
            box[i].insert(c);
        }
        if (box[i].size() < sz[i]) ans = min(ans, (int)box[i].size() + 1);
    }
    rep (i, n)
        for (int c : box[i])
            msz[c].insert(box[i].size());
    rep (i, n) {
        vector<int> num;
        for (int c : box[i])
            msz[c].erase(msz[c].find(box[i].size()));
        for (int c : box[i]) {
            if (msz[c].size() == 0) num.push_back(INT_MAX / 2);
            else num.push_back(*msz[c].begin());
        }
        sort(range(num));
        int cur = num.size();
        for (int& val : num) {
            val += cur;
            cur--;
        }
        // cout << i << ' ' << num.size() << endl;

        ans = min(ans, *min_element(range(num)));
        for (int c : box[i])
            msz[c].insert(box[i].size());
    }
    cout << ans << endl;
    return 0;
}

/*
 7
 4 1 2 3 4
 1 1
 1 2
 1 3
 1 4
 7 4 7 4 4 7 7 4
 1 5


 5
 1 1
 2 1 2
 2 2 3
 2 4 5
 1 6
 */
