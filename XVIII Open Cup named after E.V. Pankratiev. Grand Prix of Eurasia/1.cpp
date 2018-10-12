#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;
typedef unsigned long long ULL;

string str;

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> str;

        vector<int> res;
        while (str.size() >= 4) {
            reverse(str.begin() + str.size() - 4, str.end());
            int r = 0;
            rep (i, 4) {
                r = r * 2 + str.back() - '0';
                str.pop_back();
            }
            res.push_back(r);
        }

        if (str.size()) {
            reverse(range(str));
            int r = 0;
            while (str.size()) {
                r = r * 2 + str.back() - '0';
                str.pop_back();
            }
            res.push_back(r);
        }
        reverse(range(res));
        for (int x : res) printf("%X", x);
        puts("");
    }

    return 0;
}

// 011101001010110110000001000
