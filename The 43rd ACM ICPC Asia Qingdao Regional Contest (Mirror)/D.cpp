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

int n, m, len;
char str[2000005];
int a[1000005], b[1000005];

char mult_table[10][10][8];
char mult_table2[10][2000005];

void init() {
    rep (i, 10) rep (j, 10) sprintf(mult_table[i][j], "%d", i * j);
}

namespace scanner {
    char *ptr;

    void rewind() {
        ptr = str;
    }

    bool eof() {
        return *ptr == 0;
    }

    inline bool try_match(const char* str) {
        char *nptr = ptr;
        while (*str) {
            if (*nptr != *str) return false;
            nptr++;
            str++;
        }
        ptr = nptr;
        return true;
    }

    inline bool try_match(int i, int j) {
        return try_match(mult_table[i][j]);
    }
}

bool special_judge() {
    if (n == 1 and m == 1 and strcmp(str, "0") == 0) {
        puts("0 0");
        return true;
    }
    if (n == 1 and len == m and count(str, str + len, '0') == len) {
        printf("0 ");
        rep (i, m) putchar(i ? '0' : '1');
        putchar('\n');
        return true;
    }
    if (m == 1 and len == n and count(str, str + len, '0') == len) {
        rep (i, n) putchar(i ? '0' : '1');
        printf(" 0\n");
        return true;
    }
    return false;
}

bool restore_b(int dig) {
    using namespace scanner;
    rewind();
    rep (i, m) {
        rep (d, 10) {
            if (try_match(dig, d)) {
                b[i] = d;
                goto cont;
            }
        }
        return false;
        cont:;
    }
    // printf("restore b success with a[0]=%d\n", dig);
    // rep (i, m) putchar(b[i] + '0'); putchar('\n');
    return true;
}

bool restore_a() {
    rep (d, 10) {
        int ptr = 0;
        rep (i, m) {
            sprintf(mult_table2[d] + ptr, "%s", mult_table[d][b[i]]);
            ptr += strlen(mult_table[d][b[i]]);
        }
    }
    using namespace scanner;
    rewind();
    rep (i, n) {
        rep (d, 10) {
            if (try_match(mult_table2[d])) {
                a[i] = d;
                goto cont;
            }
        }
        return false;
        cont:;
    }
    // _debug("restore a success");
    return eof();
}

int main() {
    init();
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%s", &n, &m, str);
        len = strlen(str);
        if (special_judge()) continue;
        try {
            for (int dig = 1; dig <= 9; dig++) {
                if (restore_b(dig) and restore_a()) goto cont;
            }
            throw 0;
            cont:
            rep (i, n) putchar('0' + a[i]); putchar(' ');
            rep (i, m) putchar('0' + b[i]); putchar('\n');
        } catch (...) {
            puts("Impossible");
        }
    }
    return 0;
}