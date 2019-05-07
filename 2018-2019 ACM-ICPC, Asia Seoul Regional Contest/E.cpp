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

int n;
vector<pair<int, int>> a;
int x[1 << 20];
int sufmax[1 << 20], sufmin[1 << 20];
int prefmax[1 << 20], prefmin[1 << 20];

int max_left(int d) {
    int ptr = 0;
    while (ptr < n and x[ptr] <= d) ptr++;
    return ptr;
}


bool check(int d) {
    if (a[0].first == 0 and x[0] * 2 > d) return false;
    int l = max_left(d / 2);
    if (l == n) return true;
    prefmax[l] = prefmin[l] = x[l];
    for (int i = l ; i < n; i++) {
        prefmax[i + 1] = max(prefmax[i], x[i]);
        prefmin[i + 1] = min(prefmin[i], x[i]);
    }
    if (prefmax[n] - prefmin[n] <= d) return true;
    if (sufmax[l] - sufmin[l] <= d) return true;
    for (int i = l + 1; i < n; i++) {
        if (prefmax[i] + prefmin[i] <= sufmax[i] + sufmin[i] 
                and max(prefmax[i] - prefmin[i], sufmax[i] - sufmin[i]) <= d) 
            return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        int x, y; scanf("%d%d", &x, &y);
        a.emplace_back(x, y);
    }
    sort(range(a));
    rep (i, n) x[i] = a[i].second;
    sufmax[n] = sufmin[n] = x[n-1];
    for (int i = n - 1; i >= 0; i--) {
        sufmax[i] = max(sufmax[i+1], x[i]);
        sufmin[i] = min(sufmin[i+1], x[i]);
    }
    int l = 0, r = 1000000000;
    while (l < r) {
        int mid =  (l + r) / 2;
        if (check(mid)) r = mid; else l = mid + 1;
    }
    printf("%.1f\n", r / 2.0);
    return 0;
}
