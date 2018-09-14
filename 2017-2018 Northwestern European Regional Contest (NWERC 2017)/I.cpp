//
// Created by sy-chen on 18-5-31.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e2+10;
const int maxc = 1e4+100;
int n,c;
int d[maxn],s[maxn];
int rk[maxn];
int dp[maxn][maxc];
int pre[maxn][maxc];
vector<int>ans;
bool cmp(int x,int y){
    return d[x] - s[x] > d[y] - s[y];
}
int main(){
    scanf("%d%d",&n,&c);
    for (int i=1;i<=n;i++){
        scanf("%d%d",d+i,s+i);
        rk[i]=i;
    }
    sort(rk+1,rk+n+1,cmp);
    for (int j=0;j<=n;j++)
    for (int i=1;i<=c;i++){
        dp[j][i]=-1;
    }
    for (int i=1;i<=n;i++){
        int x = rk[i];
        int V = max(d[x],s[x]);
        for (int j=min(c,c-V+s[x]);j>=s[x];j--){
            if(dp[i-1][j-s[x]]!=-1&&dp[i][j]<dp[i-1][j-s[x]]+1){
                dp[i][j] = dp[i-1][j-s[x]]+1;
                pre[i][j] =x;
            }
        }
        for (int j=1;j<=c;j++){
            if(dp[i-1][j]>dp[i][j]){
                dp[i][j]=dp[i-1][j];
                pre[i][j]=0;
            }
        }
    }
    int now =n;
    int res=-1,cost =-1;
    for (int i=c;i>=0;i--){
        if(dp[now][i]>res)
        {
            res=dp[now][i];
            cost=i;
        }
    }
    printf("%d\n",dp[now][cost]);
    while (now){
        if(pre[now][cost]){
            ans.push_back(pre[now][cost]);
            //printf("%d ",pre[now]);
            int cc = cost-=s[pre[now][cost]];
            now--;
            cost = cc;
        }else{
            now--;
        }
    }
    reverse(ans.begin(),ans.end());
    for (int x:ans){
        printf("%d ",x);
    }
    puts("");
    return 0;
}
