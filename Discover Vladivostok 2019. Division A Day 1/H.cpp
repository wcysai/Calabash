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
char a[1 << 20], b[1 << 20];
int s[1 << 20], t[1 << 20];
int dp[1 << 20][2];

// 0 -> 0 [OK]
int cost1(bool last, int s, int t) {
    if (s < 0) {
        if (t == 0) return 0;
        if (t == 1) return 1;   // inc
        if (last) return 2;     // inc + modify
        return 1;               // modify
    } else {
        return s != t;          // modify
    }
}

// 1 -> 0 [OK]
int cost2(bool last, int s, int t) {
    if (s < 0) {
        if (t == 1) return 0;
        return 1;               // modify
    } else {
        if (s == 9) {
            if (t == 0) return 2;
            return 1;
        } else {
            return s + 1 != t;
        }
    }
}

// 0 -> 1
int cost3(bool last, int s, int t) {
    if (s < 0) {
        return 1 + (t != s);    // inc + (modify)
    } else {
        return min(1 + (t != s), (s != 9) + 1 + (t != 0)); 
            // (modify) + inc + (modify)
    }
}

// 1 -> 1
int cost4(bool last, int s, int t) {
    if (s < 0) {
        return 2 + (t != 0);
    } else {
        if (s == 9 and t == 0) return 0;
        if (s == 9 and t > 0) return 1;
        if (t == 0) return 1;
        if (t > 0) return 2;
        assert(0);
    }
}

int main() {
    scanf("%s%s", a, b); n = strlen(b);
    assert(strcmp(a, "0"));
    reverse(a, a + strlen(a)); reverse(b, b + strlen(b));
    memset(s, -1, sizeof s); memset(t, -1, sizeof t);
    for (int i = 0; a[i]; i++) s[i] = a[i] - '0';
    for (int i = 0; b[i]; i++) t[i] = b[i] - '0';
    dp[0][1] = 1;
    for (int i = 0; i < n; i++) {
        dp[i+1][0] = 
            min(dp[i][0] + cost1(i == n - 1, s[i], t[i]), 
                dp[i][1] + cost2(i == n - 1, s[i], t[i]));
        dp[i+1][1] = 
            min(dp[i][0] + cost3(i == n - 1, s[i], t[i]), 
                dp[i][1] + cost4(i == n - 1, s[i], t[i]));
    }
    cout << dp[n][0] << endl;
    return 0;
}
