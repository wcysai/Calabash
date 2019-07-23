#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int MAXN = maxn;
const int MOD = 1e9+7;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
typedef long long LL;
typedef pair<LL,LL> pll;
bool illegal[maxn*4];
int n,m;
int x,y;
bool used[maxn*4];
bitset<MAXN> ok[4];
/*
 *   1 2 3 ... n
 *
 *
 *  2*n+1       3*n+1
 *  2*n+2       3*n+2
 *  .            .
 *  .            .
 *  .            .
 *  3*n          4*n
 *
 *
 *  n+1,n+2,n+3 ... 2*n
 *
 */
int brute_force2_1(){
    memset(used,0,sizeof used);
    int M =0;
    for (int i=1;i<=n;i++){
        M+= (illegal[2*n+i]==0);
        if (illegal[2*n+i])continue;
        if (i&1){
            used[2*n+i]=1;
        }else{
            used[3*n+i]=1;
        }
    }
    int ans = M;
    for (int i=1;i<=n;i++){
        if (illegal[i])continue;
        if (!used[2*n+i]&&!used[4*n+1-i]){
            ans++;
        }else if (!used[3*n+1-i]&&!used[3*n+i]){
            ans++;
        }
    }
    return ans;
}
int brute_force2_2(){
    memset(used,0,sizeof used);
    int M =0;
    for (int i=1;i<=n;i++){
        M+= (illegal[2*n+i]==0);
        if (illegal[2*n+i])continue;
        if (!(i&1)){
            used[2*n+i]=1;
        }else{
            used[3*n+i]=1;
        }
    }
    int ans = M;
    for (int i=1;i<=n;i++){
        if (illegal[i])continue;
        if (!used[2*n+i]&&!used[4*n+1-i]){
            ans++;
        }else if (!used[3*n+1-i]&&!used[3*n+i]){
            ans++;
        }
    }
    return ans;
}
int brute_force2_3(){
    memset(used,0,sizeof used);
    int M =0;
    for (int i=1;i<=n;i++){
        M+= (illegal[2*n+i]==0);
        if (illegal[2*n+i])continue;
        used[2*n+i]=1;
 
    }
    int ans = M;
    for (int i=1;i<=n;i++){
        if (illegal[i])continue;
        if (!used[2*n+i]&&!used[4*n+1-i]){
            ans++;
        }else if (!used[3*n+1-i]&&!used[3*n+i]){
            ans++;
        }
    }
    return ans;
}
int brute_force2_4(){
    memset(used,0,sizeof used);
    int M =0;
    for (int i=1;i<=n;i++){
        M+= (illegal[2*n+i]==0);
        if (illegal[2*n+i])continue;
        used[3*n+i]=1;
 
    }
    int ans = M;
    for (int i=1;i<=n;i++){
        if (illegal[i])continue;
        if (!used[2*n+i]&&!used[4*n+1-i]){
            ans++;
        }else if (!used[3*n+1-i]&&!used[3*n+i]){
            ans++;
        }
    }
    return ans;
}
int brute_force1_1(){
    memset(used,0,sizeof used);
    int N = 0;
    for (int i=1;i<=n;i++){
        N+= (illegal[i]==0);
        if (illegal[i])continue;
        if (i&1){
            used[i] =1;
        }else{
            used[n+i]=1;
        }
    }
    int ans = N;
    for (int i=1;i<=n;i++){
        if (illegal[2*n+i])continue;
        if (!used[i]&&!used[2*n+1-i]){
            ans++;
        }else if (!used[n+1-i]&&!used[n+i]){
            ans++;
        }
    }
   // cout<<ans<<endl;
    return ans;
}
int brute_force1_2(){
    memset(used,0,sizeof used);
    int N = 0;
    for (int i=1;i<=n;i++){
        N+= (illegal[i]==0);
        if (illegal[i])continue;
        if (!(i&1)){
            used[i] =1;
        }else{
            used[n+i]=1;
        }
    }
    int ans = N;
    for (int i=1;i<=n;i++){
        if (illegal[2*n+i])continue;
        if (!used[i]&&!used[2*n+1-i]){
            ans++;
        }else if (!used[n+1-i]&&!used[n+i]){
            ans++;
        }
    }
    // cout<<ans<<endl;
    return ans;
}
int brute_force1_3(){
    memset(used,0,sizeof used);
    int N = 0;
    for (int i=1;i<=n;i++){
        N+= (illegal[i]==0);
        if (illegal[i])continue;
        used[i]=1;
    }
    int ans = N;
    for (int i=1;i<=n;i++){
        if (illegal[2*n+i])continue;
        if (!used[i]&&!used[2*n+1-i]){
            ans++;
        }else if (!used[n+1-i]&&!used[n+i]){
            ans++;
        }
    }
    // cout<<ans<<endl;
    return ans;
}
int brute_force1_4(){
    memset(used,0,sizeof used);
    int N = 0;
    for (int i=1;i<=n;i++){
        N+= (illegal[i]==0);
        if (illegal[i])continue;
        used[n+i]=1;
    }
    int ans = N;
    for (int i=1;i<=n;i++){
        if (illegal[2*n+i])continue;
        if (!used[i]&&!used[2*n+1-i]){
            ans++;
        }else if (!used[n+1-i]&&!used[n+i]){
            ans++;
        }
    }
    // cout<<ans<<endl;
    return ans;
}
void input(){
    for(int i=0;i<4;i++) {
        for(int j=1;j<=n/2;j++){
            ok[i].flip(j);
        }
        if(n&1){
            ok[i].flip(n/2+1);
        }
    }
    for(int i=0;i<m;i++) {
        scanf("%d%d",&x,&y);
        ok[0][x]=0;
        ok[2][n+1-x]=0;
        ok[1][y]=0;
        ok[3][n+1-y]=0;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    input();
 
    int ans=0;
    for(int i=0;i<4;i++) {
        if(n%2&&ok[i][n/2+1])
            ans--;
        ans+=ok[i].count();
    }
    if(n%2&&(ok[0][n/2+1]||ok[2][n/2+1]||ok[1][n/2+1]||ok[3][n/2+1]))
        ans+=1;
    printf("%d\n",ans);
 
}
