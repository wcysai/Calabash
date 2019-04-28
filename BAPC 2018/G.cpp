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
string str;

int cnt[3][3];
int cc[3];

void enter(char ch, int c[3]) {
    c[ch - 'A'] ++;
}

void enter(int c[3], char ch) {
    c[ch - 'A'] ++;
}

void leave(char ch, int c[3]) {
    c[ch - 'A'] --;
}

void leave(int c[3], char ch) {
    c[ch - 'A'] --;
}

int main() {
    cin >> n >> str; 
    rep (i, 3) cc[i] = count(range(str), 'A' + i);
    str += str; str += str[0];

    int ans = 0;

    rep (i, n) {
        if (i < cc[0]) enter(str[i], cnt[0]);
        else if (i < cc[0] + cc[1]) enter(str[i], cnt[1]);
        else enter(str[i], cnt[2]);
    }
    rep (i, n) {
        ans = max(ans, cnt[0][0] + cnt[1][1] + cnt[2][2]);
        leave(cnt[0], str[i]);
        leave(cnt[1], str[i + cc[0]]);
        leave(cnt[2], str[i + cc[0] + cc[1]]);
        enter(cnt[0], str[i + cc[0]]);
        enter(cnt[1], str[i + cc[0] + cc[1]]);
        enter(cnt[2], str[i + cc[0] + cc[1] + cc[2]]);
    }
     
    memset(cnt, 0, sizeof cnt);
    rep (i, n) {
        if (i < cc[0]) enter(str[i], cnt[0]);
        else if (i < cc[0] + cc[2]) enter(str[i], cnt[2]);
        else enter(str[i], cnt[1]);
    }
    rep (i, n) {
        ans = max(ans, cnt[0][0] + cnt[1][1] + cnt[2][2]);
        leave(cnt[0], str[i]);
        leave(cnt[2], str[i + cc[0]]);
        leave(cnt[1], str[i + cc[0] + cc[2]]);
        enter(cnt[0], str[i + cc[0]]);
        enter(cnt[2], str[i + cc[0] + cc[2]]);
        enter(cnt[1], str[i + cc[0] + cc[1] + cc[2]]);
    }
    cout << n - ans << endl;
    return 0;
}
