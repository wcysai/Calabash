//
// Created by calabash on 10/19/18.
//
#pragma  GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef long double db;
const int maxn = 25;
int n,m;
db dp[2][maxn][maxn];
db succ[3];
char S[maxn],T[maxn];
pair<int,int> nxt[maxn][maxn][2];
bool used[maxn][maxn];
vector<pair<int,int> > valid(0);
int id[maxn][maxn];
struct KMP{
    int nxt[maxn];
    int len;
    char t[maxn];
    void clear(){
        len =0;
        nxt[0] = nxt[1] =0;
    }
    /* 1-bas */
    /* 注意在ss结尾添加‘\0’ */
    void init(char* ss){
        len = strlen(ss+1);
        memcpy(t,ss,(len+2)*sizeof(char));
        for (int i=2;i<=len;i++){
            nxt[i] = nxt[i-1];
            while (nxt[i]&&ss[i]!=ss[nxt[i]+1]) nxt[i] = nxt[nxt[i]];
            nxt[i]+=(ss[i]==ss[nxt[i]+1]);
        }
    }
    void debug(){
        for (int i=0;i<=len;i++){
            printf("[debug] nxt[%d]=%d\n",i,nxt[i]);
        }
    }
}ks,kt;
int calc_nxt(char * s,int x,int dig,const KMP & kmper){
    int now = x;
    char ch = 'H';
    if (dig){
        ch = 'T';
    }
    while (now && s[now+1] != ch){
        now = kmper.nxt[now];
    }
    if (s[now+1] == ch)now++;
    return now;
}
void init(){
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            for (int k =0;k<2;k++){
                nxt[i][j][k] = make_pair(calc_nxt(S,i,k,ks),calc_nxt(T,j,k,kt));
            }
        }
    }
}
void debug(){
    for (int i=0;i<=n;i++){
        for (int j=0;j<=m;j++){
            for (int k=0;k<2;k++){
                printf("nxt[%d][%d][%d]=(%d,%d)\n",i,j,k,nxt[i][j][k].first,nxt[i][j][k].second);
            }
        }
    }
}
void dfs(int x,int y){
    if (used[x][y])return;
    used[x][y] = 1;
    valid.push_back({x,y});
    id[x][y] = valid.size()-1;
    for (int k=0;k<2;k++){
        pair<int,int> Nxt = nxt[x][y][k];
        dfs(Nxt.first,Nxt.second);
    }
}
int dim;
struct Mat{
    db a[402][402];
    Mat(){
        memset(a,0,sizeof a);
    }
    Mat operator * (const Mat & other){
        Mat ret;
        for (int i=0;i<dim;i++){
            for (int j=0;j<dim;j++){
                for (int k=0;k<dim;k++){
                    ret.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return ret;
    }
    void debug(){
        for (int i=0;i<dim;i++){
            for (int j=0;j<dim;j++){
                printf("%.2Lf ",a[i][j]);
            }
            puts("");
        }
    }
};
int main(){
    scanf("%s",S+1);
    scanf("%s",T+1);
    n = strlen(S+1);
    m = strlen(T+1);
    ks.clear();kt.clear();
    ks.init(S);kt.init(T);
    dp[0][0][0] = 1.0;
    init();
    dfs(0,0);
    //debug();
    static Mat start;
    start.a[0][0] = 1;
    static Mat trans;
    for (int d = 0;d< valid.size();d++){
        int i = valid[d].first;
        int j = valid[d].second;
        if (i == n || j == m){
            trans.a[d][d] = 1;
            continue;
        }
        for (int k=0;k<2;k++){
            pair<int,int> Nxt = nxt[i][j][k];
            int ID = id[Nxt.first][Nxt.second];
            trans.a[d][ID] = 0.5;
        }
    }
    //dim = 400;
    dim = valid.size();
    // cout<<dim<<endl;
    //trans.debug();

    for (int i=0;i<80;i++){
        trans = trans* trans;
    }
    //trans.debug();
    start = start * trans;
    //start.debug();
    for (int d=0;d< valid.size();d++){
        int ii = valid[d].first;
        int jj = valid[d].second;
        int tar = 3;
        if (ii == n && jj == m)tar = 2;
        else if (ii == n)tar = 0;
        else if (jj == m)tar = 1;
        if (tar ==3)continue;
        succ[tar] += start.a[0][d];
    }
//    int step = 1;
//    while (1){
//        step ++;
//        memset(dp[now^1],0,sizeof dp[now^1]);
//        for (int d = 0;d< valid.size();d++){
//            int i = valid[d].first;
//            int j = valid[d].second;
//            for (int k=0;k<2;k++){
//                pair<int,int> Nxt = nxt[i][j][k];
//                int ii = Nxt.first;
//                int jj = Nxt.second;
//                dp[now^1][ii][jj] += dp[now][i][j] /2.0;
//                if (ii == n && jj == m){
//                    succ[2] += dp[now][i][j] / 2.0;
//                }else if (ii == n){
//                    succ[0] += dp[now][i][j] / 2.0;
//                }else if (jj == m){
//                    succ[1] += dp[now][i][j] / 2.0;
//                }
//            }
//        }
//        db tot = 0;
//        for (int i=0;i<3;i++){
//            tot += succ[i];
//        }
//        tot = 1.0 - tot;
//        printf("%.9Lf\n",tot);
//        if (tot < 1e-9)break;
//        now ^=1;
//    }
//    printf("%d\n",step);
    printf("%.10Lf\n%.10Lf\n%.10Lf\n",succ[0],succ[1],succ[2]);
    return 0;
}
