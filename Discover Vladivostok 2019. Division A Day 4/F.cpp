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

int p[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
int n;
const LL mod = 1'000'000'009;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

vector<int> ps;
map<double, LL> ans;

vector<int> cur;

void compute() {
    auto s = cur;
    sort(range(s), greater<>());
    LL ans = 1;
    double apans = 0.0;
    for (int i = 0; i < s.size(); i++) {
        ans = ans * powmod(p[i], s[i] - 1) % mod;
        apans += log(p[i]) * (s[i] - 1);
    }
    ::ans[apans] = ans;
}

void dfs(int ptr, int s) {
    if (ptr == ps.size()) {
        compute();
        return;
    }
    if (ptr and ps[ptr] != ps[ptr - 1]) s = 0;
    for (; s < cur.size(); s++) {
        cur[s] *= ps[ptr];
        dfs(ptr + 1, s);
        cur[s] /= ps[ptr];
    }
    cur.push_back(ps[ptr]);
    dfs(ptr + 1, s);
    cur.pop_back();
}

int main() {
    int n; cin >> n;
    for (int f = 2; n > 1; f++) {
        while (n % f == 0) {
            n /= f;
            ps.push_back(f);
        }
    }
    dfs(0, 0);
    cout << ans.begin()->second << endl;
    return 0;
}
