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

#define next teuowhe

int l, n;
int pos;
string tape, text;
int next[1 << 18][128];

int main() {
    getline(cin, tape); l = tape.size(); tape += tape;
    rep (i, l + l) {
        next[i][tape[i]] = 0;
        for (int j = i - 1; j >= 0 and tape[j] != tape[i]; j--) 
            next[j][tape[i]] = i - j;
    }
    rep (i, l) rep (ch, 128) next[i+l][ch] = next[i][ch];
    LL ans = 0;
    while (getline(cin, text)) {
        int cur = 0;
        rep (i, text.size()) if (text[i] != ' ')
            cur = max(cur, next[pos + i][text[i]]);
        ans += cur + 1;
        pos = ans % l;
    }
    cout << ans << endl;
    return 0;
}
