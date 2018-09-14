#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
  __func__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long ll;
typedef unsigned long long ull;

enum {
  A, B, C, D
};

const int  mday[13] = { 0,
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int type = A;
int yy = 2007, mm = 1, dd = 1;
int wday = 1;

bool isleap(int y) {
  if (y % 4 == 0  && y != 2100) return true;
  return false;
}

void adv_year() {
  yy++;
}

void adv_month() {
  mm++;
  if (mm > 12) {
    mm = 1;
    adv_year();
  }
}

int advan() {
  dd++;
  wday ++;
  if (wday > 7) wday = 1;
  int mmday = mday[mm];
  if (mm == 2 && isleap(yy)) mmday++;
  if (dd > mmday) {
    dd = 1;
    adv_month();
  }
  if (mm == 3 && wday == 7 && dd > 7 && dd <= 14) {
    type = C;
    return B; 
  }
  if (mm == 11 && wday == 7 && dd <= 7) {
    type = A;
    return D;
  }
  return type;
}

string genstr() {
  char buf[100];
  sprintf(buf, "%04d-%02d-%02d", yy, mm, dd);
  return string(buf);
}

map<string, int> m;

void prep() {
  m[genstr()] = type;
  do {
    int tp = advan();
    m[genstr()] = tp;

  } while (yy <= 2100);
}


int main() {
  prep();
  string str;
  char tim[20];
  int hh;
  int T;
  cin >> T;
  Rep(t, T) {
    cin >> str >> tim;
    sscanf(tim, "%d", &hh);
    switch (m[str]) {
      case A:
        printf("Case #%d: PST\n", t);
        break;
      case B:
        if (hh < 2) {
          printf("Case #%d: PST\n", t);
        } else if (hh >= 3) {
          printf("Case #%d: PDT\n", t);
        } else {
          printf("Case #%d: Neither\n", t);
        } 
        break;
      case C:
        printf("Case #%d: PDT\n", t);
        break;
      case D:
        if (hh < 1) {
          printf("Case #%d: PDT\n", t);
        } else if (hh >= 2) {
          printf("Case #%d: PST\n", t);
        } else {
          printf("Case #%d: Both\n", t);
        } 
        break;
    }
  }
  return 0;
}
