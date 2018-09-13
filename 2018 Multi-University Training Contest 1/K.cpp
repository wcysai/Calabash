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

int h, m;
char str[32];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d %d %s", &h, &m, str);
    {
      double off;
      sscanf(str + 3, "%lf", &off);
      off *= 10;
      int t = lround(off);  
      t -= 80;
      m += t * 6;
    }
    while (m < 0) m += 60, h--;
    while (m >= 60) m-= 60, h++;
    while (h < 0) h += 24;
    while (h >= 24) h -= 24;
    printf("%02d:%02d\n", h, m);
  }
  return 0;
}
