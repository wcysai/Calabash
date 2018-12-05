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

string str;

int main() {
    cin >> str;
    int c0 = count(range(str), '0');
    int c1 = count(range(str), '1');
    if (c0 < c1) {
        for (char ch : str) cout << '0';
    } else if (c0 > c1) {
        for (char ch : str) cout << '1';
    } else {
        int flag = str[0] - '0';
        rep (i, str.size()) {
            if (i == 0) cout << 1 - flag;
            else cout << flag;
        }
    }
    return 0;
}
