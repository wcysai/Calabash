#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)

typedef long long LL;
typedef unsigned long long ULL;

int adj[512 * 5000][10];
bool vis[512 * 5000];
int dist[512 * 5000];
int d, s;

int enc(int sum, int rem) {
    return sum * d + rem;
}

pair<int, int> dec(int code) {
    return {code / d, code % d};
}

bool bfs() {
    fill(range(dist), INT_MAX);
    dist[enc(0, 0)] = 0;
    queue<int> q; q.push(enc(0, 0));
    while (q.size()) {
        int x = q.front(); q.pop();
        rep (dig, 10) {
            int y = adj[x][dig];
            if (dist[y] > dist[x] + 1) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }
    return dist[enc(s, 0)] != INT_MAX;
}

string str;
void construct(int cur) {
    if (cur == enc(s, 0)) {
        cout << str << endl;
        exit(0);
    }
    if (vis[cur]) return;
    vis[cur] = true;
    rep (dig, 10) {
        int next = adj[cur][dig];
        if (dist[next] != dist[cur] + 1) continue;
        str.push_back('0' + dig);
        construct(next);
        str.pop_back();
    }
}

int main() {
    cin >> d >> s;
    for (int sum = 0; sum <= s; sum++) {
        for (int rem = 0; rem < d; rem++) {
            int current_state = enc(sum, rem);
            for (int dig = 0; dig < 10; dig++) {
                int next_sum = sum + dig, next_rem = (rem * 10 + dig) % d;
                if (next_sum > s) continue;
                int next_state = enc(next_sum, next_rem);
                adj[current_state][dig] = next_state;
            }
        }
    }
    if (!bfs()) {
        puts("-1");
        return 0;
    }
    construct(enc(0, 0));
    return 0;
}
