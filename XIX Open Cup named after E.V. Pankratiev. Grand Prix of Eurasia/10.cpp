#include<bits/stdc++.h>
#define MAXN 105
#define INF1 5000
#define INF2 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int W,H,M,R;
char mp[MAXN][MAXN][2];
int type[MAXN][MAXN]; //0:plain 1:hill 2:mountain
int feat[MAXN][MAXN]; //0:grass 1:forest 2:marsh
int pre[10005]; //path record
struct edge{int to,cost;};
vector<edge> G[10005];
vector<int> ans;
P d[10005];
int st,ed;
struct river
{
    int x1,y1,x2,y2;
    bool operator <(const river &rhs)const {return tie(x1,y1,x2,y2)<tie(rhs.x1,rhs.y1,rhs.x2,rhs.y2);}
};
set<river> s;
void add_edge(int u,int v,int cost)
{
    G[u].push_back((edge){v,cost});
}
void try_add(int x1,int y1,int x2,int y2)
{
    if(x2<0||x2>=H||y2<0||y2>=W) return;
    int c=1;
    if(type[x2][y2]==2) c=INF2;
    else
    {
        if(s.count((river){x1,y1,x2,y2})||s.count((river){x2,y2,x1,y1})) c=INF1;
        else
            {
            if (type[x2][y2] == 1 && type[x1][y1] == 0) c++;
            if (feat[x2][y2] == 1 || feat[x2][y2] == 2) c++;
        }
    }
    //printf("added %d %d %d %d %d\n",x1,y1,x2,y2,c);
    int u=x1*W+y1,v=x2*W+y2;
    add_edge(u,v,c);
}
void dijkstra(int s)
{
    for(int i=0;i<H*W;i++) d[i]=P(INF2,INF2);
    priority_queue< pair<P,int>, vector<pair<P,int> >, greater< pair<P,int> > > que;
    while(que.size()) que.pop();
    d[s]=P(0,0);
    que.push(make_pair(P(0,0),s) );
    while(que.size())
    {
        auto p=que.top();que.pop();
        if(p.F>d[p.S]) continue;
        for(auto &e: G[p.S])
        {
            P nxt;
            if(e.cost==INF2) continue;
            else if(e.cost==INF1) nxt=P(p.F.F+1,0);
            else if(e.cost+p.F.S>=M) nxt=P(p.F.F+1,0);
            else nxt=P(p.F.F,p.F.S+e.cost);
            if(nxt<d[e.to])
            {
                d[e.to]=nxt;
                pre[e.to]=p.S;
                que.push(make_pair(nxt,e.to));
            }
        }
    }
}
int main() {
    scanf("%d%d", &W, &H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            scanf("%s", mp[i][j]);
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (mp[i][j][0] == 'p') type[i][j] = 0;
            else if (mp[i][j][0] == 'h') type[i][j] = 1;
            else type[i][j] = 2;
            if (mp[i][j][1] == 'g') feat[i][j] = 0;
            else if (mp[i][j][1] == 'f') feat[i][j] = 1;
            else feat[i][j] = 2;
        }
    }
    scanf("%d", &R);
    for (int i = 0; i < R; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        swap(x1, y1);
        swap(x2, y2);
        s.insert((river) {x1, y1, x2, y2});
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            try_add(i, j, i - 1, j - 1);
            try_add(i, j, i + 1, j + 1);
            try_add(i, j, i + 1, j);
            try_add(i, j, i - 1, j);
            try_add(i, j, i, j + 1);
            try_add(i, j, i, j - 1);
        }
    }
    scanf("%d", &M);
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    swap(x1, y1);
    swap(x2, y2);
    st = x1 * W + y1;
    ed = x2 * W + y2;
    dijkstra(st);
    if(d[ed].F==INF2) {puts("They shall not pass"); return 0;}
    puts("Come this way");
    if(d[ed].S==0) printf("%d\n",d[ed].F); else printf("%d\n",d[ed].F+1);
    int cur=ed;
    ans.push_back(cur);
    while(cur!=st)
    {
        cur=pre[cur];
        ans.push_back(cur);
    }
    printf("%d\n",(int)ans.size());
    for(int i=(int)ans.size()-1;i>=0;i--)
    {
        int x=ans[i]/W,y=ans[i]%W;
        printf("%d %d\n",y,x);
    }
    return 0;
}
/*
 5 2
 pg hg hf pg pg
 pg hg hm pg pg
 3
 2 0 3 0
 2 0 3 1
 2 1 3 1
 4
 0 1 4 0
 */
