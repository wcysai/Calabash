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

char str[1 << 20];

map<int, pair<char, list<int>>> tr;

template <typename T>
inline list<int>& lis(T it) {
    return it->second.second;
}

/*
template <typename T>
void print_node(T it) {
    printf("%d, %c\n", );
}
 */

int query(int left, int right) {
    if (tr.size() <= 1) return 0;
    auto lptr = tr.upper_bound(left);
    if (lptr->second.first == ')') lptr++;
    if (lptr == tr.end()) return 0;
    assert(lptr->second.first == '(');
    auto rptr = next(lptr);

    _debug("lptr: %d, %c", lptr->first, lptr->second.first);
    _debug("rptr: %d, %c", rptr->first, rptr->second.first);

    int ans = 0;
    while (rptr != tr.end()) {
        auto &lsl = lptr->second.second;
        auto &lsr = rptr->second.second;

        while (lsl.size() and lsr.size() and lsl.back() >= left and lsr.front() <= right) {
            lsl.pop_back();
            lsr.pop_front();
            ans += 2;
        }

        // if (lsl.size() and lsr.size()) break;
        if (lsl.empty()) {
            tr.erase(lptr);
            if (rptr != tr.begin()) {
                auto pptr = prev(rptr);
                lsr.splice(lsr.begin(), pptr->second.second);
                tr.erase(pptr);
            }

            lptr = next(rptr);
            if (lptr == tr.end()) break;
            rptr = next(lptr);
        } else if (lsr.empty()) {
            tr.erase(rptr);
            auto nptr = next(lptr);
            if (nptr != tr.end()) {
                auto &lsn = lis(nptr);
                lsn.splice(lsn.begin(), lsl);
                tr.erase(lptr);
                lptr = nptr;
                rptr = next(lptr);
            } else break;
        } else if (lsl.back() < left) {
            lptr = next(rptr);
            if (lptr == tr.end()) break;
            rptr = next(lptr);
        } else {
            break;
            // assert(0);
        }// break; // at least one of "lsl.back() >= left and lsr.front() <= right" does not hold
    }

    return ans;
}

void init() {
    int ptr = 0;
    while (str[ptr]) {
        int from = ptr;
        list<int> ls;
        while (str[ptr] == str[from]) {
            ls.push_back(ptr);
            ptr++;
        }
        tr.emplace(ptr, make_pair(str[from], move(ls)));
    }
}

int main() {
    scanf("%s", str);
    init();
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        l--; r--;
        printf("%d\n", query(l, r));
    }
    return 0;
}

/*
(((())()))
 3
 4 9
 2 9
 1 10
*/
