#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5+100;
int c[maxn];
vector<int> E[maxn];
vector<int> e[maxn];
int n;
int rd[maxn];
int RD[maxn];
vector<int> top_order;
int R[maxn];
void init_top_order(){
    queue<int> Q;
    for (int i=1;i<=n;i++){
        if (rd[i] == 0){
            Q.push(i);
        }
    }
    while (!Q.empty()){
        int head = Q.front();
        Q.pop();
        top_order.push_back(head);
        for (int v : E[head]){
            rd[v] --;
            if (rd[v] == 0){
                Q.push(v);
            }
        }
    }
}
struct Node{
    int x;
    bool operator <(const Node&other)const{
        return c[other.x] > c[x];
    }
};
int check(){
    for (int i = top_order.size() - 1;i >=0;i--){
        int x = top_order[i];
        for (int v : E[x]){
            c[x] = max(c[x],c[v]);
        }
    }
    for (int i=1;i<=n;i++){
        rd[i] = RD[i];
    }
    priority_queue<Node> pq; 
    for (int i=1;i<=n;i++){
        if (rd[i] == 0){
            pq.push((Node){i});
        }
    }
    int now = 0;
    int ans = 0;
    while (!pq.empty()){
        int head = pq.top().x;
        ans = max(ans,now + c[head]);
        now ++;
        pq.pop();
        for (int v : E[head]){
            rd[v] --;
            if (rd[v] == 0){
                pq.push((Node){v});
            }
        }
    }
    return ans;
}
        

int main(){
    scanf("%d",&n);
    int max_c = -0x3f3f3f3f;
    for (int i=1;i<=n;i++){
        int cnt;
        scanf("%d%d",&c[i],&cnt);
        max_c = max(max_c,c[i]);
        for (int j=0;j<cnt;j++){
            int y;
            scanf("%d",&y);
            E[y].push_back(i);
            rd[i] ++;
            RD[i] ++;
        }
    }
    init_top_order();
    cout<<check()<<endl;
    return 0;
}


