#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
typedef long long LL;
int a[maxn];
LL sum[maxn];
int n,p;
int main(){
    cin>>n>>p;
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        sum[i] = sum[i-1]+a[i];
    }
    LL ans =0;
    for (int i=1;i<=n-1;i++){
        LL ans1 = sum[i]%p;
        LL ans2 = sum[n]-ans1;
        ans2%=p;
        ans = max(ans,ans1+ans2);
    }
    cout<<ans<<endl;
    return 0;
}
