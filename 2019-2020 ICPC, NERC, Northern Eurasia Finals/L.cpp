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

int n, l, k, ptr;
char str[1 << 20];
string ans[1 << 10];

int main() {
    scanf("%d%d%d", &n, &l, &k);
    scanf("%s", str); sort(str, str + n * l);
    int left = 0, right = k - 1;
    rep (i, l) {
        for (int j = left; j <= right; j++) ans[j].push_back(str[ptr++]);
        while (ans[left].back() != ans[right].back()) left++;
    }
    rep (i, n) while (ans[i].size() < l) ans[i].push_back(str[ptr++]);
    rep (i, n) puts(ans[i].c_str());
    return 0;
}
