#include<bits/stdc++.h>
using namespace std;
const int maxn = 2005;
char a[maxn][maxn];
int lr[maxn];
int lc[maxn];
int n,m;
int T;
void debug(){
    for (int i=1;i<=n;i++){
        printf("lr[%d]=%d\n",i,lr[i]);
    }
    for (int i=1;i<=m;i++){
        printf("lc[%d]=%d\n",i,lc[i]);
    }
}
void solve(){
    scanf("%d%d",&n,&m);
    assert(n%2==0&&m%2==0);
    for (int i=1;i<=n;i++){
        scanf("%s",&a[i][1]);
    }
    for (int i=1;i<=n;i++){
        if (a[i][1]!=a[i][m]){
            puts("0");
            return;
        }
    }
    for (int i=1;i<=m;i++){
        if (a[1][m]!=a[n][m]){
            puts("0");
            return ;
        }
    }
    int N = n/2;
    int M = m/2;
    for (int i=1;i<=n;i++){
        int len = 1;
        while (len<M&&a[i][len+1]==a[i][m-len])len++;
        lr[i] = len;
    }
    for (int i=1;i<=m;i++){
        int len =1;
        while (len<N&&a[len+1][i]==a[n-len][i])len++;
        lc[i] = len;
    }
  //  debug();
    int imin =1;
    while (imin<N&&lr[imin]==M&&lr[n-imin+1]==M)imin++;
    int jmin =1;
    while (jmin<M&&lc[jmin]==N&&lc[m-jmin+1]==N)jmin++;
    for (int i=N-1;i>=1;i--){
        lr[i] = min(min(lr[i],lr[i+1]),lr[n-i+1]);
    }
    for (int i=M-1;i>=1;i--){
        lc[i] = min(min(lc[i],lc[i+1]),lc[m-i+1]);
    }
   // cout<<"imin:"<<imin<<endl;
    //cout<<"jmin:"<<jmin<<endl;
   // debug();
    int ans =0;
    for (int i=imin;i>1;i--) for (int j=jmin;j>1;j--){
        if (lr[i]>=j-1&&lc[j]>=i-1){
            ans++;
        }
    }
    cout<<ans<<endl;
 
}
int main(){
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
/*
3
 6 8
acbbbbca
dcaccacd
cdaddadc
cdaddadc
dcaccacd
acbbbbca
 6 8
acbcbbca
dcaccacd
cdaddadc
cdaddadc
dcaccacd
acbbbbca
6 8
acbbbbca
dcadcacd
cdaddadc
cdaddadc
dcaccacd
acbbbbca
 */
