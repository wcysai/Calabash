#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debuf(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

inline int xlat(char ch) {
    if (ch == 'W') return 1;
    else if (ch == 'B') return -1;
    return 0;
}

int g[8][8];

bool put(int i, int j, int p) {
    g[i][j] = p;
    
    bool flag = false;
    for (int k = j - 1; k >= 0; k--) {
        if (g[i][k] == 0) break;
        if (g[i][k] == p) {
            for (int kk = k; kk < j; kk++) 
                g[i][kk] = p;
            flag |= (k < j - 1);
            break;
        }
    }

    for (int k = j + 1; k < 8; k++) {
        if (g[i][k] == 0) break;
        if (g[i][k] == p) {
            for (int kk = j + 1; kk < k; kk++) 
                g[i][kk] = p;
            flag |= (k > j + 1);
            break;
        }
    }

    for (int k = i - 1; k >= 0; k--) {
        if (g[k][j] == 0) break;
        if (g[k][j] == p) {
            for (int kk = k; kk < i; kk++)
                g[kk][j] = p;
            flag |= (k < i - 1);
            break;
        }
    }
    
    for (int k = i + 1; k < 8; k++) {
        if (g[k][j] == 0) break;
        if (g[k][j] == p) {
            for (int kk = i + 1; kk < k; kk++)
                g[kk][j] = p;
            flag |= (k > i + 1);
            break;
        }
    }

    {
        int ii = i, jj = j;
        while (ii >= 0 and jj >= 0) {
            if (g[ii][jj] == 0) break;
            if (ii != i and g[ii][jj] == p) {
                flag |= (ii < i - 1);
                while (ii != i and jj != j) 
                    g[ii++][jj++] = p;   
                break;
            }
            ii--; jj--;
        }
    }
    
    {
        int ii = i, jj = j;
        while (ii >= 0 and jj < 8) {
            if (g[ii][jj] == 0) break;
            if (ii != i and g[ii][jj] == p) {
                flag |= (ii < i - 1);
                while (ii != i and jj != j) 
                    g[ii++][jj--] = p;   
                break;
            }
            ii--; jj++;
        }
    }
    
    {
        int ii = i, jj = j;
        while (ii < 8 and jj < 8) {
            if (g[ii][jj] == 0) break;
            if (ii != i and g[ii][jj] == p) {
                flag |= (ii > i + 1);
                while (ii != i and jj != j) 
                    g[ii--][jj--] = p;   
                break;
            }
            ii++; jj++;
        }
    }
    
    {
        int ii = i, jj = j;
        while (ii < 8 and jj >= 0) {
            if (g[ii][jj] == 0) break;
            if (ii != i and g[ii][jj] == p) {
                flag |= (ii > i + 1);
                while (ii != i and jj != j) 
                    g[ii--][jj++] = p;   
                break;
            }
            ii++; jj--;
        }
    }

    return flag;
}

int decide() {
    int ans = 0;
    rep (i, 8) rep (j, 8) ans += g[i][j];
    if (ans > 0) return 1;
    if (ans < 0) return -1;
    return 0;
}

int num;
vector<pair<int, int>> pos;
bool used[16];
bool passed = false;

int dfs(int p) {
    int save[8][8];
    int ans = -p;
//    if (accumulate(used, used + num, 0) == num) return decide();

    memcpy(save, g, sizeof g);
    bool flag = false;
    for (int i = 0; i < num; i++) {
        if (ans == p) break;
        if (used[i]) continue;
        int x, y; tie(x, y) = pos[i];
        memcpy(g, save, sizeof g);
        if (!put(x, y, p)) continue;
        flag = true;
        used[i] = true;
        int cur = dfs(-p);
        used[i] = false;
        if (p < 0) ans = min(ans, cur);
        else ans = max(ans, cur);
    }
    memcpy(g, save, sizeof g);
    if (!flag) {
        if (passed) ans = decide();
        else {
            passed = true;
            ans = dfs(-p);
            passed = false;
        }
    }
    memcpy(g, save, sizeof g);
    return ans;
}

int main() {
    char buf[12][12], play[2];
    rep (i, 8) scanf("%s", buf[i]);
    scanf("%s", play);
    rep (i, 8) rep (j, 8) g[i][j] = xlat(buf[i][j]);
    
    rep (i, 8) rep (j, 8) if (g[i][j] == 0) {
        num++;
        pos.emplace_back(i, j);
    }

    int ans = dfs(xlat(play[0]));
    if (ans == 1) puts("WHITE");
    else if (ans == -1) puts("BLACK");
    else puts("DRAW");
    return 0;
}
