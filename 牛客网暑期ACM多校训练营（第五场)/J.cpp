#include<bits/stdc++.h>
using namespace std;
const int manx = 1e5+100;
typedef long long LL;
LL p2,p3;
LL n;
int main(){
    cin>>n>>p2>>p3;
    if (n<=2){
        cout<<min(p2,p3)<<endl;
        return 0;
    }
    if (3LL*p2<=2LL*p3){
        if (n%2==0){
            cout<<1LL*n/2*p2<<endl;
        }else{
            LL ans = 1LL*(n-3)/2*p2;
            ans += min(2*p2,p3);
            cout<<ans<<endl;
        }
    }else{
        if (n%3==0){
            cout<<1LL*n/3*p3<<endl;
        }else if (n%3==1){
            LL ans = 1LL*(n-4)/3*p3;
            ans += min(2*p2,2*p3);
            cout<<min(ans,1LL*n/3*p3+min(p2,p3))<<endl;
        }else{
            cout<<min(1LL*(n+1)/3*p3,1LL*n/3*p3+p2)<<endl;
        }
    }
    return 0;
}
