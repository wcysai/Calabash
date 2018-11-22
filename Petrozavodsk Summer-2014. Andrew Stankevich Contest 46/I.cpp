#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr,"[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void)0)
#endif
typedef long long LL;
typedef unsigned long long ULL;
template <typename T> inline T maxz(T& x, T y) { return x = max(x, y); }
template <typename T> inline T minz(T& x, T y) { return x = min(x, y); }

int n;

int r1, l3;
deque<int> pos1, pos3;

int l2, r2;
deque<int> pos2;

int sz[300003], pos[300003];

void Alloc(int pos) {
    printf("A %d\n", pos + 1);
}

void Move(int from, int to) {
    printf("M %d %d\n", from + 1, to + 1);
}

void dealloc(int id) {
   if (sz[id] == 1) {
        if (pos[id] < r1 - 1) {
            Move(r1 - 1, pos[id]);
            pos[pos1.back()] = pos[id];
            swap(pos1[pos[id]], pos1.back());
        }
        r1--;
        pos1.pop_back();
   } else if (sz[id] == 2) {
        if (pos[id] == l2) {
            pos2.pop_front();
            l2 += 2;
        } else if (pos[id] == r2 - 2) {
            pos2.pop_back();
            r2 -= 2;
        } else {
            int index = (pos[id] - l2) / 2;
            pos[pos2.front()] = pos[id];
            Move(l2, pos[id]);
            swap(pos2[index], pos2.front());
            l2 += 2;
            pos2.pop_front();
        }
   } else if (sz[id] == 3) {
        _debug("Deallocation 3 of id %d", id);
        if (pos[id] > l3) {
            int index = (pos[id] - l3) / 3;
            pos[pos3.front()] = pos[id];
            Move(l3, pos[id]);
            swap(pos3[index], pos3.front());
        }
        l3 += 3;
        pos3.pop_front();
   } else assert(0);
   printf("D\n");
}

void shl2() {
    if (l2 == r2) {
        l2 -= 2; 
        r2 -= 2;
        return;
    }
    Move(r2 - 2, l2 - 2);
    pos[pos2.back()] = l2 - 2;
    pos2.push_front(pos2.back());
    pos2.pop_back();
    l2 -= 2; r2 -= 2;
}

void shr2() {
    if (l2 == r2) {
        l2 += 2;
        r2 += 2;
        return ;
    }
    Move(l2, r2);
    pos[pos2.front()] = r2;
    pos2.push_back(pos2.front());
    pos2.pop_front();
    l2 += 2; r2 += 2;
}

void alloc1(int id) {
    sz[id] = 1;
    if (l2 - r1 < 1) shr2();
    pos1.push_back(id);
    pos[id] = r1;
    r1++;
    Alloc(pos[id]);
}

void alloc2(int id) {
    sz[id] = 2;
    if (l2 - r1 >= 2) {
        pos2.push_front(id);
        l2 -= 2;
        pos[id] = l2;
    } else {
        assert(l3 - r2 >= 2);
        pos2.push_back(id);
        pos[id] = r2;
        r2 += 2;
    }
    Alloc(pos[id]);
}

void alloc3(int id) {
    sz[id] = 3;
    int cnt = 0;
    while (l3 - r2 < 3) {
        cnt++;
        shl2();
    }
    assert(cnt <= 2);
    pos3.push_front(id);
    l3 -= 3;
    pos[id] = l3;
    Alloc(pos[id]);
}

int main() {
    scanf("%d", &n);
    r1 = 0;
    l2 = r2 = 0;
    l3 = n;
    int op, id = 0; 
    while (scanf("%d", &op), op) {
        _debug("B: r1=%d, l2=%d, r2=%d, l3=%d", r1, l2, r2, l3);
        id++;
        switch (op) {
        case 1:
            alloc1(id);
            break;
        case 2:
            alloc2(id);
            break;
        case 3:
            alloc3(id);
            break;
        default:
            dealloc(-op);
            break;
        }
        _debug("A: r1=%d, l2=%d, r2=%d, l3=%d", r1, l2, r2, l3);
        assert(r1 >= 0 and r1 <= l2 and l2 <= r2 and r2 <= l3 and l3 <= n);
        fflush(stdout);
    }
    return 0;
}
