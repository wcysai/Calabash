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

typedef pair<LL, LL> interval;

inline interval operator + (interval l, interval r) {
  return {l.first + r.first, l.second + r.second};
}

inline interval operator - (interval l, interval r) {
  return {l.first - r.second, l.second - r.first};
}

inline interval operator * (interval l, interval r) {
  return minmax({l.first * r.first,   l.second * r.first, 
                 l.first * r.second,  l.second * r.second});
}

ostream& operator << (ostream& lhs, interval rhs) {
  lhs << rhs.first << ' ' << rhs.second;
  return lhs;
}

int pos, len;
char expr[256];

interval get_immd(int l, int r) {
  _debug("%d-%d", l, r);
  LL x = 0;
  for (int i = l; i <= r; i++) {
    x = x * 10 + expr[i] - '0';
  }
//  cout << interval(x, x) << endl;
  return {x, x};
}

inline interval op_d(interval l, interval r) {
  // TODO
  interval ans {l.first * 1, l.second * max(r.first, r.second)};
//  cout << ans << endl;
  return ans;
}

bool check_parentheses(int l, int r) {
  if (expr[l] == '(' && expr[r] == ')') {
    int cnt = 0;
    for (int i = l + 1; i < r; i++) {
      if (expr[i] == '(') cnt++;
      if (expr[i] == ')') {
        cnt--;
        if (cnt < 0) return false;
      }
    }
    return true;
  }
  return false;
}

#define PM    1
#define MULT  2
#define D     3

int max_precedence(int l, int r) {
  int cnt = 0;
  int prec = INT_MAX;
  for (int i = l; i <= r; i++) {
    switch (expr[i]) {
      case '(' : cnt++; break;
      case ')' : cnt--; break;
      case '+' : case '-': 
        if (cnt == 0) prec = min(prec, PM); 
        break;
      case '*' :
        if (cnt == 0) prec = min(prec, MULT);
        break;
      case 'd' :
        if (cnt == 0) prec = min(prec, D);
        break;
    }
  }
  return prec;
}

interval eval(int l, int r) {
  if (check_parentheses(l, r)) {
    return eval(l + 1, r - 1);
  }
  int max_prec = max_precedence(l, r);
  _debug("%d %d %d", l, r, max_prec);
  switch (max_prec) {
    case INT_MAX:
      return get_immd(l, r);
    case PM:
      {
        int cnt = 0, pos = 0;
        for (int i = l; i <= r; i++) {
          switch (expr[i]) {
            case '(' : cnt++; break;
            case ')' : cnt--; break;
            case '+' : case '-' :
              if (cnt == 0) pos = i;
          }
        }
        _debug("pos=%d", pos);
        if (expr[pos] == '+') {
          return eval(l, pos - 1) + eval(pos + 1, r);
        } else {
          return eval(l, pos - 1) - eval(pos + 1, r);
        }
      }
    case MULT:
      {
        int cnt = 0, pos = 0;
        for (int i = l; i <= r; i++) {
          switch (expr[i]) {
            case '(' : cnt++; break;
            case ')' : cnt--; break;
            case '*' : 
              if (cnt == 0) pos = i;
          }
        }
        return eval(l, pos - 1) * eval(pos + 1, r);
      }
    case D:
      {
        int cnt = 0, pos = 0;
        for (int i = l; i <= r; i++) {
          switch (expr[i]) {
            case '(' : cnt++; break;
            case ')' : cnt--; break;
            case 'd' :
              if (cnt == 0) {
                pos = i;
                goto cont;
              }
          }
        }
cont:
        return op_d(eval(l, pos - 1), eval(pos + 1, r));
      }
    default: assert(0);
  }
}

int main() {
  while (cin >> expr) {
    len = strlen(expr);
    auto ans = eval(0, len - 1);
    cout << ans.first << ' ' << ans.second << endl;
  }
  return 0;
}
