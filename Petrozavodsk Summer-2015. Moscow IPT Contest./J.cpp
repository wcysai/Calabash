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

bool query(int u, int v) {
    printf("? %d %d\n", u, v);
    fflush(stdout);
    char ret[5];
    scanf("%s", ret);
    return ret[0] == 'W';
}

int n;
int pivot;
vector<int> remain;

int getrem() {
    int x = remain.back(); remain.pop_back();
    return x;
}

deque<int> white, black;

int main() {
    scanf("%d", &n);
    Rep (i, n) remain.push_back(i);
    pivot = getrem();
    while (remain.size()) {
        if (black.empty()) {
            if (query(pivot, remain.back())) {
                black.push_back(getrem());
            } else {
                white.push_front(pivot);
                pivot = getrem();
            }
        } else if (white.empty()) {
            if (query(pivot, remain.back())) {
                black.push_front(pivot);
                pivot = getrem();
            } else {
                white.push_back(getrem());
            }
        } else {
            if (query(black.back(), white.back())) {
                if (query(white.back(), remain.back())) {
                    black.push_back(white.back()); white.pop_back();
                    black.push_back(getrem());
                } else {
                    white.push_back(getrem());
                }
            } else {
                if (query(black.back(), remain.back())) {
                    black.push_back(getrem());
                } else {
                    white.push_back(black.back()); black.pop_back();
                    white.push_back(getrem());
                }
            }
        }
    }
    printf("! %d", pivot);
    for (auto it = white.begin(); it != white.end(); it++) {
        printf(" %d", *it);
    }
    for (auto it = black.rbegin(); it != black.rend(); it++) {
        printf(" %d", *it);
    }
    fflush(stdout);
    return 0;
}
