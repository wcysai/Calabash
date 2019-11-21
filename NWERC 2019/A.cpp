#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int maxn = 6e5 + 100;
const int N = 6e5 + 10;
struct Query{
    int tar,sig,limit;
};
ll SUM[maxn];
ll CNT[maxn];
vector<Query> Q[maxn];
ll ans[maxn];
int val[maxn];
int timestamp[maxn];
int n,w;
void add_query(int tar,int sig,int bound,int limit){
    if (bound <=0)return;
    Q[bound].push_back((Query){tar,sig,limit});
}
void add(int x,int i){
    val[x] ++;
    CNT[val[x]] ++;
    SUM[val[x]] += i-1;
}
vector<int> ops[maxn];
int main(){
    cin>>n>>w;
    for (int i=1;i<=n;i++){
        val[i] = 1;
        timestamp[i] = 0;
    }
    for (int i=1;i<=w;i++){
        int k;
        cin>>k;
        while (k--){
            int x;
            cin>>x;
            ops[i].push_back(x);
            int R = i-1;
            int L = timestamp[x];
            int Limit = val[x];
            add_query(x,1,R,Limit);
            add_query(x,-1,L-1,Limit);
            val[x] ++;
            timestamp[x] = i;
        }
    }
    for (int i=1;i<=n;i++){
        int L = timestamp[i];
        int R = w;
        int Limit = val[i];
        add_query(i,1,R,Limit);
        add_query(i,-1,L-1,Limit);
        val[i] = 1;
    }
    for (int i=1;i<=w;i++){
        for (int x : ops[i]){
            add(x,i);
        }
        for (auto q : Q[i]){
            int tar = q.tar,sig = q.sig,limit = q.limit;
            ans[tar] += 1ll * sig * (1ll * CNT[limit+1] * i - SUM[limit+1]);
        }
    }
    for (int i=1;i<=n;i++){
        db e = 1.0 + 1.0 * ans[i] / w;
        printf("%.9f\n",e);
    }
    return 0;
}
