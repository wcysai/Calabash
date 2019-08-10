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

int cnt = 0;
vector<char> seq;

void enter(char ch) {
    seq.push_back(ch);
    if (seq.size() < 3) return;
    auto it = seq.rbegin();
    if (it[0] == it[1] and it[1] == it[2]) {
        cnt++;
        seq.pop_back();
        seq.pop_back();
        seq.pop_back();
    }
}

int main() {
    string str;
    cin >> str;
    for (char ch : str) enter(ch);
    cout << cnt << endl;
    return 0;
}
