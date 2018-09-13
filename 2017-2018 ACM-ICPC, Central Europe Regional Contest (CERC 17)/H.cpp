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

int th;

vector<string> name;
struct dir {
  int size;
  vector<int> files;
  map<string, dir> subdirs;
  bool flag;

  int getsize() {
    size = 0;
    flag = false;
    for (auto& d : subdirs) {
      int cur = d.second.getsize();
      if (cur >= th) flag = true;
      size += cur;
    }
    for (int x : files) size += x;
    return size;
  }

  void print() {
    char ctl;
    if (subdirs.size() == 0) ctl = ' ';
    else if (flag) {
      ctl = '-';
    } else ctl = '+';
    cout << ctl << ' ';
    cout << '/';
    for (auto str : name) cout << str << '/';
    cout << ' ' << size << endl;
    if (ctl == '+') return;
    for (auto& d : subdirs) {
      name.push_back(d.first);
      d.second.print();
      name.pop_back();
    }
  }

} root;

int main() {
  int n;
  cin >> n;
  rep (i, n) {
    string str;
    int sz;
    cin >> str >> sz;
    int beg = 1, ptr = 1;
    dir *cur = &root;
    while (str[ptr]) {
      while (str[ptr] && str[ptr] != '/') ptr++;
      if (str[ptr] == 0) break;
      string dirname = str.substr(beg, ptr - beg);
//      _debug("%s", dirname.c_str());
      cur = &(cur->subdirs[dirname]);
      beg = ptr + 1;
      ptr++;
    }
//    _debug("1");
    cur->files.push_back(sz);
  }
  cin >> th;
  root.getsize();
  root.print();
  return 0;
}
