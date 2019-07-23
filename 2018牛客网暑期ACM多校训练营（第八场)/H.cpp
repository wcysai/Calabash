#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
  
const LL mod = 997137961, inv2 = (mod + 1) / 2;
  
LL powmod(LL b, LL e) {
  LL r = 1;
  while (e) {
    if (e & 1) r = r * b % mod;
    b = b * b % mod;
    e >>= 1;
  }
  return r;
}
  
const int N = 1 << 19;
int n, ans = 0;
int powa[20][1 << 19];
int a[1 << 19], b[1 << 19];
  
void prep() {
  rep (i, N) powa[0][i] = 1;
  rep (i, N) powa[1][i] = a[i];
  for (int x = 2; x < 20; x++) {
    rep (i, N) {
      powa[x][i]= 1ll * powa[x-1][i] * powa[x-1][i] % mod;
    }
  }
}
  
void fwt(int* a) {
  for (int d = 1; d < N; d <<= 1) {
    for (int i = 0; i < N; i += d << 1) {
      rep (j, d) {
        int x = a[i+j], y = a[i+j+d];
        a[i+j] = (x+y)%mod; a[i+j+d] = (x+mod-y)%mod;
//        if (a[i+j] >= mod) a[i+j] -= mod;
//        if (a[i+j+d] >= mod) a[i+j+d] -= mod;
      }
    }
  }
}
  
void ifwt(int* a) {
  for (int d = 1; d < N; d <<= 1) {
    for (int i = 0; i < N; i += d << 1) {
      rep (j, d) {
        int x = a[i+j], y = a[i+j+d];
        a[i+j] = (x+y);
        if (a[i+j] >= mod) a[i+j] -= mod;
        a[i+j+d] = (x+mod-y);
        if (a[i+j+d] >= mod) a[i+j+d] -= mod;
      }
    }
  }
}
  
int tot = 0;
bool check(int x) {
  ifwt(b);
  return b[tot];
}
  
int main() {
  scanf("%d", &n);
  rep (i, n) {
    int x; scanf("%d", &x);
    if (x!=0) a[x]++;
  }
  for(int i=0;i<N;i++)
      if(a[i]>=2)
      {
          if(a[i]&1) a[i]=1; else a[i]=2;
      }
    rep (i, N) if (a[i]&1) tot ^= i;
    a[0] = 1;
    fwt(a);
    prep();
      
    int l = 0, r = 1 << 19;
    int sh = 19;
    rep (i, N) a[i] = 1;
    while (r > l + 1) {
//      _debug("[%d, %d)", l, r);
      int mid = (l + r) / 2;
      rep (i, N) b[i] = 1ll * a[i] * powa[sh][i] % mod;
      if (check(mid)) {
        r = mid;
      } else {
        rep (i, N) a[i] = 1ll * a[i] * powa[sh][i] % mod;
        l = mid;
      }
      sh--;
    }
      
    rep (i, N) b[i] = 1ll * a[i] * powa[sh][1] % mod;
    if (!check(r)) l++;
  
//    _debug("[%d, %d)", l, r);
      
    cout << n - l << endl;
  return 0;
}
