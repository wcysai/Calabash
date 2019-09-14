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

typedef array<int, 5> suite;
int n;
char name[100005][12];
tuple<int, int, int> value[100005];

suite parse(char buf[]) {
    suite ret;
    int cnt = 0;
    while (cnt < 5) {
        if (*buf == '1') {
            ret[cnt] = 10;
            buf += 2;
        } else {
            char cur = *buf++;
            if (isdigit(cur)) ret[cnt] = cur - '0';
            else if (cur == 'A') ret[cnt] = 1;
            else if (cur == 'J') ret[cnt] = 11;
            else if (cur == 'Q') ret[cnt] = 12;
            else if (cur == 'K') ret[cnt] = 13;
            else {
                fprintf(stderr, "mysterious character '%c', cnt=%d\n", cur, cnt);
                assert(!"unexpected card");
            }
        }
        cnt++;
    }
    return ret;
}

tuple<int, int, int> identify(suite st) {
    sort(range(st));

    // royal straight
    if (st == suite{{1, 10, 11, 12, 13}}) return make_tuple(8, 0, 0);

    // straight
    if (st[1] == st[0] + 1 and st[2] == st[1] + 1 and st[3] == st[2] + 1 and st[4] == st[3] + 1)
        return make_tuple(7, st[0], 0);

    // 4 of a kind
    if (st[0] == st[1] and st[1] == st[2] and st[2] == st[3]) return make_tuple(6, st[0], st[4]);
    if (st[1] == st[2] and st[2] == st[3] and st[3] == st[4]) return make_tuple(6, st[1], st[0]);

    // full house
    if (st[0] == st[1] and st[1] == st[2] and st[3] == st[4]) return make_tuple(5, st[0], st[3]);
    if (st[0] == st[1] and st[2] == st[3] and st[3] == st[4]) return make_tuple(5, st[2], st[0]);

    // 3 of a kind
    if (st[0] == st[1] and st[1] == st[2]) return make_tuple(4, st[0], st[3] + st[4]);
    if (st[1] == st[2] and st[2] == st[3]) return make_tuple(4, st[1], st[0] + st[4]);
    if (st[2] == st[3] and st[3] == st[4]) return make_tuple(4, st[2], st[0] + st[1]);

    // 2 pairs
    if (st[0] == st[1] and st[2] == st[3]) return make_tuple(3, st[0] + st[2] * 100, st[4]);
    if (st[1] == st[2] and st[3] == st[4]) return make_tuple(3, st[1] + st[3] * 100, st[0]);
    if (st[0] == st[1] and st[3] == st[4]) return make_tuple(3, st[0] + st[3] * 100, st[2]);

    // pair
    if (st[0] == st[1]) return make_tuple(2, st[0], st[2] + st[3] + st[4]);
    if (st[1] == st[2]) return make_tuple(2, st[1], st[0] + st[3] + st[4]);
    if (st[2] == st[3]) return make_tuple(2, st[2], st[0] + st[1] + st[4]);
    if (st[3] == st[4]) return make_tuple(2, st[3], st[0] + st[1] + st[2]);

    // high card
    return make_tuple(1, st[0] + st[1] + st[2] + st[3] + st[4], 0);
}

int main() {
    while (scanf("%d", &n) == 1) {
        rep (i, n) {
            char buf[12];
            scanf("%s%s", name[i], buf);
            value[i] = identify(parse(buf));
        }
        vector<int> id(n);
        iota(range(id), 0);
        sort(range(id), [] (int x, int y) {
            if (value[x] == value[y]) return strcmp(name[x], name[y]) < 0;
            return value[x] > value[y];
        });
        for (int x : id) puts(name[x]);
    }
    return 0;
}
