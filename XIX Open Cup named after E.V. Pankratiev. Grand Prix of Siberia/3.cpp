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

const int h = 16, w = 30;
int k;
char g[10005][16][30];
bool imposs[10005];
bool queried[16][30];

inline bool peek_mine(int s, int i, int j) {
    if (i < 0 || j < 0 || i >= h || j >= w) return 0;
    return g[s][i][j] == '*';
}

void complete(int s) {
    rep (i, h) {
        rep (j, w) {
            if (g[s][i][j] == '*') continue;
            g[s][i][j] = '0' + 
                peek_mine(s, i-1, j-1) + peek_mine(s, i-1, j) + peek_mine(s, i-1, j+1) + 
                peek_mine(s, i, j-1)   + peek_mine(s, i, j)   + peek_mine(s, i, j+1)   + 
                peek_mine(s, i+1, j-1) + peek_mine(s, i+1, j) + peek_mine(s, i+1, j+1);
        }
    }
}

mt19937 gen(time(NULL));
uint32_t seed;
uint32_t get_next() {
    return seed = uint64_t(48271) * seed % 2147483647;
}

int main() {
    scanf("%*d%*d%d", &k);
    vector<int> cand; 
    for (int s = 100; s <= 10000; s++) {
        int kk = 0; seed = s;
        while (kk < k) {
            int t = get_next(), r = (t / w) % h, c = t % w;
            if (g[s][r][c] == '*') continue;
            g[s][r][c] = '*';
            kk++;
        }
        complete(s);
        cand.push_back(s);
    }
    while (cand.size() > 1) {
        int i = gen() % h, j = gen() % w;
        printf("%d %d\n", i, j); fflush(stdout);
        char tp[12], c[3]; scanf("%s", tp);
        if (strcmp(tp, "Boom") == 0) c[0] = '*'; else scanf("%s", c);
        vector<int> next_cand;
        for (int x : cand) if (g[x][i][j] == c[0]) next_cand.push_back(x);
        cand = move(next_cand);
    }
    int s = cand[0];
    rep (i, h) rep (j, w) if (g[s][i][j] != '*') printf("%d %d\n", i, j);
    fflush(stdout);
//    cout << s << endl;
//    rep (i, h) { rep (j, w) putchar(g[s][i][j]); puts(""); }
    return 0;
}
