#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

mt19937_64 gen(time(NULL));

int n;
vector<int> arr;
bool bs[10008];

void query(int len) {
    shuffle(range(arr), gen);
    memset(bs, 0, sizeof bs);
    rep (i, len) bs[arr[i]] = true;
    rep (i, n) printf("%d", int(bs[i]));
    putchar('\n');
    fflush(stdout);
    char res[5]; scanf("%s", res);
    if (res[0] == '+') exit(0);
}

int main() {
    scanf("%d", &n);
    rep (i, n) arr.push_back(i);
    int cur = 1;
    while (true) {
        cur <<= 1;
        if (cur >= n) cur = 1;
        query(cur);
    }
    return 0;
}
