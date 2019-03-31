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

const char digit[10][7][5] = {
{
    ".XX.",
    "X..X",
    "X..X",
    "....",
    "X..X",
    "X..X",
    ".XX.",
}, // 0
{
    "....",
    "...X",
    "...X",
    "....",
    "...X",
    "...X",
    "....",
}, // 1
{
    ".XX.",
    "...X",
    "...X",
    ".XX.",
    "X...",
    "X...",
    ".XX.",
}, // 2
{
    ".XX.",
    "...X",
    "...X",
    ".XX.",
    "...X",
    "...X",
    ".XX.",
}, // 3
{
    "....",
    "X..X",
    "X..X",
    ".XX.",
    "...X",
    "...X",
    "....",
}, // 4
{
    ".XX.",
    "X...",
    "X...",
    ".XX.",
    "...X",
    "...X",
    ".XX.",
}, // 5
{
    ".XX.",
    "X...",
    "X...",
    ".XX.",
    "X..X",
    "X..X",
    ".XX.",
}, // 6
{
    ".XX.",
    "...X",
    "...X",
    "....",
    "...X",
    "...X",
    "....",
}, // 7
{
    ".XX.",
    "X..X",
    "X..X",
    ".XX.",
    "X..X",
    "X..X",
    ".XX.",
}, // 8
{
    ".XX.",
    "X..X",
    "X..X",
    ".XX.",
    "...X",
    "...X",
    ".XX.",
}  // 9
};

const char mask[7][22] = {
    ".XX...XX.....XX...XX.",
    "X..X.X..X...X..X.X..X",
    "X..X.X..X.X.X..X.X..X",
    ".XX...XX.....XX...XX.",
    "X..X.X..X.X.X..X.X..X",
    "X..X.X..X...X..X.X..X",
    ".XX...XX.....XX...XX.",
};

char canvas[7][22];

void paintchar(int x, int y, int ch) {
    if (ch == -1) {
        rep (i, 7) rep (j, 4) canvas[x+i][y+j] = '.';
    } else {
        rep (i, 7) rep (j, 4) canvas[x+i][y+j] = digit[ch][i][j];
    }
}

void paint(int hh, int mm) {
    paintchar(0, 0, (hh < 10) ? -1 : (hh / 10));
    paintchar(0, 5, hh % 10);
    paintchar(0, 12, mm / 10);
    paintchar(0, 17, mm % 10);
//    rep (i, 7) puts(canvas[i]);
}

int n;
char smp[128][7][22];

bool a0[7][22], a1[7][22];
bool lw[7][22];

enum STATUS {
    UNKNOWN = 0,
    ON = 1,
    OFF = 2,
    WORK = 3,
    CONFUSION = 4,
};

int merge(int x, int y) {
    if (x == 0 or y == 0) return x + y;
    if (x != y) return 4;
    return x;
}

int status[7][22];

bool test(int hh, int mm) {
    rep (i, 7) rep (j, 21) lw[i][j] = true;
    rep (i, n) {
        paint(hh, mm);
        rep (x, 7) rep (y, 21) if (mask[x][y] == 'X') 
            lw[x][y] &= (canvas[x][y] == smp[i][x][y]);
        mm++;
        if (mm == 60) {
            mm = 0;
            hh++; 
        }
        if (hh == 24) hh = 0;
    }
    rep (x, 7) rep (y, 21) if (mask[x][y] == 'X') if (!lw[x][y] and !a0[x][y] and !a1[x][y]) 
        return false;
    rep (x, 7) rep (y, 21) if (mask[x][y] == 'X') {
        status[x][y] = merge(status[x][y], 
            merge(merge(a0[x][y] ? OFF : 0, a1[x][y] ? ON : 0), lw[x][y] ? WORK : 0));
    }
    return true;
}

int main() {
    memcpy(canvas, mask, sizeof mask);

    scanf("%d", &n);
    rep (i, n) rep (j, 7) scanf("%s", smp[i][j]);
    rep (i, 7) rep (j, 21) a0[i][j] = a1[i][j] = true;
    rep (i, n) rep (x, 7) rep (y, 21) {
        a0[x][y] &= (smp[i][x][y] == '.');
        a1[x][y] &= (smp[i][x][y] == 'X');
    }

    bool flag = false;
    rep (i, 24) rep (j, 60) {
        if (test(i, j)) {
            flag = true;
        }
    }
    if (!flag) {
        puts("impossible");
    } else {
        rep (x, 7) {
            rep (y, 21) {
                if (mask[x][y] == '.') {
                    putchar('.'); 
                } else {
                    if (status[x][y] == CONFUSION) {
                        putchar('?');
                    } else if (status[x][y] == WORK) {
                        putchar('W');
                    } else if (status[x][y] == OFF) {
                        putchar('0');
                    } else if (status[x][y] == ON) {
                        putchar('1');
                    } else {
                        putchar('?');
                    }
                }
            }
            putchar('\n');
        }
    }
    return 0;
}
