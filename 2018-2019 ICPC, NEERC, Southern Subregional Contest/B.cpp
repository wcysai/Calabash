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

const unsigned BLACK = 1, WHITE = 2;

vector<pair<unsigned, int>> blacks;

struct node {
    unsigned mask, tot_mask;
    node *child[2];

    node() {
        mask = 0;
        tot_mask = 0;
        child[0] = child[1] = nullptr;
    }

    node* getch(bool id) {
        if (child[id] == nullptr) child[id] = new node();
        return child[id];
    }

    unsigned compute_tot_mask() {
        tot_mask = mask;
        rep (i, 2) if (child[i]) tot_mask |= child[i]->compute_tot_mask();
        return tot_mask;
    }

    bool check_conflict() {
        if (mask & WHITE) if (tot_mask & BLACK) return true;
        if (mask & BLACK) if (tot_mask & WHITE) return true;
        rep (i, 2) if (child[i] && child[i]->check_conflict()) return true;
        return false;
    }

    void optimize(unsigned ip, int level) {
        if (tot_mask == BLACK) {
            blacks.emplace_back(ip << level, 32 - level);
        } else {
            for (unsigned i = 0; i <= 1; i++) {
                if (child[i]) child[i]->optimize(ip << 1 | i, level - 1);
            }
        }
    }
} root;

void insert(unsigned mask, unsigned ip, int subnet) {
    node* cur = &root;
    while (subnet) {
        cur = cur->getch(ip >> 31);
        ip <<= 1;
        subnet--;
    }
    cur->mask |= mask;
}

tuple<unsigned, unsigned, int> parse_ip(string str) {
    unsigned n1, n2, n3, n4;
    unsigned ip, masked_ip;
    char ch;
    int b;
    sscanf(str.c_str(), "%c%u.%u.%u.%u/%d", &ch, &n1, &n2, &n3, &n4, &b);
    ip = n1 << 24 | n2 << 16 | n3 << 8 | n4;
    masked_ip = ip & (0xFFFF'FFFFull << (32 - b));
    _debug("%c: [%X] %d:%d:%d:%d / %d", ch, masked_ip, n1, n2, n3, n4, b);
    return make_tuple(ch == '+' ? WHITE : BLACK, masked_ip, b);
}

int n;
int main() {
    cin >> n;
    rep (i, n) {
        string str; cin >> str;
        unsigned mask, ip;
        int subnet;
        tie(mask, ip, subnet) = parse_ip(str + "/32");
        insert(mask, ip, subnet);
    }
    root.compute_tot_mask();
    if (root.check_conflict()) {
        puts("-1");
        return 0;
    }
    root.optimize(0, 32);
    printf("%d\n", (int)blacks.size());
    for (auto p : blacks) {
        unsigned ip;
        int subnet;
        tie(ip, subnet) = p;
        _debug("%X, %d", ip, subnet);
        unsigned n1, n2, n3, n4;
        n4 = ip & 0xff; ip >>= 8;
        n3 = ip & 0xff; ip >>= 8;
        n2 = ip & 0xff; ip >>= 8;
        n1 = ip;

        printf("%u.%u.%u.%u/%d\n", n1, n2, n3, n4, subnet);
    }
    return 0;
}
