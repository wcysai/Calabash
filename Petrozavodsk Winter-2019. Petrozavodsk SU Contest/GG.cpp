#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double dbl;
typedef pair<int, int> pii;
#define mp make_pair
#define pb push_back

const int INF = (int) (1e9 + 7);

string alph;
int cnt[333];
int pos[333];
string C[] = { "CcEFfGHhIiJjKkLlMmNnrSsTtUuVvWwXxYyZz", "AabDdeOoPpQqR", "Bg" };
map<int, char> nr[52];

struct item {
  char f, s;
  int v1, v2;
  int cost;
  int add;

  item () {}

  item (char f, char s, int v1, int v2, int cost, int add) : f (f), s (s), v1 (v1), v2 (v2), cost (cost), add (add) {}

  bool operator < (const item &it) const {
    if (abs (add) != abs (it.add)) return abs (add) > abs (it.add);
    if (cost != it.cost) return cost < it.cost;
    return mp (min (f, s), max (f, s)) < mp (min (it.f, it.s), max (it.f, it.s));
  }

  friend ostream &operator << (ostream &cout, const item &it) {
    cout << it.f << ' ' << it.s << ' ' << it.v1 << ' ' << it.v2 << ' ' << it.add << ' ' << it.cost;
    return cout;
  }
};

inline int getDst (int a, int b) {
  int res = pos[b] - pos[a];
  if (res < 0) res += alph.size ();
  return res;
}

inline void opt (map<int, int> &t, int k, int v) {
  auto it = t.find (k);
  if (it == t.end ()) t[k] = v;
  else it -> second = min (it -> second, v);
}

void pre () {
  for (int i = 0; i < 26; i++) {
    alph += 'A' + i;
    alph += 'a' + i;
  }

  for (int i = 0; i < 3; i++) {
    for (auto c : C[i]) {
      cnt[(int)c] = i;
    }
  }
  for (int i = 0; i < (int)alph.size (); i++) {
    pos[(int)alph[i]] = i;
  }

  for (int i = 0; i < (int) alph.size (); i++) {
    int C = cnt[(int) alph[i]];
    map<int, int> tmp;
    for (auto c : alph) {
      int df = cnt[(int) c] - C;
      opt (tmp, df, getDst (alph[i], c));       
    }
    for (auto it : tmp) {
      nr[i][it.first] = alph[(i + it.second) % alph.size ()];
    }
  }
}

int n;
string s;
ll k;

void change (int id, int shift) {
  int v = s[id];
  v = pos[v];
  v += shift;
  v %= alph.size ();
  s[id] = alph[v];
}

void load () {
  cin >> n >> k;
  cin >> s;
}


vector<int> CC;
set<item> Q;
int ans;

void build () {
  for (auto c1 : alph) {
    for (auto c2 : alph) {
      for (auto it1 : nr[pos[(int) c1]]) {
        for (auto it2 : nr[pos[(int) c2]]) {          
          char c3 = it1.second;
          char c4 = it2.second;
          int cnt1 = cnt[(int) c1] + cnt[(int) c2];
          int cnt2 = cnt[(int) c3] + cnt[(int) c4];
          int step = cnt2 - cnt1;
          if (abs (step) > 2 || !step) continue;
          int cost = getDst (c1, c3) + getDst (c2, c4);
          item tmp (c1, c2, getDst (c1, c3), getDst (c2, c4), cost, step);
          Q.insert (tmp);
        }
      }
    }
  }
  CC.resize (alph.size ());
  for (auto c : s) {
    CC[pos[(int) c]]++;
  }
}

vector<int> PS[52];

vector<int> change (int id, int shift, int cnt) {
  vector<int> res;
  while (cnt --> 0) {
    int I = PS[id].back ();
    PS[id].pop_back ();
    change (I, shift);
    res.pb (I);
  }
  return res;
}

void push (int id, vector<int> &ids) {
  for (auto it : ids) PS[id].pb (it);
}

void recoveryInc (int diff) {
  for (auto it : Q) {
    if (it.add < 0) continue;
    if (it.add > diff) continue;
    
    int cnt = diff / it.add;
    int sh = it.f == it.s && min (it.v1, it.v2) > 0;
                              
    if (it.v1) cnt = min (cnt, CC[pos[(int) it.f]] >> sh);
    if (it.v2) cnt = min (cnt, CC[pos[(int) it.s]] >> sh);
    if (!cnt) continue;
    
    CC[pos[(int) it.f]] -= cnt;
    CC[pos[(int) it.s]] -= cnt;
    
    int nf = (pos[(int) it.f] + it.v1) % alph.size ();
    int ns = (pos[(int) it.s] + it.v2) % alph.size ();
    
    CC[nf] += cnt;
    CC[ns] += cnt;
    
    vector<int> F, S;
                                               
    if (it.v1) {             
      F = change (pos[(int) it.f], it.v1, cnt);   
    }
    if (it.v2) {
      S = change (pos[(int) it.s], it.v2, cnt);   
    }                                                  
    push ((pos[(int) it.f] + it.v1) % alph.size (), F);
    push ((pos[(int) it.s] + it.v2) % alph.size (), S); 

    diff -= cnt * it.add;
  }
}

