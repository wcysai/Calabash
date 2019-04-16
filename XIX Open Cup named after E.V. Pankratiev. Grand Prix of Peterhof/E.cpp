#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000000+5;
int x,y;
double dp[maxn][2];
inline void gao(int son,int u){
    double rest_0 = 0;
    double rest_1 = 0;
    rest_0 = dp[son][0] /2 + dp[u][0] / 2;
    rest_1 = dp[son][1] / 2 + dp[u][1] / 2;
    dp[u][0] = rest_0;
    dp[u][1] = rest_1;
}
void work(int u){
    int lson = u * 2;
    int rson = lson + 1;
    if (lson <= x + y)work(lson);
    if (rson <= x+y) work(rson);
    if (u <= x){
        dp[u][0] = 1;
        dp[u][1] = 0;
    }else{
        dp[u][0] = 0;
        dp[u][1] = 1;
    }
    if (rson <= x+y){
        gao(rson,u);   
    }
    if (lson <= x + y){
        gao(lson,u);
    }
}
int main(){
    scanf("%d%d",&x,&y);
    work(1);
    printf("%.9lf\n",dp[1][1]);
    return 0;
}
