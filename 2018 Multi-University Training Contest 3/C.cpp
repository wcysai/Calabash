#pragma GCC optimize(3)
// #pragma GCC optimize("Ofast")
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


int n, m;
int adj[16][16];

typedef pair<short, short> edge;
typedef array<int*, 6> match;
edge e[12];
bool used[16];

vector<match> matches[10][10];

void enumerate_matching(int sz, int al, int cur) {
  if (sz == al) {
    match m = {0, 0, 0, 0, 0};
    rep (i, sz) m[i] = &(adj[e[i].first][e[i].second]);
    rep (i, sz) matches[e[i].first][e[i].second].push_back(m);
    
    return;
  }
  for (; cur < n; cur++) {
    if (used[cur]) continue;
    used[cur] = 1;
    for (int i = cur + 1; i < n; i++) {
      if (!used[i]) {
        used[i] = 1;
        e[al] = {cur, i};
        enumerate_matching(sz, al+1, cur+1);
        used[i] = 0;
      }
    }
    used[cur] = 0;
  }
}

const LL mod = 1000000007;
LL cur[10];

int main() {
  int T; scanf("%d", &T);
//  enumerate_matching(1, 0, 0);
  
  while (T--) {
    rep (i, 10) rep (j, 10) matches[i][j].clear();
    scanf("%d%d", &n, &m);
  Rep (i, n / 2) enumerate_matching(i, 0, 0);
    memset(cur, 0, sizeof cur);
    memset(adj, 0, sizeof adj);
    while (m--) {
      char ch[12]; int u, v;
      scanf("%s%d%d", ch, &u, &v); u--; v--;
      int* thispos = &(adj[u][v]);
      for (auto& m : matches[u][v]) {
        LL tot = 1;
        int num = 0;
        while (m[num]) {
          auto ed = m[num];
          if (ed != thispos) tot *= *ed;
          num++;
        }
        tot %= mod;
        auto& val = cur[num];
        if (ch[0] == '+') val += tot;
        else val += (mod  - tot);
        if (val >= mod) val -= mod;
      }
      Rep (i, n/2) printf("%d%c", int(cur[i]), (i==n/2)?'\n':' ');
      if (ch[0] == '+') adj[u][v]++; else adj[u][v]--;
    }
  }
  return 0;
}
