#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 30
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int maxv = 35;
const int maxd = 1005;
ll a[maxv];
ll dp[maxv][maxd];
int d,v;
void solve(int Case){
    scanf("%d%d",&v,&d);
    ll sum = 0;
    for (int i=1;i<=v;i++){
        scanf("%lld",a+i);
        sum += a[i];
    }
    sort(a+1,a+1+v,[](ll x,ll y){
            return x > y;
            });
    memset(dp,0,sizeof dp);
    dp[0][0] = 1;
    for (int i=1;i<=v;i++){
        for (int d_pre = 0;d_pre <=d;d_pre++)dp[i][d_pre] = dp[i-1][d_pre];
        for (int d_pre = 0;d_pre <=d;d_pre++){
            int d_now = d_pre + a[i];
            if (d_now > d)break;
            dp[i][d_now] += dp[i-1][d_pre];
        }
    }
   // for (int i=1;i<=v;i++){
   //     for (int di=0;di<=d;di++){
   //         printf("dp[%d][%d]=%lld\n",i,di,dp[i][di]);
   //     }
  //  }
    ll ans = 0;
    //all use
    if (sum <= d){
        ans ++;
    }
    //at least one unuse
    ll tmp_sum = 0;
    for (int i=v;i>=1;i--){
        ll tot_d = d - tmp_sum;
        for (int j = max(0ll,tot_d - a[i] + 1);j<=tot_d;j++){
            ans += dp[i-1][j];
            //printf("%lld,%d,%d\n",ans,i-1,j);
        }
        tmp_sum += a[i];
    }
    printf("%d %lld\n",Case,ans);
    //cout<<ans<<endl;
}
int main()
{
    int T;
    int Case = 1;
    for (scanf("%d",&T);T;T--){
        solve(Case);
        Case ++;
    }
    return 0;
}

