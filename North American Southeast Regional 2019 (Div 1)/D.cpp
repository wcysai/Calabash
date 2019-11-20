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

const int MAXN = 1024;

vector<int> adj[MAXN];
queue<int> q;
int n;
int label[MAXN], mate[MAXN], save[MAXN], used[MAXN];

void rematch(int x, int y) {
    int m = mate[x]; mate[x] = y;
    if (mate[m] == x) {
        if (label[x] <= n) {
            mate[m] = label[x]; rematch(label[x], m);
        } else {
            int a = 1 + (label[x] - n - 1) / n;
            int b = 1 + (label[x] - n - 1) % n;
            rematch(a, b); rematch(b, a);
        }
    }
}

void traverse(int x) {
    Rep (i, n) save[i] = mate[i];
    rematch(x, x);
    Rep (i, n) {
        if (mate[i] != save[i]) used[i]++;
        mate[i] = save[i];
    }
}

void relabel(int x, int y) {
    Rep (i, n) used[i] = 0;
    traverse(x); traverse(y);
    Rep (i, n) {
        if (used[i] == 1 and label[i] < 0) {
            label[i] = n + x + (y - 1) * n;
            q.push(i);
        }
    }
}

int solve() {
    Rep (i, n) {
        if (mate[i]) continue;
        Rep (j, n) label[j] = -1;
        label[i] = 0; q = queue<int>(); q.push(i);
        while (q.size()) {
            int x = q.front(); q.pop();
            for (int y : adj[x]) {
                if (mate[y] == 0 and i != y) {
                    mate[y] = x; rematch(x, y); q = queue<int>(); break;
                }
                if (label[y] >= 0) { relabel(x, y); continue; }
                if (label[mate[y]] < 0) {
                    label[mate[y]] = x;
                    q.push(mate[y]);
                }
            }
        }
    }
    int cnt = 0;
    Rep (i, n) cnt += (mate[i] > i);
    return cnt;
}


string s[512];

int dif(const string& a, const string& b) {
    int sz = 0;
    rep (i, a.size()) sz += a[i] != b[i];
    return sz;
}

int main() {
    cin >> n;
    Rep (i, n) cin >> s[i];
    Rep (i, n) Rep (j, n) if (dif(s[i], s[j]) == 2) adj[i].push_back(j);
    cout << n - solve() << endl;
    return 0;
}
