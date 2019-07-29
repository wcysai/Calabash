/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Total Time = O(mlogm)
 */

#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>

using namespace std;

#define next dfosakfoa
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define mp make_pair

typedef pair <int, int> pii;

template <class T> inline void relaxMin( T &a, T b ) { a = min(a, b); }

/* Main part */

const int maxN = (int)1e5;
const int maxM = (int)1e5;

struct query
{
  int a, b, L, R;

  query() { }
  query( int _a, int _b, int _L, int _R ) : a(_a), b(_b), L(_L), R(_R) { }
};

int n, m, qn, res[maxM + 1];
query q[maxM];

const int maxMem = (int)1e7;
const int maxE = (int)1e6;

int mpos = 0, en, next[maxE], to[maxE], w[maxE];
char mem[maxMem];

template <class T> T *getMem( int n )
{
  char *r = mem + mpos;
  mpos += n * sizeof(T);
  assert(mpos <= maxMem);
  return (T *)r;
}

void addE( int a, int b, int x, int *head )
{
  assert(en + 2 <= maxE);
  next[en] = head[a], to[en] = b, w[en] = x, head[a] = en++;
  next[en] = head[b], to[en] = a, w[en] = x, head[b] = en++;
}

int curT, cc, used[maxN], T[maxN], minT[maxN];
int sp, ss[maxN];
int vnX, color[maxN];
int enX, ea[maxM], eb[maxM], ew[maxM];

// find components of edge-2-connectivity and bridges
void getComp( int old_sp )
{
  while (sp > old_sp)
    color[ss[--sp]] = vnX;
  vnX++;
}

void dfs( int v, int pr, int *head )
{
  int cnt = 0;
  ss[sp++] = v;
  used[v] = cc;
  minT[v] = T[v] = curT++;
  for (int e = head[v]; e != -1; e = next[e])
  {
    int x = to[e];
    if (x != pr || ++cnt > 1)
    {
      if (used[x] != cc)
      {
        int old_sp = sp;
        dfs(x, v, head);
        if (minT[x] > T[v])
          getComp(old_sp), ew[enX] = w[e], ea[enX] = v, eb[enX++] = x;
      }
      relaxMin(minT[v], minT[x]);
    }
  }
}

// determine important vertices in tree
int paint( int v, int *head ) 
{
  int num = 0;
  used[v] = cc;
  for (int e = head[v]; e != -1; e = next[e])
    if (used[to[e]] != cc)
      num += paint(to[e], head);
  color[v] |= (num >= 2);
  return color[v] || num;
}

// consolidate edges
int findEdges( int v, int start, int curLen, int *head )
{
  int ret = 0;
  used[v] = cc;
  if (color[v] && curLen > 0)
  {
    ea[enX] = v, eb[enX] = start, ew[enX++] = curLen;
    start = v, curLen = 0, ret = 1;
  }
  for (int e = head[v]; e != -1; e = next[e])
    if (used[to[e]] != cc && findEdges(to[e], start, curLen + w[e], head))
      w[e] = 0, w[e ^ 1] = 0, ret = 1;
  return ret;
}

// main procedure
void newGraph( int qn, query *q, int &vn, int *head, int &old_en )
{
  fill(head, head + vn, -1), en = old_en, vn = vnX;
  forn(i, enX)
    addE(color[ea[i]], color[eb[i]], ew[i], head);
  forn(i, qn)
    q[i].a = color[q[i].a], q[i].b = color[q[i].b];
}

void Solve( int L, int R, int qn2, query *q2, int vn2, int *head2, int have )
{
  query *q = getMem<query>(qn2);
  int old_en = en, old_mpos = mpos;
  int qn = 0, vn = vn2;
  int *head = getMem<int>(vn);

  /* Process all already obvious queries */
  memcpy(head, head2, sizeof(head2[0]) * vn);
  forn(i, qn2)
    if (q2[i].L < L && q2[i].R >= R)
      addE(q2[i].a, q2[i].b, 1, head);
    else if (q2[i].R >= L && q2[i].L < R)
      q[qn++] = q2[i];

  /* Consolidate components of edge-2-connectivity */
  cc++, curT = 0;
  vnX = enX = sp = 0;
  forn(i, vn)
    if (used[i] != cc)
      dfs(i, -1, head), getComp(0);
  newGraph(qn, q, vn, head, old_en);

  /* Determine all important edges */
  forn(i, vn)
    color[i] = 0;
  forn(i, qn)
    color[q[i].a] = color[q[i].b] = 1;
  cc++;
  forn(i, vn)
    if (used[i] != cc)
      paint(i, head);

  /* Reduce the graph */
  enX = 0, cc++;
  forn(i, vn)
    if (used[i] != cc && color[i])
      findEdges(i, i, 0, head);
  forn(i, vn)
    for (int e = head[i]; e != -1; e = next[e])
      if (w[e] > 0)
        have += w[e];
  vnX = 0;
  forn(i, vn)
    if (color[i])
      color[i] = vnX++;
  newGraph(qn, q, vn, head, old_en);
      
  /* Recursion continues... */
  mpos -= sizeof(int) * (vn2 - vn);
  if (L == R)
    res[L] = have / 2;
  else
  {
    int M = (L + R) / 2;
    Solve(L, M, qn, q, vn, head, have);
    Solve(M + 1, R, qn, q, vn, head, have);
  }
  en = old_en, mpos = old_mpos;
}

void Read()
{
  #define NAME "bridges3"
  //assert(freopen(NAME ".in", "r", stdin));
  //assert(freopen(NAME ".out", "w", stdout));

  assert(scanf("%d%d", &n, &m) == 2);
  assert(1 <= n && n <= maxN);
  assert(0 <= m && m <= maxM);

  map <pii, int> L;
  forn(i, m)
  {
    char com[9];
    int a, b;
    assert(scanf("%s", com) == 1);
    assert(scanf("%d%d", &a, &b) == 2);
    assert(1 <= a && a <= n && 1 <= b && b <= n && a != b);
    a--, b--;
    if (a > b)
      swap(a, b);

    pii p = mp(a, b);
    assert(!strcmp(com, "ADD") == !L.count(p));
    if (L.count(p))
    {
      q[qn++] = query(a, b, L[p], i);
      L.erase(p);
    }
    else
      L[p] = i;
  }
  forit(it, L)
    q[qn++] = query(it->first.first, it->first.second, it->second, m);
}

void TimeStamp( const char *s )
{
  fprintf(stderr, "[%05.2f] %s\n", (double)clock() / CLOCKS_PER_SEC, s);
}

int main()
{
  Read();
  
  TimeStamp("Data is read");

  int *head = getMem<int>(n);
  fill(head, head + n, -1);

  TimeStamp("Memory is allocated");

  Solve(0, m, qn, q, n, head, 0);

  TimeStamp("Problem is solved");

  forn(i, m)
    printf("%d\n", res[i + 1]);

  TimeStamp("Result is outputed");
  return 0;
}
  
