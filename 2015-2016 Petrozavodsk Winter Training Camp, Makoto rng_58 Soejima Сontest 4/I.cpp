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

#define LEFT    1
#define RIGHT   2
#define UP      3
#define DOWN    4

int n;
int64_t t;

map<int, int> xobj[100005], yobj[100005];
vector<int> xs, ys;

struct event {
  LL T;
  int actor, target;
  
  event(LL T, int actor, int target) : T(T), actor(actor), target(target) {}

  void process();

  bool operator < (const struct event& rhs) const {
    return T > rhs.T;
  }
};

struct robot {
  int id;
  LL x, y, start_time;
  int xid, yid, dir;
  bool run;

  void add_event();
  
  bool start(LL T) {
    if (run) return false;
    _debug("robot %d started at time %lld", id, T);
    run = true;
    start_time = T;
    xobj[xid].erase(yid);
    yobj[yid].erase(xid);
    add_event();
    return true;
  }
   
  pair<LL, LL> get_position(LL T) {
    if (!run) return {x, y};
    T -= start_time;
    switch (dir) {
      case LEFT:    return {x - T, y};
      case RIGHT:   return {x + T, y};
      case UP:      return {x, y + T};
      case DOWN:    return {x, y - T};
    }
    assert(0);
  }
} robots[100005];

priority_queue<event> q;

void event::process() {
  robots[target].start(T);
  if (robots[target].dir != robots[actor].dir)
    robots[actor].add_event();
}

void robot::add_event() {
  switch (dir) {
    case LEFT: 
      {
        auto it = yobj[yid].lower_bound(xid);
        if (it == yobj[yid].begin()) return;
        it--;
        robot& r = robots[it->second];
        q.emplace(start_time + x - r.x, id, r.id);
      } break;
    case RIGHT:
      {
        auto it = yobj[yid].lower_bound(xid);
        if (it == yobj[yid].end()) return;
        robot& r = robots[it->second];
        q.emplace(start_time + r.x - x, id, r.id);
      } break;
    case UP:
      {
        auto it = xobj[xid].lower_bound(yid);
        if (it == xobj[xid].end()) return;
        robot& r = robots[it->second];
        q.emplace(start_time + r.y - y, id, r.id);
      } break;
    case DOWN:
      {
        auto it = xobj[xid].lower_bound(yid);
        if (it == xobj[xid].begin()) return;
        it--;
        robot& r = robots[it->second];
        q.emplace(start_time + y - r.y, id, r.id);
      } break;
  }
}

void play() {
  robots[0].start(0); 
  while (q.size()) {
    event e = q.top();
    if (e.T > t) return;
    q.pop();
    e.process();
  }
}

int main() {
  scanf("%d%" SCNd64, &n, &t);
  rep (i, n) {
    int x, y;
    char ch;
    scanf("%d %d %c", &x, &y, &ch);
    robots[i].id = i;
    robots[i].x = x;
    robots[i].y = y;
    xs.push_back(x);
    ys.push_back(y);
    if (ch == 'U')      robots[i].dir = UP;
    else if (ch == 'D') robots[i].dir = DOWN;
    else if (ch == 'L') robots[i].dir = LEFT;
    else if (ch == 'R') robots[i].dir = RIGHT;
  }
  sort(range(xs)); sort(range(ys));
  xs.resize(unique(range(xs)) - xs.begin());
  ys.resize(unique(range(ys)) - ys.begin());
  rep (i, n) {
    robots[i].xid = lower_bound(range(xs), robots[i].x) - xs.begin();
    robots[i].yid = lower_bound(range(ys), robots[i].y) - ys.begin();
  }
  rep (i, n) {
    xobj[robots[i].xid][robots[i].yid] = i;
    yobj[robots[i].yid][robots[i].xid] = i;
  }
  play();
  rep (i, n) {
    auto pos = robots[i].get_position(t);
    printf("%" PRId64 " %" PRId64 "\n", (int64_t)pos.first, (int64_t)pos.second);
  }
  return 0;
}
