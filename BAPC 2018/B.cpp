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
typedef pair<int, int> Date;

int n;
const int day[] = {
    31, 28, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31
};

Date inc(Date d) {
    d.second++;
    if (d.second == day[d.first]) {
        d.second = 0;
        d.first++;
    }
    if (d.first == 12) d.first = 0;
    return d;
}

int datediff(Date a, Date b) {
    int ans = 0;
    do {
        a = inc(a);
        ans ++;
    } while (a != b);
    return ans;
}

Date readdate() {
    int m, d; scanf("%d-%d", &m, &d);
    m--; d--; return {m, d};
}

void writedate(Date d) {
    printf("%02d-%02d\n", d.first + 1, d.second + 1);
}

set<Date> dates;

tuple<int, int, Date> check(Date dt) {
    int ans = 0;
    while (!dates.count(inc(dt))) {
        dt = inc(dt);
        ans++;
    }
    return {ans, -datediff({9, 26}, dt), dt};
}

int main() {
    scanf("%d", &n);
    rep (i, n) { 
        char str[64]; scanf("%s", str);
        dates.insert(readdate());
    }
    tuple<int, int, Date> ans = {-1, -1, {0, 0}};
    for (Date dt : dates) {
        ans = max(ans, check(dt)); 
    }
    writedate(get<2>(ans));
    return 0;
}
