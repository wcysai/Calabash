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

#define hash rhewofhwre

int n;
bool hash[10006][256];
int op[10006], v[10006], k[10006];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i <= n; i++)
            memset(hash[i], 0, sizeof(hash[i]));
        rep (i, n) {
            char str[6]; scanf("%s", str);
            if (strcmp(str, "add") == 0) {
                op[i] = 1; scanf("%d", v + i);
            } else if (strcmp(str, "beq") == 0) {
                op[i] = 2; scanf("%d", v + i); scanf("%d", k + i); k[i]--;
            } else if (strcmp(str, "bne") == 0) {
                op[i] = 3; scanf("%d", v + i); scanf("%d", k + i); k[i]--;
            } else if (strcmp(str, "blt") == 0) {
                op[i] = 4; scanf("%d", v + i); scanf("%d", k + i); k[i]--;
            } else if (strcmp(str, "bgt") == 0) {
                op[i] = 5; scanf("%d", v + i); scanf("%d", k + i); k[i]--;
            }
        }

        int pc = 0;
        uint8_t reg = 0;
        hash[pc][reg] = true;
        while (pc < n) {
            switch (op[pc]) {
                case 1:
                    reg += v[pc]; pc++;
                    break;
                case 2:
                    if (reg == v[pc]) pc = k[pc]; else pc++;
                    break;
                case 3:
                    if (reg != v[pc]) pc = k[pc]; else pc++;
                    break;
                case 4:
                    if (reg < v[pc]) pc = k[pc]; else pc++;
                    break;
                case 5:
                    if (reg > v[pc]) pc = k[pc]; else pc++;
                    break;
            }
            if (hash[pc][reg]) {
                puts("No");
                goto cont;
            }
            hash[pc][reg] = true;
        }
        puts("Yes");
        cont:;
    }
    return 0;
}
