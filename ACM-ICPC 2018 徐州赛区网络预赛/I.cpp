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

int n;
char src[1000005], buf[2000005];
char* ptr;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    char ch;
    scanf("%d %c%s", &n, &ch, src);
    ptr = buf;
    for (int i = 0; src[i]; i++) {
      int cur = abs(src[i] - ch);
      *ptr = cur / 10 + '0'; ptr++;
      *ptr = cur % 10 + '0'; ptr++;
    }
    char* beg = buf;
    while (*beg == '0') beg++;
    //printf("%s\n", buf);
    printf("%d\n", max(1, int(ptr - beg)));
  }
  return 0;
}
