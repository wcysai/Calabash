#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 1 << 20;

typedef array<int, 20> arr;
arr def;

int sadd(int& a, int b) {
    a += b;
    if (a < 0) a = INT_MAX;
    return a;
}

struct Trie {
    int n;
    int ch[MAXN][2];
    int cnt[MAXN];

    void rewind() { 
        rep (i, n + 1)
            ch[i][0] = ch[i][1] = cnt[i] = 0;
        n = 0;
    }

    void insert(const char* str) {
        int cur = 0;
        while (*str) {
            bool x = *str - 'a';
            if (!ch[cur][x]) {
                ch[cur][x] = ++n;
                ch[n][0] = ch[n][1] = 0;
            }
            cur = ch[cur][x]; str++;
        }
//        cout << cur << endl;
        cnt[cur]++;
    }

    arr trav(int n, int dep) {
        arr cur;
        rep (i, 20) cur[i] = (i == 0);
        for (int c : ch[n]) if (c) {
            arr ret = trav(c, dep);
            for (int i = dep; i; i--) sadd(cur[i], ret[i-1]);
        } else {
            arr ret = def;
            for (int i = dep; i; i--) sadd(cur[i], ret[i-1]);
        }
        int sz = cnt[n], ptr = dep;
        while (sz and ptr >= 0) {
            if (cur[ptr] >= sz) {
                cur[ptr] -= sz;
                sz = 0;
            } else {
                sz -= cur[ptr];
                ptr--;
            }
        }
        if (sz) throw 0;
        return cur;
    }
} trie;


int n;
char buf[1 << 20];
int main() {
    def[0] = 1; for (int i = 1; i < 20; i++) def[i] = 2*def[i-1];
    while (scanf("%d", &n), n) {
        trie.rewind();
        rep (i, n) { 
            scanf("%s", buf); trie.insert(buf);
        }
        int ans = 0;
        while (true) {
            try {
                trie.trav(0, ans);
                break;
            } catch (...) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
