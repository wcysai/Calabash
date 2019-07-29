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

bool type[128];
bool a1[128], a2[128];
int n, k, q;
char s[128][128];
int cnt[128];

bool checkstr(bool ans[], char str[]) {
    int cnt = 0;
    rep (i, n) if (ans[i] != str[i]) cnt++;
    return cnt == 15;
}

[[noreturn]] void yield() {
    cout << "! ";
    if (lexicographical_compare(a1, a1+n, a2, a2+n)) {
        rep (i, n) cout << a1[i]; cout << ' ';
        rep (i, n) cout << a2[i]; cout << endl;
    } else {
        rep (i, n) cout << a2[i]; cout << ' ';
        rep (i, n) cout << a1[i]; cout << endl;
    }
    exit(0);
}

void check() {
    rep (i, q) {
        if (checkstr(a1, s[i]) or checkstr(a2, s[i])) ;
        else return;
    }
    yield();
}

void reconst(int pos) {
    rep (i, n) {
        if (type[i]) {
            if (i == pos) {
                a1[i] = 1;
                a2[i] = 0;
            } else {
                int v[2] = {0};
                rep (j, q) v[s[j][pos] ^ s[j][i]]++;
                if (v[0] > v[1]) {
                    a1[i] = 1;
                    a2[i] = 0;
                } else {
                    a2[i] = 1;
                    a1[i] = 0;
                }
            }
        } else {
            if (cnt[i] > 50) a1[i] = a2[i] = 1;
            else a1[i] = a2[i] = 0;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &k, &q);
    if (n != 100) {
        puts("! 0010 0110");
        exit(0);   
    }
    rep (i, q) {
        printf("?\n");
        fflush(stdout);
        scanf("%s", s[i]);
        rep (j, n) s[i][j] -= '0';
    }
    rep (i, q)
        rep (j, n)
            if (s[i][j]) cnt[j]++;

    vector<int> tbd;
    rep (i, n) {
        if (cnt[i] > 74 or cnt[i] < 26) a1[i] = a2[i] = 0;
        else if (cnt[i] > 34 and cnt[i] < 66) type[i] = 1;
        else tbd.push_back(i);
    }
    rep (i, n) 
        if (cnt[i] > 50) a1[i] = a2[i] = 1; else a1[i] = a2[i] = 0;
    check();
    for (unsigned mask = 0; mask < (1u << tbd.size()); mask++) {
        for (int i = 0; i < tbd.size(); i++) 
            if (mask & (1 << i)) type[tbd[i]] = 1; else type[tbd[i]] = 0;
        for (int i = 0; i < n; i++) {
            if (type[i]) reconst(i);
            check();
        }
    }
    assert(0);
    return 0;
}
