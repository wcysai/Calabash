#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
// Unweighted general matching.
// Vertices are numbered from 1 to V.
// G is an adjlist.
// G[x][0] contains the number of neighbours of x.
// The neigbours are then stored in G[x][1] .. G[x][G[x][0]].
// Mate[x] will contain the matching node for x.
// V and E are the number of edges and vertices.
// Slow Version (2x on random graphs) of Gabow's implementation
// of Edmonds' algorithm (O(V^3)).
const int MAXV = 1024;
int G[MAXV][MAXV];
int VLabel[MAXV];
int  Queue[MAXV];
int   Mate[MAXV];
int   Save[MAXV];
int   Used[MAXV];
int    Up, Down;
int           V;

void Init(int n) {
    V = n;
    memset(G, 0, sizeof G);
    memset(VLabel, 0, sizeof VLabel);
    memset(Queue, 0, sizeof Queue);
    memset(Mate, 0, sizeof Mate);
    memset(Save, 0, sizeof Save);
    memset(Used, 0, sizeof Used);
    Up = Down = 0;
}

void ReMatch(int x, int y)
{
  int m = Mate[x]; Mate[x] = y;
  if (Mate[m] == x)
    {
      if (VLabel[x] <= V)
        {
          Mate[m] = VLabel[x];
          ReMatch(VLabel[x], m);
        }
      else
        {
          int a = 1 + (VLabel[x] - V - 1) / V;
          int b = 1 + (VLabel[x] - V - 1) % V;
          ReMatch(a, b); ReMatch(b, a);
        }
    }
}
 
void Traverse(int x)
{
  for (int i = 1; i <= V; i++) Save[i] = Mate[i];
  ReMatch(x, x);
  for (int i = 1; i <= V; i++)
    {
      if (Mate[i] != Save[i]) Used[i]++;
      Mate[i] = Save[i];
    }
}
 
void ReLabel(int x, int y)
{
  for (int i = 1; i <= V; i++) Used[i] = 0;
  Traverse(x); Traverse(y);
  for (int i = 1; i <= V; i++) 
    {
      if (Used[i] == 1 && VLabel[i] < 0)
        {
          VLabel[i] = V + x + (y - 1) * V;
          Queue[Up++] = i;
        }
    }
}

// Call this after constructing G
void Solve()
{
  for (int i = 1; i <= V; i++)
    if (Mate[i] == 0)
      {
        for (int j = 1; j <= V; j++) VLabel[j] = -1;
        VLabel[i] = 0; Down = 1; Up = 1; Queue[Up++] = i;
        while (Down != Up)
          {
            int x = Queue[Down++];
            for (int p = 1; p <= G[x][0]; p++)
              {
                int y = G[x][p];
                if (Mate[y] == 0 && i != y)
                  {
                    Mate[y] = x; ReMatch(x, y);
                    Down = Up; break;
                  }
                if (VLabel[y] >= 0)
                  {
                    ReLabel(x, y);
                    continue;
                  }
                if (VLabel[Mate[y]] < 0)
                  {
                    VLabel[Mate[y]] = x;
                    Queue[Up++] = Mate[y];
                  }
              }
          }
      }
}

// Call this after Solve(). Returns number of edges in matching (half the number of matched vertices)
int Size()
{
  int Count = 0;
  for (int i = 1; i <= V; i++)
    if (Mate[i] > i) Count++;
  return Count;
}

int n, m;
int perm[1024], iperm[1024], mate[1024], mate2[1024];
int main() {
    srand(time(NULL));
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        Init(n);
        vector<pair<int, int>> edges;
        iota(perm + 1, perm + 1 + n, 1);
        rep (i, m) {
            int u, v; scanf("%d%d", &u, &v);
            edges.emplace_back(u, v);
            G[u][++G[u][0]] = v;
            G[v][++G[v][0]] = u;
        }
        Solve();
        memcpy(mate, Mate, sizeof mate);
        if (Size() != n / 2) {
            puts("NO");
            continue;
        }
      //  Rep (i, n) printf("%d ", mate[i]); puts("");
        rep (_, 10) {
            random_shuffle(perm + 1, perm + n + 1);
            Rep (i, n) iperm[perm[i]] = i;
            Init(n);
            for (auto p : edges) {
                int u, v; tie(u, v) = p;
                u = perm[u]; v = perm[v];
                G[u][++G[u][0]] = v;
                G[v][++G[v][0]] = u;
            }
            Rep (i, n) random_shuffle(G[i] + 1, G[i] + 1 + G[i][0]);
            Solve();
            Rep (i, n) mate2[i] = iperm[Mate[perm[i]]];
/*
            printf("run %d: ", _);
            Rep (i, n) printf("%d ", mate2[i]);
            puts("");
  */          
            Rep (i, n) if (mate2[i] != mate[i]) {
                puts("NO");
                goto cont;
            }
        }
        puts("YES");
        Rep (i, n) if (mate[i] > i) printf("%d %d\n", i, mate[i]);
cont:;
    }
    return 0;
}
