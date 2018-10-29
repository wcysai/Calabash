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

int n;
int a[512];
int mid;

bool compare(int x, int y) {
    if (x == y) return false;
    int res;
    printf("? %d %d\n", x, y);
    fflush(stdout);
    scanf("%d", &res);
    return res;
}

int main() {
    srand(time(NULL));
    scanf("%d", &n);
    rep (i, n) a[i] = i + 1;
    random_shuffle(a, a + n);
    int piv = a[0];
    mid = partition(a, a + n, [piv] (int x) -> bool {
        if (x == piv) return true;
        return compare(x, piv);
    }) - a;
    sort(a, a + mid, compare);
    sort(a + mid, a + n, compare);
    if (n <= 2 or compare(a[0], a[n - 1])) {
        puts("! YES");
    } else {
        puts("! NO");
        printf("%d ", n);
    }
    rep (i, n) printf("%d ", a[i]);
    return 0;
}
