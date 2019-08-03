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

inline bool isleap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    if (y % 4 == 0) return true;
    return false;
}

inline int weekday(int y, int m, int d) {
    if (m <= 2) m += 12, y--;
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
}

mt19937 gen(time(NULL));
int n;
vector<string> days;
char xlat[12];

bool check(const string& str) {
    static const int mdays[] = { 0,
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int y = 0, m = 0, d = 0;
    for (int i = 0; i < 4; i++) y = y * 10 + xlat[str[i] - 'A'];
    if (y < 1600) return false;
    for (int i = 5; i < 7; i++) m = m * 10 + xlat[str[i] - 'A'];
    if (m == 0 or m > 12) return false;
    for (int i = 8; i < 10; i++) d = d * 10 + xlat[str[i] - 'A'];
    if (d == 0 or d > mdays[m] + bool(m == 2 && isleap(y))) return false;
    return weekday(y, m, d) == 5;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    Rep (t, T) {
        cin >> n; days.resize(n); rep (i, n) cin >> days[i];
        sort(range(days)); days.erase(unique(range(days)), days.end());
        n = days.size();
        shuffle(range(days), gen);
        rep (i, 10) xlat[i] = i;
        cout << "Case #" << t << ": ";
        do {
            rep (i, 10) if (!check(days[gen() % n])) goto fail;
            for (auto& s : days) if (!check(s)) goto fail;
            rep (i, 10) cout << char(xlat[i] + '0');
            goto cont;
        fail:;
        } while (next_permutation(xlat, xlat + 10));
        cout << "Impossible";
        cont:;
        cout << endl;
    }
    return 0;
}
