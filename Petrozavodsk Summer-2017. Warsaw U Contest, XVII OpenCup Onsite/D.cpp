#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARG__)
#else
#define _debug(fmt, ...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int cnt = 0;
void recursive_construct(int x) {
    if (x == 1) {
        printf("1");
        cnt++;
    } else if (x == 2) {
        printf("(1+1)");
        cnt+=2;
    } else if (x & 1) {
        printf("(");
        recursive_construct(x - 1);
        printf("+1)");
        cnt++;
    } else {
        printf("((1+1)*");
        recursive_construct(x / 2);
        printf(")");
        cnt+=2;
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        int k; cin >> k;
        recursive_construct(k);
        puts("");
        // cout << cnt << endl;
    }
    return 0;
}
