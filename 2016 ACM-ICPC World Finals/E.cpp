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

LL y, vl;
char l[70];
char pre[70];

ULL isqrt(ULL x) {
    if (x == 0) return 0;
    ULL t = sqrt(x);
    while (t * t < x) t++;
    if (t * t != x) return 0;
    return t;
}

LL qsolve(LL a, LL b, LL c) {
    double delta2 = double(b * b) + double(- 4 * c) * a;
    LL delta = sqrt(delta2);
    rep (_, 100) {
        static const LL m1 = 954854573, m2 = 1009775293;
        if (delta % m1 * delta % m1 == (b * b % m1 + (-4 * c) % m1 * a % m1) % m1 and 
            delta % m2 * delta % m2 == (b * b % m2 + (-4 * c) % m2 * a % m2) % m2)  goto cont;
        delta++;
    }
    return -1;
    cont:;
    if (delta <= 0) return -1;
    if ((-b + delta) % (2 * a)) return -1;
    return (-b + delta) / (2 * a);
}

int ncmp() {
    int l1 = strlen(l), l2 = strlen(pre);
    if (l1 != l2) return (l1 < l2) ? -1 : 1;
    return strcmp(l, pre);
}

bool cast_to_base(LL y, int b) {
    int ptr = 0;
    memset(pre, 0, sizeof pre);
    while (y) {
        if (y % b >= 10) return false;
        pre[ptr++] = '0' + y % b;
        y /= b;
    }
    reverse(pre, pre + ptr);
    return true;
}

int main() {
    scanf("%lld%s", &y, l); sscanf(l, "%lld", &vl);
    LL ans = 10;
    for (int b = 10; b <= 1000001; b++) 
        if (cast_to_base(y, b) and ncmp() <= 0)
            ans = b;
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i * 10 + j >= vl and (y - j) % i == 0)  
                ans = max(ans, (y - j) / i);
        }
    }
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (i * 100 + j * 10 + k >= vl) 
                    ans = max(ans, qsolve(i, j, k - y));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
