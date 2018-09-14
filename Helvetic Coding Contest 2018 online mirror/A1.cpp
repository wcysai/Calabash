#include <bits/stdc++.h>
using namespace std;

#define DEBUG(fmt, ...) fprintf(stderr, "%s: " fmt "\n", __func__, ##__VA_ARGS__)
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int n;
char s[15][15];
char a[15][15];
char b[15][15];
char c[15][15];

bool judge() {
  rep (i, n) rep (j, n) 
    if (s[i][j] != c[i][j]) return false;
  return true;

}

void rot() {
  rep (i, n) rep (j, n)
    c[n-1-j][i] = b[i][j];
}

int main() {
  cin >> n;
  rep (i, n) cin >> s[i];
  rep (i, n) cin >> a[i];
  memcpy(b, a, sizeof a);
  for (int i=0; i<8; i++) {
    memcpy(c, b, sizeof a);
//    DEBUG("");
//    rep (i, n) {rep (j, n) cout << c[i][j]; cout << endl;}
    if (judge()) goto yes;
    rot();
    memcpy(b, c, sizeof a);
  }
  rep (i, n) reverse(a[i], a[i]+n);
  memcpy(b, a, sizeof a);
  for (int i=0; i<8; i++) {
    memcpy(c, b, sizeof a);
    if (judge()) goto yes;
    rot();
    memcpy(b, c, sizeof a);
  }
  cout << "No" << endl;
  return 0;
yes:
  cout << "Yes" << endl;
  return 0;
}
