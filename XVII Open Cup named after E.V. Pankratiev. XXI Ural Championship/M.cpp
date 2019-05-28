#pragma GCC optimize(3)
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

struct bigint {
    int n = 0;
    uint8_t d[60] = {};

    bool operator < (const bigint &rhs) const {
        if (n != rhs.n) return n < rhs.n;
        for (int i = n-1; i >= 0; i--) 
            if (d[i] != rhs.d[i]) return d[i] < rhs.d[i];
        return false;
    }
    
    bigint prepend(uint8_t digit) const {
        bigint ret(*this);
        ret.d[ret.n++] = digit;
        return ret;
    }
    
    bigint append(uint8_t digit) const {
        bigint ret(*this);
        for (int i = ret.n; i; i--) ret.d[i] = ret.d[i-1];
        ret.n++;
        ret.d[0] = digit;
        return ret;
    }
    
    bigint concat(const bigint &rhs) const {
        bigint ret(rhs);
        rep (i, n) 
            ret.d[ret.n++] = d[i];
        return ret;
    }

    bigint operator + (const bigint &rhs) const {
        bigint ret(*this);
        ret.n = max(n, rhs.n);
        rep (i, ret.n) {
            ret.d[i] += rhs.d[i];
            if (ret.d[i] >= 10) {
                ret.d[i] -= 10;
                ret.d[i+1]++;
            }
        }
        if (ret.d[ret.n]) ret.n++;
        return ret;
    }

    void print() const {
        if (n == 0) {
            putchar('0');
        } else {
            for (int i = n - 1; i >= 0; i--) putchar('0' + d[i]);
        }
    }
};

struct state {
    int id;
    bigint up;
    bigint down;

    void print() {
        cout << "> " << id << ' '; up.print(); cout << ' '; down.print(); cout << endl;
    }
};

int n;
unsigned e[10000005];

bigint ans;
vector<state> s;

inline void addans(const bigint& cur) {
//    cout << "ans "; cur.print(); cout << ' ';
    ans = ans + cur;
//    ans.print(); cout << endl;
}

void shift(state cur) {
//    cur.print();
    if (cur.id / 2 * 2 + 1 > n) {
        cur.id /= 2;
        addans(cur.up);
        cur.up = cur.up.append(e[cur.id]);
        cur.down = cur.down.prepend(e[cur.id]);
        shift(cur);
    } else if (s.size() and cur.id / 2 == s.back().id / 2) {
        addans(max(s.back().up.concat(cur.down), cur.up.concat(s.back().down)));
        state ns; ns.id = cur.id / 2;
        ns.up = max(s.back().up, cur.up).append(e[ns.id]);
        ns.down = max(s.back().down, cur.down).prepend(e[ns.id]);
        s.pop_back();
        shift(ns);
    } else {
        s.push_back(cur);
    }
}

int main() {
    cin >> n >> e[1];
    for (int i = 2; i <= n; i++) 
        e[i] = (e[i-1] * 1103515245 + 12345) & 0x7fffffff;
    for (int i = 1; i <= n; i++) e[i] = (e[i] >> 16) % 9 + 1; 
    int split = n;
    while (split & (split - 1)) split -= split & -split;
    for (int i = split; i <= n; i++) {
        state s; s.id = i; s.up = s.up.append(e[i]); s.down = s.down.append(e[i]);
        shift(s);   
    }
    for (int i = n / 2 + 1; i < split; i++) {
        state s; s.id = i; s.up = s.up.append(e[i]); s.down = s.down.append(e[i]);
        shift(s);
    }
    ans.print();
    return 0;
}
