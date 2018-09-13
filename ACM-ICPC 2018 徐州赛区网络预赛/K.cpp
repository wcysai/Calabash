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

const int MAXN = 64;
struct matrix {
  bool m[MAXN][MAXN];

  void operator *= (matrix& a) {
    static bool t[MAXN][MAXN];
    rep (i, MAXN) {
      rep (j, MAXN) {
        t[i][j] = 0;
        rep (k, MAXN) t[i][j] ^= m[i][k] and a.m[k][j];
      }
    }
    memcpy(m, t, sizeof(t));
  }
};

matrix r;
void m_powmod(matrix& b, int e) {
  memset(r.m, 0, sizeof(r.m));
  rep (i, MAXN) r.m[i][i] = 1;
  while (e) {
    if (e & 1) r *= b;
    b *= b;
    e >>= 1;
  }
}

typedef array<bitset<64>, 64> mat;

inline mat operator * (mat a, mat b) {
  mat res;
  rep (i, 64) rep (j, i) {
    bool tmp = b[i][j];
    b[i][j] = b[j][i];
    b[j][i] = tmp;
//    swap(b[i][j], b[j][i]);
  }
  rep (i, 64)
    rep (j, 64) 
      res[i][j] = (a[i] & b[j]).count() & 1;
  return res;
}

inline mat mat_powmod(mat b, int e) {
  mat r;
  rep (i, 64) rep (j, 64) r[i][j] = (i == j);
  while (e) {
    if (e & 1) r = r * b;
    b = b * b;
    e >>= 1;
  }
  return r;
}

int n, M, m, t;

int a[8][8], b[8][8];
int fa[64];
int coef[64][64];

int id(int x, int y) {
  return 8 * x + y;
}

bool valid(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

bool validb(int x, int y) {
  return x >= 0 && x < M && y >= 0 && y < M;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(coef, 0, sizeof coef);
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    scanf("%d%d%d", &n, &M, &t); m = M / 2;
    rep (i, n) rep (j, n) {
      scanf("%d", &(a[i][j]));
      fa[id(i, j)] = a[i][j];
    }
    rep (i, M) rep (j, M) scanf("%d", &(b[i][j]));
    rep (i, n) {
      rep (j, n) {
        int did = id(i, j);
        for (int p = i - m; p <= i + m; p++) {
          for (int q = j - m; q <= j + m; q++) {
            if (!valid(p, q)) continue;
            int sid = id(p, q);
//            assert(validb(p-i+m, q-j+m));
//            _debug("%d %d", did, sid);
            coef[did][sid] ^= b[p-i+m][q-j+m] & 1;
          }
        }
      }
    }
    mat matr; 
    rep (i, 64) {
      rep (j, 64) {
        matr[i][j] = coef[i][j] & 1;  
      }
    }
    matr = mat_powmod(matr, t);
    int ans = 0;
    rep (i, 64) {
      bool cur = 0;
      rep (j, 64) {
        cur ^= matr[i][j] & fa[j];
      }
      if (cur) ans++;
    }
    cout << ans << endl;
  }
  return 0;
}
