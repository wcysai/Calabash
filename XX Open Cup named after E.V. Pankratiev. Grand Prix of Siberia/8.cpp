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
vector<int> rcd[100005];
int perm[100005];

bool compare(int i, int j) {
    rcd[i].push_back(j);
    rcd[j].push_back(i);
    printf("? %d %d\n", i, j); fflush(stdout);
    char str[2];
    scanf("%s", str);
    return str[0] == '<';
}

int solve(int l, int r) {
    if (r == l + 1) return l;
    int mid = (l + r) / 2;
    return min(solve(l, mid), solve(mid, r), compare);
}

int main() {
    scanf("%d", &n);
    // iota(perm, perm + n, 0); random_shuffle(perm, perm + n);
    auto vec = rcd[solve(0, n)];
    int val = *min_element(range(vec), compare);
    printf("! %d\n", val); fflush(stdout);
    return 0;
}
