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

#define tm regufwo

LL a, b, c, d, v, t;

LL tm[2000006], press[2000006], acc[2000006];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> a >> b >> c >> d >> v >> t;

        int cur = 1;
        LL nextb = a, nextd = c;
        tm[0] = 0; press[0] = b + d;
        while (nextb != nextd) {
            if (nextb < nextd) {
                tm[cur] = nextb;
                press[cur] = b;
                nextb += a;
            } else {
                tm[cur] = nextd;
                press[cur] = d;
                nextd += c;
            }
            if (tm[cur] - tm[cur - 1] > v) press[cur]--;
            cur++;
        }
        bool flag = false;
        if (nextb - tm[cur - 1] > v) {
            flag = true;
            press[0]--;
        }
        partial_sum(press, press + cur, acc + 1);
        LL tot = acc[cur] * (t / nextb);
        t %= nextb;
        int p = lower_bound(tm, tm + cur, t + 1) - tm;
        tot += acc[p];
        if (flag == false) tot--;
        cout << tot << endl;
    }
    return 0;
}
