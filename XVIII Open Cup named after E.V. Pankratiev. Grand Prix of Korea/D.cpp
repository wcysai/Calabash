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

int n;
bool occur[256];
char str[1 << 20];

int main() {
    scanf("%s", str);
    n = strlen(str);
    int cnt = 0;
    int lpos = 0, rpos = 0;
    rep (i, n) {
        if (!occur[str[i]]) {
            _debug("+ %d", i);
            if (lpos) cnt++;
            cnt++;
            occur[str[i]] = true;
            lpos = 0;
            rpos = i;
        } else {
            redo:
            while (lpos <= rpos) {
                if (str[lpos] == str[i]) {
                    lpos++;
                    goto cont;
                }
                lpos++;
            }
            _debug("%d", i);
            cnt++;
            lpos = 0;
            rpos = i - 1;
            goto redo;
        }
        cont:;
    }
    if (lpos) cnt++;
    cout << cnt << endl;
    return 0;
}
