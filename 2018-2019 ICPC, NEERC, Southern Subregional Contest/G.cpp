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

int n, m;

int a[128];
int id[128], h[128];

vector<int> seq;
bool work_left(int f) {
    bool flag = false;
    int pos = f + 1;
    for (int i = f; i > 0; i--) {
        if (id[i]) {
            flag = true;
            int cur = h[i];
            for (int j = i + 1; j < pos; j++) {
                cur += a[j];
                if (cur < 0) goto cont;
            }
            seq.push_back(id[i]);
            flag = false;
            pos = i;
        }

        cont:;
    }
    return !flag;
}

bool work_right(int f) {
    bool flag = false;
    int pos = f - 1;
    for (int i = f; i <= n; i++) {
        if (id[i]) {
            flag = true;
            int cur = h[i];
            for (int j = i - 1; j > pos; j--) {
                cur += a[j];
                if (cur < 0) goto cont;
            }
            seq.push_back(id[i]);
            flag = false;
            pos = i;
        }
        cont:;
    }
    return !flag;
}

bool done[128];

int minpos = INT_MAX, maxpos = INT_MIN;

int main() {
    scanf("%d%d", &n, &m);
    Rep (i, m) {
        int s, hp; scanf("%d%d", &s, &hp);
        minpos = min(minpos, s);
        maxpos = max(maxpos, s);
        id[s] = i;
        h[s] = hp;
    }
    Rep (i, n) scanf("%d", a + i);

    for (int i = minpos; i <= maxpos; i++) {
        seq.clear();
        if (work_left(i) == false) continue;
        if (work_right(i + 1) == false) continue;

        for (int x : seq)
            done[x] = true;
        Rep (i, m) if (!done[i]) seq.push_back(i);
        printf("%d\n", i);
        for (int x : seq) {
            printf("%d ", x);
        }
        puts("");
        return 0;
    }

    for (int i = minpos; i <= maxpos; i++) {
        seq.clear();
        if (work_right(i) == false) continue;
        if (work_left(i - 1) == false) continue;

        for (int x : seq)
            done[x] = true;
        Rep (i, m) if (!done[i]) seq.push_back(i);
        printf("%d\n", i);
        for (int x : seq) {
            printf("%d ", x);
        }
        puts("");
        return 0;
    }
    puts("-1");
    return 0;
}
