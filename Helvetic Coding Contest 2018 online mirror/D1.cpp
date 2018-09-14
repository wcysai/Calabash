#include <bits/stdc++.h>
using namespace std;

#define DEBUG(fmt, ...) fprintf(stderr, "%s: " fmt "\n", __func__, ##__VA_ARGS__)
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

map<pair<int, int>, int> cnt;
pair<int, int> pos[200006];

int gcd(int a, int b) {
  if (!b) return a;
  return gcd(b, a%b);
}

int n;
char str[100];
int main() {
  cin >> n;
  rep (i, n) {
    int a, b, c;
    cin >> str;
    sscanf(str, "(%d %d)/%d", &a, &b, &c);
    a+=b;
    int g = gcd(a, c);
    a/=g; c/=g;
    pos[i] = make_pair(a, c);
    cnt[pos[i]] += 1;
  }
  rep (i, n) {
    cout << cnt[pos[i]] << ' ';
  }
  return 0;
}
