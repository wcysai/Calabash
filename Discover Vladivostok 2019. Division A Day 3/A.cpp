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

int n, base;
int a[100005], b[100005];

char cvt(int x) {
    if (x < 10) return '0' + x;
    return 'A' + x - 10;
}

int main() {
    cin >> base >> n;
    if (n == 1) {
        puts("0");
        return 0;
    }
    for (int i = 0; i < n / 2; i++) a[i] = base - 1;
    for (int i = n / 2; i < n - 1; i++) a[i] = 0;
    a[n-1] = 1;
    reverse_copy(a, a + n, b);
    swap(a[n-1], a[n/2]);
    int borrow = 0;
    for (int i = n - 1; i >= 0; i--) {
        a[i] -= b[i] + borrow;
        if ((borrow = (a[i] < 0))) a[i] += base;
    }
    int ptr = 0;
    while (a[ptr] == 0) {
        ptr++;
        if (ptr >= n) {
            puts("0");
            return 0;
        }
    }
    for (int i = ptr; i < n; i++) putchar(cvt(a[i]));
    putchar('\n');
    return 0;
}
