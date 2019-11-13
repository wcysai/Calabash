#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int maxn = 105;
const int maxS = 1e6 + 100;
int n,k,S;
ll P;
template<class T>
void Max(T & tar,const T other){
    tar = max(tar,other);
}
struct Match{
    db p[3];
    void read(){
        for (int i=0;i<3;i++){
            cin>>p[i];
        }
        sort(p,p + 3,[](db x,db y){
            return x > y;
        });
    }
    db sin(){
        return p[0];
    }
    db dou(){
        return p[0] + p[1];
    }
    db tri(){
        return 1.;
    }
}match[maxn];
tuple<int,int,int> ticket[maxn];
db dp[maxn][maxn][maxn];
db bag[maxS];
int main(){
    cin>>n>>k>>S>>P;
    for (int i=1;i<=n;i++){
        match[i].read();
    }
    for (int i=1;i<=k;i++){
        int db_cnt;
        int tri_cnt;
        int cost;
        cin>>db_cnt>>tri_cnt>>cost;
        ticket[i] = make_tuple(db_cnt,tri_cnt,cost);
    }
    dp[0][0][0] = P;
    for (int i=1;i<=n;i++){
        for (int db_cnt = 0;db_cnt <= i;db_cnt ++){
            for (int tri_cnt = 0;tri_cnt + db_cnt <= i;tri_cnt ++){
                // single
                Max(dp[i][db_cnt][tri_cnt],dp[i-1][db_cnt][tri_cnt] * match[i].sin());
                // double
                if (db_cnt)Max(dp[i][db_cnt][tri_cnt],dp[i-1][db_cnt-1][tri_cnt] * match[i].dou());
                // triple
                if (tri_cnt)Max(dp[i][db_cnt][tri_cnt],dp[i-1][db_cnt][tri_cnt-1] * match[i].tri());
            }
        }
    }
    for (int i=1;i<=k;i++){
        int tri_cnt,db_cnt,cost;
        tie(db_cnt,tri_cnt,cost) = ticket[i];
        db value = dp[n][db_cnt][tri_cnt];
        for (int j = cost; j <=S;j ++){
            Max(bag[j],bag[j - cost] + value);
        }
    }
    db ans = 0;
    for (int i=0;i<=S;i++){
        Max(ans,bag[i]);
    }
    printf("%.12f\n",ans);
    return 0;
}
