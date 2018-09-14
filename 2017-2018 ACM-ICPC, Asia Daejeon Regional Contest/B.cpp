#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

typedef unsigned status;

int g[4][4];

int x, a, b;

int judge() {
  rep (i, 4) { 
    if (g[i][0] && g[i][0] == g[i][1] && g[i][1] == g[i][2]) return g[i][0];
    if (g[i][1] && g[i][1] == g[i][2] && g[i][2] == g[i][3]) return g[i][1];
  }
  rep (j, 4) {
    if (g[0][j] && g[0][j] == g[1][j] && g[1][j] == g[2][j]) return g[0][j];
    if (g[1][j] && g[1][j] == g[2][j] && g[2][j] == g[3][j]) return g[1][j];
  }
  if (g[0][0] && g[0][0] == g[1][1] && g[1][1] == g[2][2]) return g[0][0];
  if (g[1][1] && g[1][1] == g[2][2] && g[2][2] == g[3][3]) return g[1][1];
  if (g[3][0] && g[3][0] == g[2][1] && g[2][1] == g[1][2]) return g[3][0];
  if (g[2][1] && g[2][1] == g[1][2] && g[1][2] == g[0][3]) return g[2][1];

  if (g[2][0] && g[2][0] == g[1][1] && g[1][1] == g[0][2]) return g[2][0];
  if (g[3][1] && g[3][1] == g[2][2] && g[2][2] == g[1][3]) return g[3][1];
  if (g[1][0] && g[1][0] == g[2][1] && g[2][1] == g[3][2]) return g[3][2];
  if (g[0][1] && g[1][2] == g[0][1] && g[1][2] == g[2][3]) return g[2][3];
  return 0;
}

status pack() {
  status res = 0;
  rep (i, 4) rep (j, 4) res = res << 2 | g[i][j];
  return res;
}

/*
void unpack(status stat) {
//  int wcnt = 0;
  for (int i=3; i>=0; i--) {
    for (int j=3; j>=0; j--) {
      g[i][j] = stat & 3;
      stat >>= 2;
//      if (g[i][j] == 1) wcnt ++;
//      if (g[i][j] == 2) wcnt --;
    }
  }
//  if (wcnt) return 2; else return 1;
}
*/

set<status> s, ok;

bool verify() {
  for (int i=0; i<3; i++) {
    for (int j=0; j<4; j++) {
      if (g[i][j] == 0 && g[i+1][j] != 0) return false;
    }
  }
  return true;
}

void pok() {
  int cnt = 0;
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      if (g[i][j] == 1) cnt++;
      if (g[i][j] == 2) cnt--;
    }
  }
  assert(cnt == 0 && verify());
  ok.insert(pack());
}

void dfs(int next) {
  // assert(verify());
  status stat = pack();
  if (s.find(stat) != s.end()) return;
  s.insert(stat);
  if (judge()) return;
  rep (j, 4) {
    for (int i=0; i<=3; i++) {
      if (g[i][j] == 0) {
        g[i][j] = next;
        if (i == a && j == b && next == 2 && judge() == 2) {
          pok();
          // ok.insert(pack());
        }
        dfs(3 - next);
        g[i][j] = 0;
        goto nxt;
      } 
    }
nxt:;
  }
}

int main() {
  cin >> x >> a >> b;
  x--; a--; b--;
  g[0][x] = 1;
  dfs(2);
  cout << ok.size()  << endl;
  return 0;
}
