#include <bits/stdc++.h>
using namespace std;
 
#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;
 
int n, cn, cnt;
char cur[1000005];
char str[1000005];
int pos[1000005][26];
 
int main() {
  int t; scanf("%d", &t);
  while (t--) {
    memset(pos, -1, sizeof pos);
    cnt = 0;
    scanf("%d", &n);
    int cpos, spos;
    rep (i, n) {
      scanf("%s", cur);
      cpos = spos = 0;
      cn = strlen(cur);
      while (cpos < cn && spos < cnt) {
        spos = pos[spos][cur[cpos] - 'a'];         
        if (spos == -1) {
          spos = cnt;
        } else {
          cpos++;
          spos++;
        }
      }
      for (int i = cpos; i < cn; i++) {
        str[cnt] = cur[i];
        for (int j = cnt; j >= 0 && pos[j][cur[i] - 'a'] < 0; j--) {
          pos[j][cur[i] - 'a'] = cnt;
        }
        cnt++;
      }
    }
    str[cnt] = 0;
    printf("%s\n", str);
  }
  return 0;
}
