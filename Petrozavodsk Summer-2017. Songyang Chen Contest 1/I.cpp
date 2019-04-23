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

int n;
int a[100005];
mt19937 gen(time(NULL));

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", a + i);
    int c[2] = {0, 0};
    rep (i, n) c[a[i] & 1]++;
    if (c[0] > c[1]) puts("2 0");
    else puts("2 1");
    return 0;
}
