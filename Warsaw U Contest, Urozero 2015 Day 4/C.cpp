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

int k, p, q, tot;
int num[1 << 20];
int res[1 << 20];

bool check() {
    for (int i = 1; i < tot; i++) 
        if (res[i] == res[i-1]) return false;
    return true;
}

[[noreturn]] void yield() {
    if (check()) {
        rep (i, tot) printf("%d%c", res[i], i == tot - 1 ? '\n' : ' ');
    } else puts("0");
    exit(0);
}

int main() {
    scanf("%d%d%d", &k, &p, &q);
    Rep (i, k) scanf("%d", num + i);
    tot = accumulate(num + 1, num + 1 + k, 0);
    if (tot == 1) {
        if (p == q and num[p] == 1) {
            printf("%d\n", p);
        } else {
            puts("0");
        }
    } else {
        num[p]--; num[q]--;
        res[0] = p; res[tot - 1] = q;
        if (num[p] < 0 or num[q] < 0) {
            puts("0");
            return 0;
        }
        if (tot == 2) {
            yield();
        } else if (tot == 3) {
            Rep (i, k) if (num[i]) res[1] = i;
            yield();
        } else {
            set<pair<int, int>> s;
            Rep (i, k) if (num[i]) s.emplace(-num[i], i == q ? -i : i);
            for (int i = 1; i < tot - 1; i++) {
                auto it = s.begin();
                int cur = abs(it->second);
                if (cur == res[i - 1]) {
                    it++;
                    if (it == s.end()) {
                        puts("0");
                        return 0;
                    } 
                    cur = abs(it->second);
                }
                res[i] = cur;
                auto np = make_pair(it->first + 1, it->second);
                s.erase(it);
                if (np.first != 0) s.insert(np);
            }
            yield();
        }
    }
    return 0;
}