void recoveryDec (int diff) {
  for (auto it : Q) {
    if (it.add > 0) continue;
    if (it.add < diff) continue;
    
    int cnt = diff / it.add;
    int sh = it.f == it.s && min (it.v1, it.v2) > 0;                          
    if (it.v1) cnt = min (cnt, CC[pos[(int) it.f]] >> sh);
    if (it.v2) cnt = min (cnt, CC[pos[(int) it.s]] >> sh);
    if (!cnt) continue;
    
    CC[pos[(int) it.f]] -= cnt;
    CC[pos[(int) it.s]] -= cnt;
    
    int nf = (pos[(int) it.f] + it.v1) % alph.size ();
    int ns = (pos[(int) it.s] + it.v2) % alph.size ();
    
    CC[nf] += cnt;
    CC[ns] += cnt;
    
    vector<int> F, S;
                                               
    if (it.v1) {             
      F = change (pos[(int) it.f], it.v1, cnt);   
    }
    if (it.v2) {
      S = change (pos[(int) it.s], it.v2, cnt);   
    }                                                  
    push ((pos[(int) it.f] + it.v1) % alph.size (), F);
    push ((pos[(int) it.s] + it.v2) % alph.size (), S); 

    diff -= cnt * it.add;
  }
  
}

void recovery (int diff) {
  for (int i = 0; i < (int) s.size (); i++) {
    char c = s[i];
    PS[pos[(int) c]].pb (i); 
  } 
  if (diff < 0) recoveryDec (diff);
  else recoveryInc (diff);
}

int getAnsInc (int diff) {
  //clog << "Inc" << endl;
  //clog << diff << endl;
  auto tmpC = CC;
  int res = 0;
  for (auto it : Q) {
    if (it.add < 0) continue;
    if (it.add > diff) continue;
    int cnt = diff / it.add; 
    int sh = it.f == it.s && min (it.v1, it.v2) > 0;                         
    if (it.v1) cnt = min (cnt, tmpC[pos[(int) it.f]] >> sh);
    if (it.v2) cnt = min (cnt, tmpC[pos[(int) it.s]] >> sh);
    if (!cnt) continue;
    //clog << it << ' ' << cnt << endl;
    tmpC[pos[(int) it.f]] -= cnt;
    tmpC[pos[(int) it.s]] -= cnt;
    int nf = (pos[(int) it.f] + it.v1) % alph.size ();
    int ns = (pos[(int) it.s] + it.v2) % alph.size ();
    //clog << alph[nf] << ' ' << alph[ns] << endl;
    tmpC[nf] += cnt;
    tmpC[ns] += cnt;
    res += cnt * it.cost;
    diff -= cnt * it.add;
  }
  return res;
}

int getAnsDec (int diff) {
  auto tmpC = CC;
  int res = 0;
  for (auto it : Q) {
    if (it.add > 0) continue;
    if (it.add < diff) continue;
    int cnt = diff / it.add; 
    int sh = it.f == it.s && min (it.v1, it.v2) > 0;                         
    if (it.v1) cnt = min (cnt, tmpC[pos[(int) it.f]] >> sh);
    if (it.v2) cnt = min (cnt, tmpC[pos[(int) it.s]] >> sh);
    if (!cnt) continue;
    tmpC[pos[(int) it.f]] -= cnt;
    tmpC[pos[(int) it.s]] -= cnt;
    int nf = (pos[(int) it.f] + it.v1) % alph.size ();
    int ns = (pos[(int) it.s] + it.v2) % alph.size ();
    tmpC[nf] += cnt;
    tmpC[ns] += cnt;
    res += cnt * it.cost;
    diff -= cnt * it.add;
  }
  return res;
}

void getAnsOdd (int diff) {
  int best = 1e9;
  char f = -1, s = -1;
  for (auto c : alph) {
    if (CC[pos[(int) c]] == 0) continue;
    int C = cnt[(int) c];
    int bst = 1e9;
    char to = -1;
    for (auto c2 : alph) {
      int df = abs (C - cnt[(int) c2]);
      if (!(df & 1)) continue;
      if (bst > getDst (c, c2)) {
        bst = getDst (c, c2);
        to = c2;
      }
    }
    int ans = getDst (c, to);
    CC[pos[(int) c]]--;
    CC[pos[(int) to]]++;
    int CH = cnt[(int) to] - cnt[(int) c]; 
    //clog << "change one : " << c << ' ' << to << endl;
    if (diff - CH < 0) ans += getAnsDec (diff - CH);  
    else ans += getAnsInc (diff - CH);
    CC[pos[(int) c]]++;
    CC[pos[(int) to]]--;
    if (ans < best) {
      best = ans;
      f = c;
      s = to;
    }
  }
  //clog << f << ' ' << s << endl;
  CC[pos[(int) f]]--;
  CC[pos[(int) s]]++;
  int CH = cnt[(int) s] - cnt[(int) f];
  diff -= CH; 

  for (int i = 0; i < (int) ::s.size (); i++) {
    if (::s[i] == f) {
      change (i, getDst (f, s));
      break;
    }
  }
  recovery (diff);
  ans = best;
}

void getAns (int diff) {
  //clog << diff << endl;
  if (diff == 0) return;
  if (abs (diff) & 1) {
    getAnsOdd (diff);
    return;
  }
  if (diff < 0) ans = getAnsDec (diff);
  else ans = getAnsInc (diff);
  recovery (diff);
}

void solve () {
  if (k < 0 || k > 2 * n) {
    cout << -1 << endl;
    return;
  } 

  int cur = 0;
  for (auto c : s) {
    cur += cnt[(int) c];
  }

  build ();

  int diff = k - cur;

  getAns (diff);

  cout << ans << endl;
}

int main () {
  ios_base::sync_with_stdio (false);
  cin.tie (NULL);

  pre ();
  load ();
  solve ();

  return 0;
}
