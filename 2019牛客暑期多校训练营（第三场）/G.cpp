#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 100;
ll a[maxn];
ll sum[maxn];
ll biggest[maxn];
ll temp_sum[maxn];
ll ans = 0;
int n;
int rk[maxn];
int my_rk[maxn];
void brute_force(int l,int r){
    for (int i=l;i<=r;i++){
        ll mx = -1;
        ll sm = 0;
        for (int j=i;j<=r;j++){
            mx = max(mx,a[j]);
            sm += a[j];
            if (mx * 2 <= sm)ans ++;
        }
    }
}
void solve(int l,int r){
   // cout<<l<<" "<<r<<endl;
    if (r-l <=0){
        brute_force(l,r);
       // cout<<ans<<endl;
        return;
    }
    int mid = l + r >> 1;
    int mx = -1;
    ll sm_left = 0;
    for (int i=mid;i>=l;i--){
        mx = max(mx,my_rk[i]);
        sm_left += a[i];
        biggest[i] = mx;
        temp_sum[i] = sm_left;
    }
    mx = -1;
    ll sm_right = 0;
    for (int i=mid+1;i<=r;i++){
        mx = max(mx,my_rk[i]);
        sm_right += a[i];
        biggest[i] = mx;
        temp_sum[i] = sm_right;
    }
    //mx at left
    for (int i=mid;i>=l;i--){
        ll need = max(0ll,2ll * a[rk[biggest[i]]] - temp_sum[i]);
        int L = lower_bound(temp_sum + mid + 1,temp_sum + r + 1,need) - temp_sum;
        int R = lower_bound(biggest + mid + 1, biggest + r + 1, biggest[i]) - biggest - 1;
        ans += max(0,R - L + 1);
    }
    reverse(biggest + l,biggest + mid + 1);
    reverse(temp_sum + l,temp_sum + mid + 1);
    //mx at right
    for (int i = mid+ 1;i <=r;i ++){
        ll need = max(0ll,2ll * a[rk[biggest[i]]] - temp_sum[i]);
        int L = lower_bound(temp_sum + l,temp_sum + mid + 1,need) - temp_sum;
        int R = lower_bound(biggest + l,biggest + mid + 1,biggest[i]) - biggest - 1;
        ans += max(0,R - L + 1);
    }
   // cout<<ans<<endl;
    solve(l,mid);
    solve(mid+1,r);
}
void solve(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        rk[i] = i;
        sum[i] = sum[i-1] + a[i];
    }
    sort(rk+1,rk+1+n,[](int x,int y){
        if (a[x] != a[y])return a[x] < a[y];
        return x < y;
    });
    for (int i=1;i<=n;i++){
        my_rk[rk[i]] = i;
    }
    ans = 0;
    solve(1,n);
    printf("%lld\n",ans);
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
