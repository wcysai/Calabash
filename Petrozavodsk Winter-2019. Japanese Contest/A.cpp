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
vector<LL> vec;

vector<LL> tokenize(string str) {
    vector<LL> res;
    reverse(range(str));
    while (str.size()) {
        if (isalpha(str.back())) {
            res.push_back(str.back() + 256);
            str.pop_back();
        } else {
            LL cur = 0;
            while (str.size() and isdigit(str.back())) {
                cur = cur * 10 + str.back() - '0';
                str.pop_back();
            }
            res.push_back(cur - 10000000000);
        }
    }
    return res;
}

int main() {
    cin >> n;
    string cur; cin >> cur;
    vec = tokenize(cur);
    while (n--) {
        cin >> cur;
        printf("%c\n", tokenize(cur) < vec ? '-' : '+');
    }
    return 0;
}
