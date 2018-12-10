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

constexpr int BLOCK = 800;
typedef vector<int> vi;
typedef shared_ptr<vi> pvi;
typedef shared_ptr<const vi> pcvi;

struct block {
    pcvi data;
    LL sum; 
    
    block(pcvi ptr) : 
        data(ptr), 
        sum(accumulate(ptr->begin(), ptr->end(), 0ll))
    { }
    
    void merge(const block& another) {
        pvi temp = make_shared<vi>(data->begin(), data->end());
        temp->insert(temp->end(), another.data->begin(), another.data->end());
        *this = block(temp);
    }

    block split(int pos) {
        block result(make_shared<vi>(data->begin() + pos, data->end()));
        *this = block(make_shared<vi>(data->begin(), data->begin() + pos));
        return result;
    }
};

typedef list<block>::iterator lit;

struct blocklist {
    list<block> blk;

    void maintain() {
        lit it = blk.begin();
        while (it != blk.end() and next(it) != blk.end()) {
            lit it2 = it;
            while (next(it2) != blk.end() and 
                     it2->data->size() + next(it2)->data->size() <= BLOCK) {
                it2->merge(*next(it2));
                blk.erase(next(it2));
            }
            ++it;
        }
    }

    lit split(int pos) {
        for (lit it = blk.begin(); ; it++) {
            if (pos == 0) return it;
            while (it->data->size() > pos) {
                blk.insert(next(it), it->split(pos));
            }
            pos -= it->data->size();
        }
    }
    
    LL sum(int l, int r) {
        lit it1 = split(l), it2 = split(r);
        LL res = 0;
        while (it1 != it2) {
            res += it1->sum;
            it1++;
        }
        maintain();
        return res;
    }

    void replace(int l, int r, lit nl, lit nr) {
        lit it1 = split(l), it2 = split(r);
        it2 = blk.insert(it2, nl, nr);
        blk.erase(it1, it2);
        maintain();
    }
} lsrc, lcur;

LL sum(int l, int r) {
    return lcur.sum(l, r);
}

void repcpy(int l, int r, int k) {
    int b = l - k;
    while (l < r) {
        if (r - l >= l - b) {
            lcur.replace(l, l + l - b, lcur.split(b), lcur.split(l));
            l += (l - b);
        } else {
            lcur.replace(l, r, lcur.split(b), lcur.split(b + (r - l)));
            l = r;
        }
    }
}

void changeback(int l, int r) {
    lcur.replace(l, r, lsrc.split(l), lsrc.split(r));
    lsrc.maintain();
}

int n, m;
int a[200005];

int main() {    
    scanf("%d%d", &n, &m);
    rep (i, n) scanf("%d", a + i);
    int lptr = 0, rptr = 0; 
    while (lptr < n) {
        rptr = min(lptr + BLOCK, n);
        lsrc.blk.emplace_back(make_shared<vi>(a + lptr, a + rptr));
        lptr = rptr;
    }
    lcur = lsrc;
    while (m--) {
        int op, l, r; scanf("%d%d%d", &op, &l, &r); l--;
        if (op == 1) {
            printf("%lld\n", sum(l, r)); 
        } else if (op == 2) {
            int k; scanf("%d", &k);
            repcpy(l, r, k);
        } else if (op == 3) {
            changeback(l, r);
        } else assert(0);
    }
    return 0;
}
