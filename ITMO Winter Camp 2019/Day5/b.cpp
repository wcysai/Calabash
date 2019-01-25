#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)

int n;
char str[1 << 20];
uint8_t s[1 << 20];
uint32_t wwt[1 << 24], wt[1 << 24];

uint8_t brev(uint8_t x) {
    uint8_t y = 0;
    rep (i, 8) if (x & (1 << (7 - i))) y |= (1 << i);
    return y;
}

uint32_t getwt(int x) {
    uint32_t ret = 0;
    for (int i = 0; i < 8; i++) 
        if (s[x] & (1 << i)) ret ^= wt[x * 8 + i];
    return ret;
}

void prep() {
    wwt[0] = 1;
    for (int i = 1; i < (1 << 23); i++) {
        wwt[i] = wwt[i-1] << 1;
        if (wwt[i-1] >> 31) wwt[i] ^= 0x04c11db7;
    }
}

int main() {
    prep();
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", str);
        rep (i, n * 8) wt[i] = wwt[i];
        reverse(wt, wt + n * 8);
        rep (i, n) s[i] = brev(str[i]);
        uint32_t cur = 0;
        rep (i, n) cur ^= getwt(i);
        printf("%u\n", cur);
        int q; scanf("%d", &q);
        while (q--) {
            int pos; char buf[4];
            scanf("%d%s", &pos, buf); pos--;
            cur ^= getwt(pos);
            s[pos] = brev(buf[0]);
            cur ^= getwt(pos);
            printf("%u\n", cur);
        }
    }
    return 0;
} 
