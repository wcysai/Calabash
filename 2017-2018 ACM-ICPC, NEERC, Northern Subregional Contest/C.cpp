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

char cid[256];
int mat[32][32];
int n;
char str[1 << 20];

int main() {
#define FILENAME "consonant"
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
    int cnt = 0;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        auto ptr = strchr("aeiouwy", ch);
        if (ptr) cid[ch] = -1;
        else cid[ch] = cnt++;
    }
    assert(cnt == 19);

    scanf("%s", str); n = strlen(str);
    for (int i = 1; i < n; i++) {
        int s1 = cid[str[i-1]], s2 = cid[str[i]];
        if (s1 >= 0 and s2 >= 0) mat[s1][s2]++;
    }

    pair<int, unsigned> ans(0, 0);
    for (unsigned mask = 0; mask < (1 << 19); mask++) {
        int cnt = 0;
        rep (i, 19) rep (j, 19) if (bool(mask & (1 << i)) != bool(mask & (1 << j)))
            cnt += mat[i][j];
        ans = max(ans, make_pair(cnt, mask));
    }
    unsigned mask = ans.second;
    rep (i, n) if (cid[str[i]] >= 0 and (mask & (1ull << cid[str[i]])))
        str[i] = toupper(str[i]);
    puts(str);
    return 0;
}
