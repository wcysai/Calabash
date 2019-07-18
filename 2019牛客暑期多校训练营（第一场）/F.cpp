#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int x1, y1, x2, y2, x3, y3;
    while (~scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3)) {
        x2 -= x1; x3 -= x1;
        y2 -= y1; y3 -= y1;
        long long area = abs(1LL*x2 * y3 - 1LL*y2 * x3);
        printf("%lld\n", 11 * area);
    }
}
