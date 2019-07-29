#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
constexpr int BLOCK = 800;
typedef vector<int> vi;
typedef shared_ptr<vi> pvi;

struct block {
    pvi data;
    LL sum;
    int maxv, minv;
    bool rev;
    int add;

    block(pvi ptr) :
        data(ptr),
        sum(accumulate(ptr->begin(), ptr->end(), 0ll)),
        maxv(*max_element(ptr->begin(), ptr->end())),
        minv(*min_element(ptr->begin(), ptr->end())),
        rev(0), add(0) { 
            assert(ptr->size()); 
        }
    
    void fix() {
        if (rev) reverse(data->begin(), data->end());
        if (add) for (auto &x : *data) x += add;
        rev = 0; add = 0;
    }

    void merge(block& another) {
        fix(); another.fix();
        auto temp = make_shared<vi>(data->begin(), data->end());
        temp->insert(temp->end(), another.data->begin(), 
                                  another.data->end());
        *this = block(temp);
    }

    block split(int pos) {
        fix();
        block result(make_shared<vi>(data->begin() + pos, data->end()));
        *this = block(make_shared<vi>(data->begin(), data->begin() + pos));
        return result;
    }
};

typedef list<block>::iterator lit;

struct blocklist {
    list<block> blk;
    
    void debug() {
        puts("!");
        for (auto &x : blk) {
            for (int y : *(x.data)) printf("%d ", y);
            puts("");
        }
        puts("!");
    }

    void pushblk(int* l, int *r) {
        blk.emplace_back(make_shared<vi>(l, r));
    }

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
    
    void rever(int l, int r) {
        lit it1 = split(l), it2 = split(r);
        reverse(it1, it2);        
        while (it1 != it2) {
            it1->rev ^= 1;
            it1++;
        }
        maintain();
    }
    
    void add(int l, int r, int x) {
        lit it1 = split(l), it2 = split(r);
        while (it1 != it2) { 
            it1->add += x;
            it1->sum += LL(x) * it1->data->size();
            it1->minv += x;
            it1->maxv += x;
            it1++;
        }
        maintain();
    }

    void query(int l, int r) {
        lit it1 = split(l), it2 = split(r);
        LL sum = 0;
        int maxv = INT_MIN, minv = INT_MAX;
        while (it1 != it2) {
            sum += it1->sum;
            maxv = max(maxv, it1->maxv);
            minv = min(minv, it1->minv);
            it1++;
        }
        maintain();
        printf("%lld %d %d\n", sum, minv, maxv);
    }
} blklst;

int n;
int arr[100005];

int main() {
    scanf("%d", &n);
    rep (i, n) scanf("%d", arr + i);
    for (int i = 0; i < n; i += BLOCK) 
        blklst.pushblk(arr + i, arr + min(i + BLOCK, n));
    int q; scanf("%d", &q);
    while (q--) {
        char op[12]; scanf("%s", op);
        if (op[0] == 'c') { // change
            int l, r, x; scanf("%d%d%d", &l , &r, &x); l--; 
            blklst.add(l, r, x);
        } else if (op[0] == 'q') {  //query
            int l, r; scanf("%d%d", &l , &r); l--; 
            blklst.query(l, r);
        } else if (op[0] == 'r')  { // reverse
            int l, r; scanf("%d%d", &l , &r); l--;
            blklst.rever(l, r);
        }
    }
    return 0;
}
