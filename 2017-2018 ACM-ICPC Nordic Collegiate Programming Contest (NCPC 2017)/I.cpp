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

#define prev afeuoaho

int n;
map<string, int> fid;
string fname[505];

vector<int> adj[505];
int prev[505];
int vis[505];

vector<vector<int>> ans;

void bfs(int s) {
  queue<int> q;
  
  q.push(s);

  memset(prev, 0, sizeof prev);
  memset(vis, 0, sizeof vis);
  
  while (q.size()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (!vis[v]) {
          vis[v] = true;
          prev[v] = u;
          q.push(v);
          if (v == s) {
            vector<int> cyc;
            int cur = prev[s];
            while (cur != s) {
              cyc.push_back(cur);
              cur = prev[cur];
            }
            cyc.push_back(s);
            reverse(range(cyc));
            ans.push_back(cyc);
            return;
          }
      }
    }
  }
}

int main() {
  cin >> n;
  rep (i, n) {
    cin >> fname[i];
    fid[fname[i]] = i;
  }
  rep (i, n) {
    string name; int ln, u;
    cin >> name >> ln;
    u = fid[name];
    static char code[1024 * 1024];
    gets(code);
    while (ln--) {
      gets(code);
      char *tok = strtok(code, " ,");
      tok = strtok(NULL, " ,");
      while (tok) {
        adj[u].push_back(fid[tok]);
        tok = strtok(NULL, " ,");
      }
    }
  }
/*  
  rep (i, n) {
    printf("[%d]: ", i);
    for (int j : adj[i]) cout << j << ' '; cout << endl;
  }
  */
  rep (i, n) bfs(i);
  if (ans.size() == 0) cout << "SHIP IT" << endl;
  else {
    auto it = min_element(range(ans), 
        [] (vector<int>& lhs, vector<int>& rhs) {
          return lhs.size() < rhs.size();
        });
    for (int u : *it) {
      cout << fname[u] << ' ';
    }
  }
  return 0;
}
