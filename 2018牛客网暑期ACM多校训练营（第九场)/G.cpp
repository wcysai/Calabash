#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4+10;
int A[maxn][3],B[maxn];
int n;
int dp[maxn][2][2][2];
int pos[maxn][3][2];
inline void read(int & x){
    x = 0;
    char ch = getchar();
    while (ch<'0'|| ch>'9')ch = getchar();
    while (ch>='0'&&ch<='9')x = x*10 + ch-'0',ch = getchar();
}
inline void Max(int & A,int B){
    A = max(A,B);
}
int main(){
    //scanf("%d",&n);
    read(n);
    for (int i=0;i<3;i++){
        for (int j=1;j<=n;j++){
            //scanf("%d",&A[j][i]);
            read(A[j][i]);
            if (pos[A[j][i]][i][0]){
                pos[A[j][i]][i][1] = j;
            }else{
                pos[A[j][i]][i][0] = j;
            }
        }
    }
    for (int i=1;i<=n;i++){
//        scanf("%d",B+i);
        read(B[i]);
    }
    int ans =0;
    for (int i=1;i<=n;i++){
        int now = B[i];
        for (int a=0;a<2;a++) {
            if (!pos[now][0][a])break;
            for (int b = 0; b < 2; b++){
                if (!pos[now][1][b] )break;
                for (int c = 0; c < 2; c++) {
                    if (!pos[now][2][c])break;
                    dp[i][a][b][c] = 1;
                    for (int j = max(0,i-300); j < i; j++) {
                        int pre = B[j];
                        for (int aa = 0; aa < 2; aa++) {
                            if (!pos[pre][0][aa] || pos[pre][0][aa] >= pos[now][0][a])break;
                            for (int bb = 0; bb < 2; bb++) {
                                if ( !pos[pre][1][bb]  || pos[pre][1][bb] >= pos[now][1][b])break;
                                for (int cc = 0; cc < 2; cc++) {
                                    if (!pos[pre][2][cc] || pos[pre][2][cc] >= pos[now][2][c])break;
                                    Max(dp[i][a][b][c], dp[j][aa][bb][cc] + 1);
                                }
                            }
                        }
                    }
                    Max(ans, dp[i][a][b][c]);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
