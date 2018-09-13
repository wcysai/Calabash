#pragma GCC optimize(3)
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

vector<int> deck;

int cur;

inline int next_card(int x) {
  if (x == 2) return -1;
  if (x != 13) return x + 1;
  return 1;
}

struct player {
  int pid;
  int sz;
  int cnt[16];

  void init(int i) {
    pid = i;
    sz = 0;
    memset(cnt, 0, sizeof cnt);
  }

  int penalty() {
    int tot = 0;
    Rep (i, 13) tot += i * cnt[i];
    return tot;
  }

  bool out() {
    int ncrd;
    if (cur > 0) {
      ncrd = next_card(cur);
      if (ncrd == -1) {
        _debug("player %d passed", pid);
        return false;
      }
      if (cnt[ncrd] == 0) ncrd = 2;
      if (cnt[ncrd] == 0) {
        _debug("player %d passed", pid);
        return false;
      }
    } else {
      ncrd = 3;
      while (ncrd > 0) {
        if (cnt[ncrd]) break;
        ncrd = next_card(ncrd);
      }
    }
    cnt[ncrd]--;
    cur = ncrd;
    _debug("player %d out %d", pid, ncrd);
    sz--;
    if (sz == 0) throw 0;
    return true;
  }

  void draw() {
    if (deck.size() == 0) return;
    int n = deck.back(); deck.pop_back();
    _debug("player %d draw %d", pid, n);
    cnt[n]++;
    sz++;
  }
} players[205];

void run_game(int n, int m) {
  rep (i, n) players[i].init(i);
  deck.resize(m);
  for (int i = m - 1; i >= 0; i--)
    scanf("%d", &deck[i]);
  
  rep (i, n) {
    rep (c, 5) players[i].draw();
//    assert(players[i].sz);
  }
  
  cur = -1;
  int pid = 0, pass = 0;
   
  while (true) {
    if (pass == n-1) {
      for (int id = pid; id < pid + n; id++) 
        players[id % n].draw();
      cur = -1;
    }
    if (players[pid].out()) pass = 0; else pass++;
    pid = (pid + 1) % n;
  }
}

int main() {
  int T; scanf("%d", &T);
  Rep (t, T) {
    int n, m; scanf("%d%d", &n, &m);
      _debug("%d %d", n, m);
    try {
      run_game(n, m);
    } catch(...) {
      printf("Case #%d:\n", t);
      rep (i, n) {
        int cnt = players[i].penalty();
        if (cnt == 0) puts("Winner");
        else printf("%d\n", cnt);
      }
    }
  }
  return 0;
}
