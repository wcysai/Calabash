#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;
int main() {
    long long x, y, a, b;
    while (~scanf("%lld%lld%lld%lld", &x, &a, &y, &b)) {
        i128 v1 = i128(x) * b, v2 = i128(y) * a;
        if (v1 == v2) puts("=");
        if (v1 < v2) puts("<");
        if (v1 > v2) puts(">");
    }
    return 0;
}
