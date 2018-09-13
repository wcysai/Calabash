#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;
typedef long long LL;
LL dp[1<<maxn];
LL a[maxn],b[maxn];
int n;
LL mask[maxn];
bool in[1<<maxn];
int que[(1<<maxn)+5];
int d[1<<maxn];
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a[i]>>b[i];
        int cnt;
        cin>>cnt;
        LL _mask = 0;
        for (int j=0;j < cnt;j++){
            int temp;
            cin>>temp;
            temp --;
            _mask |= (1<<temp);
        }
        mask[i] = _mask;
    }
    memset(dp,-INF,sizeof dp);
    dp[0] = 0;
    for (int i=0;i< (1<< n);i++){
        d[i] = __builtin_popcount(i);
    }
    int l = 0,r = 1;
    que[0] = 0;
    LL ans =0;
    while (r - l > 0){
        int head = que[l++];
        //cout<<head<<" "<<dp[head]<<endl;
        ans = max(ans,dp[head]);
        int cnt1 = __builtin_popcount(head)+1;
        for (int i=0;i<n;i++){
            if (head & (1<<i)){
                continue;
            }
            int nxt = head | (1<<i);
            d[nxt] --;
            if ((mask[i] & head) == mask[i]){
                dp[nxt] = max(dp[nxt],dp[head] + a[i] * cnt1 + b[i]);
            }
            if (d[nxt] == 0){
                que[r++] = nxt;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
