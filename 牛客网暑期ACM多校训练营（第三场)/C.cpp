#include <bits/stdc++.h>
#include <ext/rope>
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
 
const int BLOCK = 500;
int n, m;
list<vector<int>> block;
typedef list<vector<int>>::iterator vit;
 
void Init(int n) {
  int blk = n / BLOCK + 2;
  block.clear();
  rep (i, blk) {
    int sz = (n >= BLOCK ? BLOCK : n);
    block.push_back(vector<int>(sz));
    n -= sz;
  }
}
 
template <typename T>
void Iterate(T func) {
  int cnt = 0;
  for (auto& vec : block) {
    for (int& v : vec) {
      func(cnt, v);
      cnt++;
    }
  }
}
 
void parray() {
  for (auto& vec : block) {
    cout << &vec << ": ";
    for (int& v : vec) {
      cout << v << ' ';
    }
    cout << endl;
  }
}
 
void Merge(vit it) {
//  parray();
//  _debug("%p", &(*it));
  while (next(it) != block.end() && it->size() + next(it)->size() <= BLOCK) {
    it->insert(it->end(), next(it)->begin(), next(it)->end());
    block.erase(next(it));
  }
}
 
void Maintain() {
  vit it = block.begin();
  while (it != block.end() && next(it) != block.end()) {
//    _debug("%p",&(*it));
    Merge(it);
    ++it;
  }
}
 
void Split(vit it, int pos) {
  if (pos == 0) return ;
  if (pos == it->size()) return;
  vector<int> vec(it->begin() + pos, it->end());
  it->resize(pos);
  ++it;
  block.insert(it, move(vec));
}
 
void Move_front(int l, int r) {
    _debug("l=%d, r=%d", l, r);
  if (l == 0) return;
  int cur = 0, inc = 0;
  vit b, e;
  vit it = block.begin();
  while (it != block.end() && cur + it->size() <= l) {
    cur += it->size();
    ++it; inc++;
  }
  if (cur != l) {
    Split(it, l - cur);
    ++it; inc++;
  }
  b = it;
  cur = l;
   
  while (it != block.end() && cur + it->size() <= r) {
    cur += it->size();
    ++it;
  }
  if (cur != r) {
    Split(it, r - cur);
    ++it;
  }
  e = it;
  cur = l;
   
  block.splice(block.begin(), block, b, e);
  _debug("!");
  Maintain();
}
 
int main() {
  scanf("%d%d", &n, &m);
  Init(n);
  Iterate([] (int pos, int& v) { v = pos + 1; });
  rep (i, m) {
    _debug("%d", i);
    int u, v; scanf("%d%d", &u, &v);
    u--;
    Move_front(u, u+v);
  }
  _debug("!");
  Iterate([] (int pos, int& v) { printf("%d ", v); });
  puts("");
  return 0;
}
