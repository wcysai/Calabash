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
 
 
#define pow owahgrauhgso
 
const ULL m = 1000000007;
 
ULL k;
 
ULL powmod(ULL b, ULL e) {
  ULL r = 1;
  while (e) {
    if (e & 1) r = r * b % m;
    b = b * b % m;
    e >>= 1;
  }
  return r;
}
 
const int MAXN = 1006;
ULL inv[MAXN];
 
void init_inv() {
  inv[1] = 1;
  for (int i = 2; i <= k+1; i++) {
    inv[i] = (m - m / i) * inv[m % i] % m;
    assert(inv[i] * i % m == 1);
  }
}
 
ULL pow[MAXN];
ULL prime[MAXN], cnt;
 
void sieve() {
  cnt = 0;
  memset(pow, 0, sizeof pow);
  pow[1] = 1;
  for (int i = 2; i <= k+1; i++) {
    if (!pow[i]) {
      pow[i] = powmod(i, k);
      prime[cnt++] = i;
      for (int j = 0; j < cnt && i*prime[j] <= k+1; j++) {
        pow[i * prime[j]] = pow[i] * pow[prime[j]] % m;
        if (i % prime[j] == 0) break;
      }
    }
  }
}
 
ULL sum[MAXN];
ULL ans[MAXN];
 
auto addmod = [](ULL a, ULL b) -> ULL {return (a+b)%m;};
 
ULL lagrange(int n) {
  ULL p;
  p = 1;
  for (int i=0; i<=k+1; i++) {
    if (i) p = p * inv[i] % m;
    ans[i] = (k+1-i)&1 ? m-sum[i] : sum[i];
    ans[i] = ans[i] * p % m;
    p = p * (m + n - i) % m;
  }
  p = 1;
  for (int i=k+1; i>=0; i--) {
    if (k+1-i) p = p * inv[k+1-i] % m;
    ans[i] = ans[i] * p % m;
    p = p * (m + n - i) % m;
  }
  return accumulate(ans, ans+k+2, 0, addmod);
}
 
ULL calc(int l, int r, int K) {
  k = K;
  init_inv();
  sieve();
  partial_sum(pow, pow+k+2, sum, addmod);
  ULL ans =  (lagrange(r) - lagrange(l) + m) % m;
//  _debug("l=%d, r=%d, k=%d, ans=%llu", l, r, K, ans);
  return ans;
}
 
int main() {
  int n;
  int a[1024];
  ULL pre[1024];
  while (scanf("%d", &n) != EOF) {
    Rep (i, n) scanf("%d", &a[i]);
    sort(a+1, a+1+n);
    pre[0] = 1;
    Rep (i, n) pre[i] = pre[i-1] * a[i] % m;
    LL cnt = 0, tot = pre[n] * a[n] % m;
    for (int i = n; i; i--) {
      int pw = n - i + 1;
      cnt = cnt + pre[i-1] * calc(a[i-1]-1, a[i]-1, pw);
      cnt %= m;
    }
    cout << (tot + m - cnt) % m << endl;
  }
 
  return 0;
}
