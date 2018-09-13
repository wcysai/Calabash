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

char str[512];
int pos;

void readnum() {
  if (!isdigit(str[pos])) throw 0;
  if (str[pos] == '0') {
    if (isdigit(str[pos+1])) throw 0;
    else pos++;
    return ;
  }

  while (isdigit(str[pos])) {
    pos++;
  }
  return;
}

void readoperator() {
  if (str[pos] == '+' || str[pos] == '*') {
    pos++;
    return;
  }
  throw 0;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", str);
    for (int i = 0; str[i]; i++) {
      if (str[i] == '?') {
        if (i && str[i-1] == '0' && (i == 1 || !isdigit(str[i-2])))
            str[i] = '+'; else  str[i] = '1';
      }
    }
    try {
      pos = 0;
      readnum();
      while (str[pos]) {
        readoperator();
        readnum();
      }
    } catch(...) {
      puts("IMPOSSIBLE");
      continue;
    }
    puts(str);
  }
  return 0;
}
