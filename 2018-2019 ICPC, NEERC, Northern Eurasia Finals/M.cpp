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

struct UFS {
    int fa[10];

    UFS() { Rep (i, 9) fa[i] = i; }
    
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    
    int operator[] (int x) {
        return find(x);
    }

    void unite(int u, int v) {
        u = find(u); v = find(v);
        fa[u] = v;
    }
} ufs; 

int n;

inline int pid(int x, int y) {
    x--; y--;
    return x * n + y;
}


int toth = 0;
char graph[500][5][500];

#define layer graph[toth]

void create_wall() {
    toth++;
    Rep (i, n) Rep (j, n) {
        int id = pid(i, j);
        layer[0][id<<1] = '.';
        layer[1][id<<1] = '#';
        layer[2][id<<1] = '.';
        layer[0][id<<1|1] = '#';
        layer[1][id<<1|1] = '#';
        layer[2][id<<1|1] = '.';
    }
}

void create_floor() {
    toth++;
    Rep (i, n) Rep (j, n) {
        int id = pid(i, j);
        layer[0][id<<1] = '.';
        layer[1][id<<1] = '#';
        layer[2][id<<1] = '#';
        layer[0][id<<1|1] = '#';
        layer[1][id<<1|1] = '#';
        layer[2][id<<1|1] = '#';
    }
}

void create_node(int i, vector<int> in, vector<int> out, vector<int> nums) {
    create_wall();
    for (int x : in) {
        int id = pid(x, i);
        layer[1][id<<1] = '.';
    }
    create_floor();
    for (int x : in) {
        int id = pid(x, i);
        layer[0][id<<1] = '#';
    }
    layer[2][pid(n, n)<<1|1] = '.';
    create_wall();
    for (int x : out) {
        int id = pid(i, x);  
        layer[1][id<<1] = '.';
    }
    for (int i = 0; i < nums.size(); i++) {
        layer[2][i] = nums[i] + '0';
    }
    create_floor();
}

vector<int> nums[10];
bool adj[10][10];
int deg[10];
vector<int> topo;

void toposort() {
    vector<int> s;
    Rep (i, n) if (deg[i] == 0) s.push_back(i), topo.push_back(i);
    while (s.size()) {
        int i = s.back(); s.pop_back();
        Rep (j, n) if (adj[i][j]) {
            deg[j]--;
            if (deg[j] == 0) {
                s.push_back(j);
                topo.push_back(j);   
            }
        }
    }    
    _debug("%d", topo.size());
}

int main() {
    scanf("%d", &n);
    Rep (i, n) Rep (j, n) {
        int x; scanf("%d", &x);
        adj[i][j] = x;
    }
    Rep (i, n) adj[i][i] = 1;
    Rep (k, n) Rep (i, n) Rep (j, n) adj[i][j] |= adj[i][k] and adj[k][j];
    Rep (i, n) Rep (j, n) if (adj[i][j] and adj[j][i]) ufs.unite(i, j);
    Rep (i, n) {
        _debug("%d %d", i, ufs[i]);
        nums[ufs[i]].push_back(i);
    }
    
    bool buf[10][10] = {0};
    Rep (i, n) Rep (j, n) if (adj[i][j] and ufs[i] != ufs[j]) {
        buf[ufs[i]][ufs[j]] = true;
    }
    memset(adj, 0, sizeof adj);
    memcpy(adj, buf, 100);
    Rep (i, n) Rep (j, n) if (adj[i][j]) deg[j]++;
    toposort();
    for (int x : topo) {
        vector<int> in, out;
        if (nums[x].size() == 0) continue;
        Rep (i, n) {
            if (adj[i][x]) in.push_back(i);
            if (adj[x][i]) out.push_back(i);
        }
        //printf("-- %d\n", x); 
        //printf("IN : "); for (int x : in) printf("%d ", x); puts("");
        //printf("OUT: "); for (int x : out) printf("%d ", x); puts("");
        create_node(x, in, out, nums[x]);
    } 
    create_floor();
    int w = 3, h = n * n * 2, z = toth;
    printf("%d %d %d\n", h, w, z);
    for (int zz = 1; zz <= z; zz++) {
        rep (i, w) puts(graph[zz][i]);
        toth--;
        if (toth) puts("");
    }
    return 0;
}
