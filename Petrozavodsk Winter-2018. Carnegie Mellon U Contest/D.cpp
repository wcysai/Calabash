#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

vector<char> vc;

bool raw_push_char(char ch) {
    if (vc.size() and ch == vc.back()) {
        vc.pop_back();
        return true;
    } else {
        vc.push_back(ch);
        return false;
    }
}

void push_char(char ch) {
    if (raw_push_char(ch)) return;
    if (vc.size() < 5) return;
    char a = vc.back(), b = vc.rbegin()[1];
    _debug("%c: %c, %c", ch, a, b);
    if (vc.rbegin()[2] == vc.rbegin()[4] and a == vc.rbegin()[2] and b == vc.rbegin()[3]) {
        vc.pop_back(); vc.pop_back(); vc.pop_back(); vc.pop_back(); vc.pop_back();
        push_char(b); push_char(a); push_char(b);
    }
}

char buf[1 << 20];
int main() {
    scanf("%s", buf);
    for (int i = 0; buf[i]; i++) {
        push_char(buf[i]);
    }
    // for (char ch : vc) putchar(ch); puts("");
    puts(vc.empty() ? "closed" : "open");
    return 0;
}

// babababcacacac
