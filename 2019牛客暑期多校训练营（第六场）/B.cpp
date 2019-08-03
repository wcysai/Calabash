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

uint16_t bytes[8];

string generate(int l, int r) {
    char buf[1024], *ptr = buf;
    memset(buf, 0, sizeof buf);
    for (int i = 0; i < 8; i++) {
        if (i == l) *(ptr++) = ':';
        if (i < l || i >= r) ptr += sprintf(ptr, "%x", bytes[i]);
        if (i < l || (i >= r and i != 7)) *(ptr++) = ':';
    }
    if (buf[0] == ':') return string(":") + buf; else return buf;
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        memset(bytes, 0, sizeof bytes);
        string s; cin >> s;
        for (int i = 0; i < 128; i++)
            if (s[i] == '1') bytes[i / 16] |= 1u << ((15 - i) & 15);
        vector<string> cand = { generate(-1, -1) };
        for (int i = 0; i < 8; i++) for (int j = i + 2; j <= 8; j++)
            if (accumulate(bytes + i, bytes + j, 0) == 0)
                cand.push_back(generate(i, j));
        printf("Case #%d: %s\n", t, min_element(range(cand),
            [] (const string& a, const string& b) {
                if (a.size() != b.size()) return a.size() < b.size();
                return a < b;
            })->c_str());
    }
    return 0;
}
