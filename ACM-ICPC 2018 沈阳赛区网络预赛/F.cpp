#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<bitset>
#include<stack>
#include<cassert>
#define F first
#define S second
#define mp make_pair
#define pii pair<int,int>
#define pb push_back
#define mem(x,y) memset(x,y,sizeof x)
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long ll;
typedef double db;
const int INF=2e9;
const db eps=1e-12;
template<typename T>
inline void read(T &x)
{
    x=0; int f=1; char ch=getchar();
    while( (ch<'0' || ch>'9') && ch!='-') ch=getchar(); if(ch=='-') {f=-1; ch=getchar();}
    while(ch>='0' && ch <='9') x=x*10+ch-'0',ch=getchar();
    x*=f;
}
//==========================head template==========================
const int N=5000,M=10000;
int n,m,S,T,edge_cnt;
namespace BOUND_FLOW {
    const int ALL=N,EDGE=M*3*2;
    int SS,TT;
    int head[ALL],nxt[EDGE],to[EDGE],cap[EDGE],lst=1;
    inline void adde(int x,int y,int c) {
        nxt[++lst]=head[x]; to[lst]=y; cap[lst]=c; head[x]=lst;
    }
    inline void con(int x,int y,int c) {
        adde(x,y,c); adde(y,x,0);
    }
    inline void Del(int id) {
        cap[id]=cap[id^1]=0;
    }
    int stp[ALL];
    inline bool bfs(int S,int T) {
        queue<int> que; mem(stp,63);
        que.push(S); stp[S]=0;
        while(!que.empty()) {
            int u=que.front(); que.pop();
            for(int i=head[u];i;i=nxt[i]) {
                int v=to[i];
                if(cap[i] && stp[v]>stp[u]+1) {
                    stp[v]=stp[u]+1;
                    que.push(v);
                }
            }
        }
        // printf("%d ",stp[T]);
        return stp[T]!=stp[0];
    }
    int cur[ALL];
    inline int dfs(int u,int f,int T) {
        if(!f || u==T) return f;
        for(int &i=cur[u];i;i=nxt[i]) {
            int v=to[i];
            if(stp[v]==stp[u]+1 && cap[i]) {
                int flow=dfs(v,min(f,cap[i]),T);
                if(flow) {
                    cap[i]-=flow; cap[i^1]+=flow;
                    return flow;
                }
            }
        }
        return 0;
    }
    inline int Dinic(int S,int T) {
        int Flow=0,add=0;
        while(bfs(S,T)) {
            // if(Flow) printf("Flow=%d\n",Flow);
            memcpy(cur,head,sizeof(head));
            do {add=dfs(S,INF,T); Flow+=add;} while(add);
        }
        return Flow;
    }
    int ned=0;
    inline void addEdge(int u,int v,int l,int r){
        con(SS,v,l); con(u,TT,l); con(u,v,r-l); ned+=l;
    }
    inline void Construct() {
        int l,r;
        read(l);read(r);
        SS=n+m+3; TT=n+m+4;
        con(T,S,INF);
        for(int i=1;i<=edge_cnt;i++) {
            int u,v; read(u); read(v);
            v += n;
            addEdge(u,v,0,1);
        }
        for (int i=1;i<=n;i++){
            addEdge(S,i,l,r);
        }
        for (int i=1;i<=m;i++){
            addEdge(n+i,T,l,r);
        }
    }
    inline void clear(){
        memset(head,0,sizeof head);
        memset(nxt,0,sizeof nxt);
        memset(to,0,sizeof to);
        memset(cap,0,sizeof cap);
        memset(cur,0,sizeof cur);
        memset(stp,0,sizeof stp);
        lst =1;
        ned = 0;
    }
    bool main() {
        clear();
        Construct();
        return Dinic(SS,TT)==ned;
    }
    inline void Modify() {
        Del(2);
    }
    int Main() {
        int ret=cap[2^1]; Modify();
        return ret+Dinic(S,T);
    }
}
signed main() {

    int Case =1;
    while (scanf("%d%d%d",&n,&m,&edge_cnt)!=EOF){
        S = n+m +1;
        T = n+ m +2;
        printf("Case %d: ",Case ++);
        int type=BOUND_FLOW::main();
        if(!type) puts("No");
        else {
            puts("Yes");
        }
    }

    return 0;
}
