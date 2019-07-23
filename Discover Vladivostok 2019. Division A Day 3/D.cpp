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
int s[1 << 25];

int main() {
    cin >> n; s[1] = 1;
    if (n == 1) {
        puts("1");
        puts("a");
        return 0;
    } else if (n == 2) {
        puts("2");
        puts("ab");
        return 0;
    } else if (n == 3) {
        puts("2");
        puts("aba");
        return 0;
    }
    for (int i = 2; i <= n; i++) {
        switch (i % 4) {
            case 0:
                s[i] = s[i/4];
                break;
            case 1:
                s[i] = s[(i+1)/2];
                break;
            case 2:
                s[i] = 0;
                break;
            case 3:
                s[i] = -s[(i-1)/2];
                break;
        }
    }
    puts("3");
    Rep (i, n) {
        if (s[i] < 0) putchar('a');
        if (s[i] == 0) putchar('b');
        if (s[i] > 0) putchar('c');
    }
    putchar('\n');
    return 0;
}
