#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;
typedef unsigned long long ULL;

int T;

int n;
vector<string> str;

bool is_prefix_of(const string& l, const string& r) {
    int len = l.size();
    rep (i, len) if (l[i] != r[i]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        str.resize(n);
        rep (i, n) cin >> str[i];
        sort(range(str), [] (const string& l, const string &r) -> bool {
            return l.size() < r.size();
        });
        rep (i, n - 1) {
            if (!is_prefix_of(str[i], str[n-1])) {
                puts("Impossible");
                goto next;
            }

        }
        printf("%d\n", (int)str.back().size());
        next:;
    }

    return 0;
}
