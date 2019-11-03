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

int n, m, ptr;
char str[1024];

inline int id(int i, int j) {
    if (i < 0) i += n; if (i >= n) i -= n;
    if (j < 0) j += n; if (j >= n) j -= n;
    return i * n + j;
}

// apply a then b
vector<int> operator * (const vector<int>& a, const vector<int>& b) {
    vector<int> ret(n * n);
    rep (i, n * n) ret[i] = b[a[i]];
    return ret;
}

vector<int> power(vector<int> b, int e) {
    vector<int> ret(n * n); iota(range(ret), 0);
    while (e) {
        if (e & 1) ret = ret * b;
        b = b * b;
        e >>= 1;
    }
    return ret;
}

int readint() {
    int ret = 0;
    while (isdigit(str[ptr]))
        ret = ret * 10 + (str[ptr++] - '0');
    return ret;
}

vector<int> atom() {
    char dir = str[ptr++];
    int num = readint() - 1;
    vector<int> ret(n * n); iota(range(ret), 0);
    if (dir == 'L') {
        rep (j, n) ret[id(num, j)] = id(num, j + 1);
    } else if (dir == 'R') {
        rep (j, n) ret[id(num, j)] = id(num, j - 1);
    } else if (dir == 'U') {
        rep (i, n) ret[id(i, num)] = id(i + 1, num);
    } else if (dir == 'D') {
        rep (i, n) ret[id(i, num)] = id(i - 1, num);
    } else assert(0);
    return ret;
}

vector<int> seq() {
    vector<int> ret(n * n); iota(range(ret), 0);
    while (str[ptr] != '\0' and str[ptr] != ')') {
        if (str[ptr] == '(') {
            ptr++; // '('
            auto cur = seq();
            ptr++; // ')'
            ret = power(cur, readint()) * ret;
        } else {
            ret = atom() * ret;
        }
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", str);
    auto res = seq();
    rep (i, n) {
        rep (j, n) printf("%d ", res[i * n + j] + 1);
        puts("");
    }
    return 0;
}
