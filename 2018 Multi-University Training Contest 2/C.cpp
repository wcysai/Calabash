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
#define range(x) begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

const int MAXN = 100005;
const int MAXM = 100005;

int n, m;
int father[MAXN];
map<int, int> adj[MAXN];
pair<int, int> edges[MAXM];
bool vvis[MAXN];
bool vis[MAXM];

int getFather(int x) {
  return x == father[x] ? x : father[x] = getFather(father[x]);
}

void add(int u, int v, int z) {
  adj[u][z] = v;
  adj[v][-z] = u;
}

vector<vector<int>> paths;
vector<int> cycles[MAXN];
vector<int> path;

inline int ebeg(int w) { 
  if (w > 0) return edges[w].first;
  else return edges[-w].second;
}

inline void add_cycle(int v) {
  int u = getFather(v);
  if (cycles[u].size() == 0) return;
  int i = 0;
  while (ebeg(cycles[u][i]) != v) i++;
  rotate(cycles[u].begin() , cycles[u].begin() + i, cycles[u].end());
  for (int i : cycles[u]) path.push_back(i);
  cycles[u].clear();
}

void gen_ans() {
  /*
  for (auto& pa : paths) {
    for (int w : pa) {
      cout << w << ' ';
    }
    cout << endl;
  }
  _debug("-----");
  */
  for (auto& pa : paths) {
    path.clear();
    for (int w : pa) {
      int u, v; tie(u, v) = edges[abs(w)];
      if (w < 0) swap(u, v);
      add_cycle(u);
      path.push_back(w);
      add_cycle(v);
    }
    pa = path;
  }
  Rep (i, n) {
    if (cycles[i].size()) {
      paths.push_back(cycles[i]);
      cycles[i].clear();
    }
  }
  printf("%d\n", (int)paths.size());
  for (auto& pa : paths) {
    printf("%d", (int)pa.size());
    for (int v : pa) printf(" %d", v);
    puts("");
  } 
}

#define eid first
#define vtx second

void dfs(int u) {
  for (auto& p : adj[u]) {
    if (!vis[abs(p.eid)]) {
      vis[abs(p.eid)] = true;
      dfs(p.vtx);
      path.push_back(p.eid);
    }
  }
}

void find_odd(int u) {
  if (adj[u].size() % 2 == 0) return;
  
  auto p = *(adj[u].begin());
  adj[u].erase(p.first);
  path.push_back(p.first);
  adj[p.second].erase(-p.first);

  find_odd(p.second);
}

void solve() {
  Rep (i, n) father[i] = i;
  
  Rep (i, n) {
    if (adj[i].size() & 1) {
      path.clear();
      find_odd(i);
      paths.push_back(path);
    }
  }

  Rep (i, n) {
    for (auto& p : adj[i]) {
      father[getFather(i)] = getFather(p.second);
    }
  }
  
  memset(vis, false, sizeof(vis));
  
  Rep (i, n) {
    if (adj[i].size()) {
      if (adj[i].size() & 1) continue;
      if (getFather(i) == i) {
        path.clear();
        dfs(i);
        reverse(range(path));
        cycles[i] = path;
      }
    }
  }
  
  gen_ans(); 
}


int main() {
  while (scanf("%d%d", &n, &m) != EOF) {
    Rep (i, n) adj[i].clear();
    paths.clear();
    Rep (i, m) {
      int u, v; scanf("%d%d", &u, &v);
      edges[i] = {u, v};
      add(u, v, i);
    }
    solve();
  }
  return 0;
}
