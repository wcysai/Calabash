#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
typedef long long ll;
const int inf = 0x3f3f3f3f3f3f3f3fll;
ll dis[maxn][maxn];
vector<pair<int,int> > E[maxn];
int n,m,S,T,K;
bool used[maxn][maxn];
struct Node{
    int x;
    int dep;
    ll dis;
    Node(int x_,int dep_,ll dis_){
        x = x_;
        dep = dep_;
        dis = dis_;
    }
    bool operator < (const Node & other)const{
        return other.dis < dis;
    }
};
ll bfs(){
    dis[S][0] = 0;
    priority_queue<Node> pq;
    for (int i=1;i<=n;i++){
        for (int j=0;j<=K;j++){
            pq.push(Node(i,j,dis[i][j]));
        }
    }
    while (!pq.empty()){
        Node nd = pq.top();
        pq.pop();
        int x = nd.x;
        int dep = nd.dep;
        ll d = nd.dis;
        if (used[x][dep])continue;
        used[x][dep] = 1;
        for (auto pr : E[x]){
            //not zero
            int v;
            int len;
            tie(v,len) = pr;
            if (dis[v][dep] > d + len){
                dis[v][dep] = d + len;
                pq.push(Node(v,dep,dis[v][dep]));
            }
            //zero
            if (dep < K && dis[v][dep+1] > d){
                dis[v][dep+1] = d;
                pq.push(Node(v,dep+1,dis[v][dep+1]));
            }
        }
    }
    ll ans = inf;
    for (int i=0;i<=K;i++){
        ans = min(ans,dis[T][i]);
    }
    return ans;
}
int main(){
    cin>>n>>m>>S>>T>>K;
    while (m--){
        int a,b,l;
        cin>>a>>b>>l;
        E[a].push_back(make_pair(b,l));
        E[b].push_back(make_pair(a,l));
    }
    for (int i=1;i<=n;i++){
        for (int j=0;j<=K;j++){
            dis[i][j] = inf;
        }
    }
    cout<<bfs()<<endl;
    return 0;
}
