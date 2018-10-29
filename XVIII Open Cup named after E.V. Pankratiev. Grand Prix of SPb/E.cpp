#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)

typedef long long LL;
typedef unsigned long long ULL;

vector<ULL> seq;
void gcd(ULL x, ULL y) {
    if (x == 0) return;
    seq.push_back(y / x);
    gcd(y % x, x);
}

vector<ULL> getseq(ULL x, ULL y) {
    seq.clear();
    gcd(x, y);
    return move(seq);
}

void print_vec(vector<ULL> vec) {
    for (ULL x : vec)
        printf("%llu ", x);
    puts("");
}

// typedef LL i128;
typedef __int128_t i128;
typedef pair<i128, i128> P;

P cal(i128 a, i128 b, i128 c, i128 d) {
    i128 x = a / b + 1; if (x * d < c) return {x, 1};
    if (!a) return {1, d / c + 1};
    if (a <= b && c <= d) {
        P t = cal(d, c, b, a);
        swap(t.first, t.second);
        return t;
    }
    x = a / b;
    P t = cal(a - b * x, b, c - d * x, d);
    t.first += t.second * x;
    return t;
}

P work(i128 a, i128 b, i128 c, i128 d) {
    i128 t = __gcd(a, b); a /= t; b /= t;
    t = __gcd(c, d); c /= t; d /= t;
    return cal(a, b, c, d);
}


bool check(LL x, LL y) {
    LL g = __gcd(x, y);
    x /= g; y /= g;
    if (y <= 1'000'000'000) {
        printf("%d %d\n", (int)x, (int)y);
        return true;
    }
    return false;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        char str[32];
        scanf("%s", str);
        LL num, denom = 2'000'000'000'000'000'000;
        sscanf(str + 2, "%lld", &num);
        num *= 2;
        if (num == 0) {
            printf("0 1\n");
            continue;
        }
        if (check(num - 1, denom)) continue;
        i128 u, v, g;
        _debug("%lld %lld %lld %lld", num - 1, denom, num + 1, denom);
        tie(u, v) = work(num - 1, denom, num + 1, denom);
        g = __gcd(u, v); u /= g; v /= g;
        printf("%lld %lld\n", (LL)u, (LL)v);
    }
    return 0;
}

// 666666666666666666 1000000000000000000
/*
2
0.0990895457583377588
0.1005842141794236744
 */
