#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int inf = 0x3f3f;
const int INF = inf;

#define PB(x) push_back(x)
#define rep(i,l,r) for (int i = l,_ = r;i< _;i++)
#define REP(i,l,r) for (ll i=l,_=r;i<=_;i++)
#define leave(x) do {cout<<#x<<endl;fflush(stdout);return 0;}while (0);
#define untie do{ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);}while (0)

/************* header ******************/


const int N = 55;
const int MAX_COM = 100;
const int DX[] = {-1, 0, 1, 0};
const int DY[] = {0, -1, 0, 1};
int n, m;
char board[N][N];
char buf[N * N];
int sx, sy,fx, fy,ql, qr;
short
inner_dist[3][N * N][N * N],
inner_par[3][N * N][N * N],
go[N * N][N * N],
go_mid[N * N][N * N],
go_mid_type[N * N][N * N],
dis[N * N],
pre[N * N],
q[N * N];
inline int encode(int x, int y) {
    return x * m + y;
}
inline void decode(int v, int & x, int & y) {
    x = v / m;
    y = v % m;
}
inline void mirror(int midx, int midy, int type, int x, int y, int & nx, int & ny) {
    nx = 2 * midx - x;
    ny = 2 * midy - y;
    if (type == 1)nx++;
    if (type == 2)ny++;
}
inline bool good_cell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] != '#';
}

void inner_bfs(int startx, int starty, int dx, int dy) {
    int type = 2 * dy + dx;
    int start = encode(startx, starty);
    short * dist = inner_dist[type][start];
    short * par = inner_par[type][start];

    fill(dist, dist + n * m, INF);
    fill(par, par + n * m, -1);
    dist[start] = dx + dy;
    ql = qr = 0;
    q[qr++] = start;
    if (type > 0) {
        int neighbour = encode(startx + dx, starty + dy);
        dist[neighbour] = 1;
        par[neighbour] = start;
        par[start] = neighbour;
        q[qr++] = neighbour;
    }

    while (ql < qr) {
        int v = q[ql++];
        int x, y;
        decode(v, x, y);
        rep(d,0,4){
            int nx = x + DX[d];
            int ny = y + DY[d];
            if (!good_cell(nx, ny))continue;
            int symx, symy;
            mirror(startx, starty, type, nx, ny, symx, symy);
            if (!good_cell(symx, symy))continue;
            int to = encode(nx, ny);
            if (dist[to] == INF) {
                dist[to] = dist[v] + 2;
                par[to] = v;
                q[qr++] = to;
            }
        }
    }

    for (int v = 0; v < n * m; v++) {
        if (dist[v] > MAX_COM)continue;
        int x, y;
        decode(v, x, y);
        int symx, symy;
        mirror(startx, starty, type, x, y, symx, symy);
        int to = encode(symx, symy);
        if (go[v][to] > dist[v]) {
            go[v][to] = go[to][v] = dist[v];
            go_mid[v][to] = go_mid[to][v] = start;
            go_mid_type[v][to] = go_mid_type[to][v] = type;
        }
    }
}
void bfs() {
    int start = encode(sx, sy);
    fill(dis, dis + n * m, INF);
    fill(pre, pre + n * m, -1);
    dis[start] = 0;
    ql = qr = 0;
    q[qr++] = start;
    while (ql < qr) {
        int head = q[ql++];
        for (int to = 0; to < n * m; to++) {
            if (go[head][to] == INF)continue;
            if (dis[to] == INF) {
                dis[to] = dis[head] + 1;
                pre[to] = head;
                q[qr++] = to;
            }
        }
    }
}
char get_dir(int from, int to) {
    int x1, y1;
    decode(from, x1, y1);
    int x2, y2;
    decode(to, x2, y2);
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx == 1)return 'U';
    if (dx == -1)return 'D';
    if (dy == 1)return 'L';
    return 'R';
}
int res_total;
vector<string> res;
void print_command(int from, int to) {
    int mid = go_mid[from][to];
    int type = go_mid_type[from][to];
    short * dist = inner_dist[type][mid];
    short * par = inner_par[type][mid];
    int ptr = 0;
    int v = to;
    while (true) {
        int p = par[v];
        if (p == -1)break;
        buf[ptr++] = get_dir(p, v);
        if (type > 0 && dist[v] == 1)break;
        v = p;
    }
    if (type > 0) {
        for (int i = ptr; i < 2 * ptr - 1; i++)
            buf[i] = buf[i - ptr];
        reverse(buf + ptr, buf + 2 * ptr - 1);
        buf[2 * ptr - 1] = 0;
    } else {
        for (int i = ptr; i < 2 * ptr; i++)
            buf[i] = buf[i - ptr];
        reverse(buf + ptr, buf + 2 * ptr);
        buf[2 * ptr] = 0;
    }
    res_total++;
    res.push_back(buf);
}
signed main() {
    scanf("%d%d", &n, &m);
    rep(i,0,n)scanf("%s", board[i]);
    rep(i,0,n)rep(j,0,m) {
        if (board[i][j] == 'F') {
            sx = i, sy = j;
            board[i][j] = '.';
        }
        if (board[i][j] == 'S') {
            fx = i, fy = j;
            board[i][j] = '.';
        }
    }
    int NM = n*m;
    rep(i,0,NM)rep(j,0,NM)go[i][j] = INF;
    rep(i,0,n)rep(j,0,m) {
        if (!good_cell(i, j))continue;
        inner_bfs(i, j, 0, 0);
        if (good_cell(i+1,j))inner_bfs(i, j, 1, 0);
        if (good_cell(i,j+1))inner_bfs(i, j, 0, 1);
    }

    bfs();
    int finish = encode(fx, fy);
    if (dis[finish] == INF)return puts("-1"),0;
    int v = finish;
    while (true) {
        int p = pre[v];
        if (p == -1)break;
        print_command(p, v);
        v = p;
    }
    printf("%d\n", (int)res.size());
    for (string &s : res)puts(s.c_str());
    return 0;
}
