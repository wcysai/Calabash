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

namespace pollardrho {

    LL gcd(LL a, LL b) {return b ? gcd(b, a % b) : a;}

    inline LL mulmod(LL a, LL b, LL m) {
        return __int128(a) * __int128(b) % m;
    }

    LL powmod(LL b, LL e, LL m) {
        LL r = 1;
        while (e) {
            if (e & 1) r = mulmod(r, b, m);
            b = mulmod(b, b, m);
            e >>= 1;
        }
        return r;
    }

    bool test(LL n){
        if (n < 3) return n==2;
        // ! The array a[] should be modified if the range of x changes.
        static const LL a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, LLONG_MAX};
        LL r = 0, d = n-1, x;
        while (~d & 1) d >>= 1, r++;
        for (int i=0; a[i] < n; i++){
            x = powmod(a[i], d, n);
            if (x == 1 || x == n-1) goto next;
            rep (i, r) {
                x = mulmod(x, x, n);
                if (x == n-1) goto next;
            }
            return false;
            next:;
        }
        return true;
    }

    map<LL, int> mp;
    mt19937_64 gen(time(NULL));

    void PollardRho(LL n) {
        LL c, x, y, d;
        while (n % 2 == 0) {
            mp[2]++;
            n /= 2;
        }
        if (n == 1) return;

        if (test(n)) {
            mp[n]++;
            return;
        }

        d = n;
        static int counter = 0;
        while (d == n) {
            x = y = 2;
            d = 1;
            c = rand() % (n - 1) + 1;
            while (d == 1) {
                counter++;
                assert(counter < 500000);
                x = (mulmod(x, x, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                d = gcd(x > y ? x - y : y - x, n);
            }
        }
        PollardRho(d);
        PollardRho(n / d);
    }

    vector<int> work(LL n) {
        mp.clear();
        PollardRho(n);
        vector<int> result;
        for (auto p : mp) {
            result.push_back(p.second);
        }
        return result;
    }
}

const LL mod = 998244353;
int sz;
vector<int> res, x;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

bool adv() {
    x[0]++;
    for (int i = 0; i < sz; i++) {
        if (x[i] > min(2, res[i])) {
            x[i] = 0;
            if (i == sz - 1) return false;
            x[i+1]++;
        } else {
            return true;
        }
    }
}

LL szn2[100] = {1}, sz2[100] = {1};

void init() {
    for (int i = 1; i < 80; i++) {
        szn2[i] = szn2[i-1] * (mod - 2) % mod;
    }
    for (int i = 1; i < 80; i++) {
        sz2[i] = sz2[i-1] * 2 % mod;
    }
}

inline LL getmu() {
    int cnt = 0;
    for (int d : x) {
        switch (d) {
            case 0 : break;
            case 1 : cnt++;
            case 2 : break;
            default: return 0;
        }
    }
    return szn2[cnt];
}

inline LL get2d() {
    // LL ans = 1;
    LL b = 1;
    rep (i, sz) {
        LL d = res[i] - x[i];
        // ans = ans * sz2[d + 1] % mod;
        b *= (d + 1);
    }
    // return (ans + mod - 1) % mod;
    return (powmod(2, b) + mod - 1) % mod;
}

/*
LL aa = 0;
void dfs(int cur) {
    if (cur == sz) {
        aa += getmu() * get2d();
        aa %= mod;
        return;
    }
    for (int i = 0; i <= min(2, ))
}
*/

LL work(LL m) {
    res = pollardrho::work(m);
    sz = res.size();
    x.resize(sz);
    LL ans = 0;
    // int cnt = 0;
    do {
        // cnt++;
        // for (auto i : x) cout << i << ' ' ;cout << endl;
        LL t = getmu();
        if (t == 0) continue;
        ans += get2d() * t;
        ans %= mod;
    } while (adv());
    // cout << cnt << endl;
    return ans;
}

int main() {
    LL m; cin >> m;
    srand(time(NULL));
    init();
    if (m == 1) {
        cout << 1 << endl;
    } else {
        cout << work(m) << endl;
    }
    return 0;
}
