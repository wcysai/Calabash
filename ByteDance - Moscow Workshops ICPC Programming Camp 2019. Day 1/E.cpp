#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) ((void) 0)
#endif

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <=(n); i++)
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
char adj[1024][1024];
bitset<1024> bs[1024];

uint8_t decchr(char ch) {
    if (isupper(ch)) return ch - 'A';
    if (islower(ch)) return ch - 'a' + 26;
    if (isdigit(ch)) return ch - '0' + 52;
    if (ch == '+') return 62;
    if (ch == '/') return 63;
    assert(0);
}

int main() {
    int kase = 0;
    while (scanf("%d", &n), n) {
        kase++;
        for (int i = 0; i < n; i++) {
            scanf("%s", adj[i]); m = strlen(adj[i]);
            bs[i].reset();
            for (int j = 0; adj[i][j]; j++) {
                uint8_t x = decchr(adj[i][j]);
                for (int k = 0; k < 6; k++)
                    if (bool(x & (1 << (5 - k))))
                        bs[i][6 * j + k] = bs[6 * j + k][i] = true;
            }
        }
        // rep (i, n) cout << bs[i] << endl;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if ((bs[i] & bs[j]).count() == 0) {
                    printf("Case #%d: Members %d and %d have no common friends.\n",
                            kase, i + 1, j + 1);
                    goto cont;
                }
            }
        }
        printf("Case #%d: Social graph is too dense.\n", kase);
        cont:;
    }
    return 0;
}
