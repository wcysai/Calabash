#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
typedef long long ll;
ll a[maxn];
ll sum[maxn];
ll n,L;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        int A,B;
        cin>>A>>B;
        a[i] = min(A,B);
    }
    cin>>L;
    sort(a + 1,a + 1 + n);
    for (int i=1;i<=n;i++){
        sum[i] = sum[i-1] + a[i];
    }
    for (int ans = n;ans >= 0;ans --){
        if (ans == 1){
            cout<<1<<endl;
            return 0;
        }
        double temp = 0;
        if (ans >=2){
            temp = sum[ans - 2] + 1.0 * (a[ans] + a[ans-1]) / 2;
        }else{
            temp = 1.0 *sum[ans] / 2;
        }
        if (temp < L){
            cout<<ans<<endl;
            return 0;
        }
    }
    return 0;
}
