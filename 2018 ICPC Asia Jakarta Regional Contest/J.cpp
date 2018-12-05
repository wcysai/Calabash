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
map<string, unsigned> mp;

void enum_substring(string s, int id) {
    int len = s.length();
    for (unsigned mask = 1; mask < (1u << len); mask++) {
        string str;
        rep (i, len) 
            if (mask & (1u << i)) str.push_back(s[i]);
        mp[str] |= 1 << id;
    }
}

int dp[16], ndp[16];

int main() {
    cin >> n;
    Rep (id, n) {
        string s; cin >> s;
        enum_substring(s, id);
    }
    
    for (int &x : dp) x = INT_MIN; dp[0] = 0;

    for (auto p : mp) {
        memcpy(ndp, dp, sizeof dp);
        unsigned mask = p.second;
        Rep (i, n)
            if (mask & (1 << i)) 
                ndp[i] = max(ndp[i], dp[i-1] + int(p.first.size())); 
        memcpy(dp, ndp, sizeof dp);
    }
    if (dp[n] < 0) dp[n] = -1;
    cout << dp[n] << endl;
    return 0;
}
