#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define Rep(i, n) for (int i = 1; i <=n; i++)
#define range(x)  begin(x), end(x)
int n, m, d, dc;
int deg[320];
int adj[320][320];

vector<int> rem;

void remove(int x, int y) {
    rem.push_back(adj[x][y]);
    adj[x][y] = adj[y][x] = 0;
    deg[x]--; deg[y]--;
}

int main() {
    freopen("funny.in", "r", stdin);
    freopen("funny.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &d);
    Rep (i, m) {
        int u, v; scanf("%d%d", &u, &v);
        u-- ; v--;
        adj[u][v] = adj[v][u] = i;
        deg[u]++; deg[v]++;
    }
    dc = *min_element(deg, deg + n);
    if (dc < d) {
        cout << "NO" << endl;
        return 0;
    }
    while (dc > d) {
        rep (i, n) {
            if (deg[i] != dc) continue;
            rep (j, n) {
                if (adj[i][j] and deg[j] >= d - 1) {
                    remove(i, j);
                    break;
                }
            }
            
        }
        dc--;
    }
    sort(range(rem));
    cout << "YES" << endl;
    cout << rem.size() << endl;
    for (int x : rem) cout << x << ' ';
    return 0;
}
