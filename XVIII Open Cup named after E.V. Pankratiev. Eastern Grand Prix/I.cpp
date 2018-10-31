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

int len;
string str;
bool occ;

bool ok() {
    for (char& ch : str) {
        if (ch == 'A') {
            if (occ) return false;
        } else if (ch == '!') {
            occ = true;
        } else return false;
    }
    return str.front() == 'A' and str.back() == '!';
}

int main() {
    cin >> str;
    len = str.size();
    if (ok()) {
        puts("Panic!");
    } else {
        puts("No panic");
    }
    return 0;
}
