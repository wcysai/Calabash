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

vector<const char *> seq;

int main() {
    ULL a, b; cin >> a >> b;
    while (a % 2 == 0 and b % 2 == 0) a /= 2, b /= 2;
    while (a != b) {
        while (a % 2 == 0) { seq.push_back("B+=B"); a /= 2; }
        while (b % 2 == 0) { seq.push_back("A+=A"); b /= 2; }
        if (a == b) break;
        if (a > b) {
            seq.push_back("A+=B");
            a += b;
        } else {
            seq.push_back("B+=A");
            b += a;
        }
    }
    cout << seq.size() << endl;
    for (auto op : seq) cout << op << endl;
    return 0;
}
