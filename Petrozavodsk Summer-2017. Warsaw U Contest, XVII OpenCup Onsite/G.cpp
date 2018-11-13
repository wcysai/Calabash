#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(fmt, ...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n;
int a[100005];

void print(const vector<int> &cv) {
    int sz = cv.size();
    printf("%d", sz - 1);
    for (int i = 1; i < sz; i++) printf(" %d", cv[i]);
    puts("");
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        vector<int> down, up;
        scanf("%d", &n);
        rep (i, n) scanf("%d", a + i);
        down.push_back(INT_MAX);
        up.push_back(INT_MIN);
        rep (i, n) {
            bool flag1 = a[i] < down.back(), flag2 = a[i] > up.back();
            if (flag1 and flag2) {
                if (i == n - 1) down.push_back(a[i]);
                else if (a[i] < a[i + 1]) {
                    up.push_back(a[i]);
                } else {
                    down.push_back(a[i]);
                }
            } else if (flag1) {
                down.push_back(a[i]);
            } else if (flag2) {
                up.push_back(a[i]);
            } else {
                puts("NO");
                goto next_case;
            }
        }
        puts("YES");
        print(up);
        print(down);
        next_case:;
    }
    return 0;
}
