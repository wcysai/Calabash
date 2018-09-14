#include <bits/stdc++.h>
using namespace std;

#define DEBUG(fmt, ...) fprintf(stderr, "%s: " fmt "\n", __func__, ##__VA_ARGS__)
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int n, m;
char stra[2005][205];
char strb[205][2005];
unsigned a[2005][205], b[2005][205];
unsigned hasha[2005];
unsigned hashb[205];

unsigned powmod(unsigned x, unsigned e) {
  unsigned r = 1;
  while (e) {
    if (e&1) r*=x;
    x*=x;
    e>>=1;
  }
  return r;
}

vector<int> mlist;
void match() {
  mlist.clear();
  for (int off=0; off+m<=n; off++) {
    for (int i=0; i<m; i++)
      if (hasha[off+i] != hashb[i]) goto fail;
    mlist.push_back(off);
fail:;
  }
}

bool judge(int x, int y) {
  rep (i, m) rep (j, m) {
    if (stra[i+x][j] != strb[i][j+y]) return false;
  }
  return true;
}

unsigned divp;
int main() {
  cin >> n >> m;
  divp = powmod(29, m);
  rep (i, n) cin >> stra[i];
  rep (i, m) cin >> strb[i];
  rep (i, n) rep (j, m) {
    a[i][j] = stra[i][j] - 'a';
    b[i][j] = strb[j][i] - 'a';
  }
  rep (i, n) {
    hasha[i] = 0;
    rep (j, m) {
      hasha[i] *= 29; hasha[i] += a[i][j];
    }
  }
  for (int i = m-1; i<n; i++) {
    if (i < m) {
      rep (i, m) {
        rep (j, m) {
          hashb[j] *= 29;
          hashb[j] += b[i][j];
        }
      }
    } else {
      rep (j, m) {
        hashb[j] *= 29;
        hashb[j] += b[i][j] - divp * b[i-m][j];
      }
    }
    match();
    for (int x : mlist) {
      int y = i-m+1;
      if (judge(x, y)) {
        cout << x + 1 << ' ' << y + 1 << endl;
        return 0;
      }
    }
  }
  return 0;
}
