#pragma GCC optimize(3)
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
 
#define L 2*
#define R 1+2*
 
typedef vector<ULL> _vec;
int n, N;
char str[1 << 18 | 7];
int rev[1 << 18];
int cnt[6][1 << 16];
 
void prep() {
  cnt[0][0] = 0;
  cnt[0][1] = 1;
  for (int i = 1; i <= 4; i++) {
    for (unsigned mask = 0; mask < (1 << (1 << i)); mask++) {
      unsigned lpart = mask & ((1 << (1 << (i-1))) - 1),
               rpart = mask >> (1 << (i-1));
      cnt[i][mask] = cnt[i-1][lpart^rpart] + cnt[i-1][lpart&rpart]
        + cnt[i-1][lpart|rpart];
    }
  }
}
 
void init() {
  rep (i, N) rev[i] = (rev[i>>1]>>1) | ((i&1)<<(n-1));
  rep (i, N) if (i < rev[i]) swap(str[i], str[rev[i]]);
}
 
template <typename T>
_vec reduce(const _vec& v, T func) {
  int sz = v.size() / 2;
  _vec res(sz);
  rep (i, sz) res[i] = func(v[i], v[i + sz]);
  return res;
}
 
template <int N>
inline int compute(ULL x);
   
template <>
inline int compute<0>(ULL x) {
// _debug("mask=%x", x);
  return cnt[4][x];
}
 
template <>
inline int compute<1>(ULL x) {
  ULL lpart = x & ((1 << 16) - 1), rpart = x >> 16;
// _debug("l=%x, r=%x", lpart, rpart);
   
  return compute<0>(lpart ^ rpart) +
    compute<0>(lpart & rpart) +
    compute<0>(lpart | rpart);
}
 
template <>
inline int compute<2>(ULL x) {
  ULL lpart = x & ((1ull << 32) - 1), rpart = x >> 32;
  return compute<1>(lpart ^ rpart) +
    compute<1>(lpart & rpart) +
    compute<1>(lpart | rpart);
}
 
int cc = 0;
void search(const _vec& v) {
  if (v.size() == 1) {
    cc += compute<2>(v[0]);
  } else {
    _vec r;
    r = reduce(v, bit_and<ULL>());
    search(r);
    r = reduce(v, bit_or<ULL>());
    search(r);
    r = reduce(v, bit_xor<ULL>());
    search(r);
  }
}
 
int main() {
  prep();
  scanf("%d", &n); N = 1 << n;
  scanf("%s", str);
  init();
  if (N < 64) {
    ULL mask = 0;
    for (int j = 0; j < N; j++) mask = mask << 1 | (str[j] == '1');
//    _debug("mask=%x", mask);
    if (N == 32) cc = compute<1>(mask);
    else {
      cc = cnt[n][mask];
    }
  } else {
    _vec v(N / 64);
    for (int i = 0; i < N / 64; i++) {
      ULL mask = 0;
      for (int j = i * 64; j < (i+1) * 64; j++) {
        mask = (ULL(str[j] == '1')) << 63 | mask >> 1;
      }
      v[i] = mask;
    }
    search(v);
  }
  cout << cc << endl;
  return 0; 
}
