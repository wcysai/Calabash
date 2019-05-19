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


const char *sep = "---###---###---###---###---###---###---###---###---###---###---###---###---";
int len, n, lp;
char linebuf[1 << 24];
char text[1 << 24];
char para[1 << 24];
unordered_map<size_t, int> hashset;
hash<string> strhash;
vector<int> hit[1024];
int smpocc[1024];
constexpr int BLOCKSZ = 12;

int main() {
    while (true) {
        cin.getline(linebuf, sizeof linebuf);
        if (strcmp(linebuf, sep) == 0) break;
        strcpy(text + len, linebuf);
        len += strlen(linebuf);
    }
    bool done = false;
    while (!done) {
        lp = 0;
        while (true) {
            if (!cin.getline(linebuf, sizeof linebuf)) {
                done = true;
                break;
            }
            if (strcmp(linebuf, sep) == 0) break;
            strcpy(para + lp, linebuf);
            lp += strlen(linebuf);
        }
        for (int i = 0; i + BLOCKSZ <= lp; i ++) { 
            size_t hval = strhash(string(para + i, para + i + BLOCKSZ));
            if (hashset.count(hval)) hashset[hval] = -1; else hashset[hval] = n;
        }
        n++;
    }
    for (int i = 0; i + BLOCKSZ <= len; i++) {
        size_t hval = strhash(string(text + i, text + i + BLOCKSZ));
        if (hashset.count(hval) == 0) continue;
        int pos = hashset[hval];
        if (pos < 0) continue;
//        printf("%02d", pos);
        hit[pos].push_back(i);
    }
    rep (i, n) {
        nth_element(hit[i].begin(), hit[i].begin() + hit[i].size() / 2, hit[i].end());
        smpocc[i] = hit[i][hit[i].size() / 2];
    }
    vector<int> ans(n); iota(range(ans), 0);
    vector<int> res(n);
    sort(range(ans), [] (int i, int j) { return smpocc[i] < smpocc[j]; });
    rep (i, n) res[ans[i]] = i;
    for (int x : res) cout << x + 1 << ' ';
    return 0;
}
