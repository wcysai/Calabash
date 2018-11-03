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

int n;
char buf[1024];

int get_arrsz(const char *str) {
    while (*str) {
        if (*str == '[') {
            _debug("Array");
            int ret; sscanf(str + 1, "%d", &ret);
            return ret;
        }
        str++;
    }
    return 1;
}


void work(int kase) {
    scanf("%d", &n); getchar();
    LL tot = 0;
    while (n--) {
        fgets(buf, sizeof buf, stdin);
        int Bool = 0, Char = 0, Int = 0, Long = 0, I128 = 0, Float = 0, Double = 0;
        int arrsz = 1, typsz = 0;
        for (const char *tok = strtok(buf, " "); tok != NULL; tok = strtok(NULL, " ")) {
            _debug("token: %s", tok);
            if (strcmp(tok, "bool") == 0) Bool++;
            else if (strcmp(tok, "char") == 0) Char++;
            else if (strcmp(tok, "int") == 0) Int++;
            else if (strcmp(tok, "long") == 0) Long++;
            else if (strcmp(tok, "float") == 0) Float++;
            else if (strcmp(tok, "double") == 0) Double++;
            else if (strcmp(tok, "__int128") == 0) I128++;
            else arrsz = get_arrsz(tok);
        }
        if (Long and Double) typsz = 16;    // long double
        else if (Long == 2) typsz = 8;     // long long
        else if (I128) typsz = 16;
        else if (Float) typsz = 4;
        else if (Double) typsz = 8;
        else if (Int) typsz = 4;
        else if (Bool) typsz = 1;
        else if (Char) typsz = 1;
        else assert(0);
        _debug("typesz=%d, arrsz=%d", typsz, arrsz);
        tot += typsz * arrsz;
    }
    printf("Case #%d: %d\n", kase, int((tot + 1023) / 1024));
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T)
        work(t);
    return 0;
}
