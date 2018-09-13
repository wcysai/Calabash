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

int n, m;
char s[5120], t[5120];

int main() {
  scanf("%s%s", s, t);
  n = strlen(s); m = strlen(t);
  int l = 0, r = 0;
  while (s[l] && s[l] == s[0]) l++;
  while (t[r] && t[r] == t[0]) r++;
  if (s[0] != t[0] || l < r) {
    puts("No");
    return 0;
  }
  r = l;
  while (s[l]) {
    while (t[r] && t[r] != s[l]) r++;
    if (t[r] == 0) {
      puts("No");
      return 0;
    }
    l++; r++;
  }
  puts("Yes");
  return 0;
}
