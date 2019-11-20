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

string n;

char add(char a, char b) {
    return '0' + (a - '0' + b - '0') % 10;
}

char mul(char a, char b) {
    return '0' + (a - '0') * (b - '0') % 10;
}

bool cmp(const string& a, const string& b) {
    return a.length() < b.length() or (a.length() == b.length() and a < b);
}

string sqr(string a) {
    string ret(a.size() * 2 - 1, '0');
    rep (i, a.size()) rep (j, a.size())
        ret[i+j] = add(ret[i+j], mul(a[i], a[j]));
    return ret;
}

void dfs(string s) {
    s.push_back('0');
    if (s.size() * 2 - 1 > n.size()) return;
    while (s.back() <= '9') {
        string sq = sqr(s);
        if (sq == n) throw s;
        if (sq.substr(0, s.size()) == n.substr(0, s.size())) dfs(s);
        s.back()++;
    }
}

int main() {
    cin >> n;
    try {
        dfs("");
    } catch (string s) {
        cout << s << endl;
        return 0;
    }
    cout << -1 << endl;
    return 0;
}
