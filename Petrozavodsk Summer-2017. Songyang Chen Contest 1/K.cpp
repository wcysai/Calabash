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
}, // 9

};

char g[7][22];

int check(int x, int y, int d) {
    int cnt = 0;
    rep (i, 7) rep (j, 4) if (g[x+i][y+j] != digit[d][i][j]) cnt++;
    return cnt;
}

int recog(int x, int y) {
    int dif[10] = {0};
    rep (i, 10) dif[i] = check(x, y, i);
    return min_element(dif, dif + 10) - dif;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        rep (i, 7) scanf("%s", g[i]);
        int val[4] = {recog(0, 0), recog(0, 5), recog(0, 12), recog(0, 17)};
        printf("%d%d:%d%d\n", val[0], val[1], val[2], val[3]);
    }
    return 0;
}
