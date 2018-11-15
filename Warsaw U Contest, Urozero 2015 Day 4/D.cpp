#pragma GCC optimize(3)
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

mt19937_64 gen(time(NULL));

int n, m;
int cour[512000];
vector<int> occ[512000];
bool fail[512000];
int rec[64];

inline int random_select(int l, int r) {
    int x = gen() % (r - l) + l;
    return cour[x];
}

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, n) {
        scanf("%d", cour + i);
        occ[cour[i]].push_back(i);
    }
    while (m--) {
        int a, b; scanf("%d%d", &a, &b); b++;
        rep (_, 35) fail[rec[_]] = false;
        rep (_, 35) {
            int d = random_select(a, b);
            rec[_] = d;
            if (fail[d]) continue;
            fail[d] = true;
            if (occ[d].size() + occ[d].size() <= b - a) {
                continue;
            }
            int num = lower_bound(range(occ[d]), b) - lower_bound(range(occ[d]), a);
            if (num + num > b - a) {
                printf("%d\n", d);
                goto cont;
            }
        }
        printf("%d\n", 0);
        cont:;
    }
    return 0;
}
