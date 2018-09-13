#include<bits/stdc++.h>
using namespace std;
const int maxn = 3060;
const int M = 47;
int a[maxn][maxn];
int main(){
   //freopen("res.out","w",stdout);
    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            int t =j;
            for (int k=0;k<M;k++){
                a[i*M+j][k*M+t]=1;
                t =(t+i)%M;
            }
        }
    }
    printf("%d\n",2000);
    int cnt =0;
    for (int i=0;i<2000;i++){
        for (int j=0;j<2000;j++){
            printf("%d",a[i][j]);
            cnt+=a[i][j];
        }
        printf("\n");
    }
   // cout<<cnt<<endl;
    return 0;
}
