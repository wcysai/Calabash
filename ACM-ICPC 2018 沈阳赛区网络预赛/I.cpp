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

int bn;
bool bs[1000006];

namespace verifier {
  int num;
  int pos, id;
  int mask[4] = { 0x8, 0x4, 0x2, 0x1 };
  char str[200005];
  
  inline void ichar() {
    id = 0;
    char ch = str[pos];
//    putchar(ch); putchar('\n');
    if (isdigit(ch)) {
      num = ch - '0';
    } else {
      num = toupper(ch) - 'A' + 10;
    }
  }
  
  bool eat() {
    int res = num & mask[id];
    id++;
    if (id == 4) {
      pos++;
      ichar();
    }
//    putchar('0' + bool(res));
    return res;
  }
  
  void init() {
    bn = num = pos = id = 0;
    scanf("%s", str);
    int len = strlen(str);
//    _debug("%s !", str);
    ichar();
    for (int i = 0; i < len * 4 / 9; i++) {
      bool flag = false;
      bool res[9];
      for (int i = 0; i < 9; i++) {
        res[i] = eat();
        flag ^= res[i];
      }
      if (flag) {
        rep (i, 8) bs[bn++] = res[i];
      }
    }
//    fflush(stdout);
//    _debug("!");
//    rep (i, bn) printf("%d", bs[i]);
  }
}

struct node {
  node *son[2] = {NULL, NULL};
  bool flag = false; char ch;
} root;

int n, m;
void build_trie() {
  int asc, len; char ch;
  char bs[12];
  memset(&root, 0, sizeof root);
  rep (i, n) {
    scanf("%d%s", &asc, bs);
    _debug("%c: %s", asc, bs);
    ch = asc;
    len = strlen(bs);
    node* cur = &root;
    rep (i, len) {
      bs[i] -= '0';
      if (cur->son[bs[i]] == NULL) cur->son[bs[i]] = new node;
      cur = cur->son[bs[i]];
    }
    cur->ch = ch;
    cur->flag = true;
  }
}

char res[100006];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &m, &n);
    build_trie();
    verifier::init();
    int ptr = 0;
    rep (i, m) {
      node* cur = &root;
      while (!cur->flag) {
        cur = cur->son[bs[ptr++]];
      }
      res[i] = cur->ch;
    }
    res[m] = 0;
    printf("%s\n", res);
  }
  return 0;
}
