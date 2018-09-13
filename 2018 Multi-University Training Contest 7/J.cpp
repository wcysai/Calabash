#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
typedef long long LL;
struct Mat {
    LL val[3][3];
    int height,width;
    Mat(int height,int width):height(height),width(width){
        memset(val,0,sizeof val);
    }
    Mat operator *(const Mat& x){
        assert(width == x.height);
        Mat ret(height,x.width);
        memset(ret.val,0,sizeof ret.val);
        for (int i=0;i<height;i++) {
            for (int j = 0; j < x.width; j++) {
                for (int k = 0; k < width; k++) {
                    ret.val[i][j] += val[i][k] * x.val[k][j] % mod;
                    ret.val[i][j] %= mod;
                }
            }
        }
        return ret;
    }
};
Mat power(Mat x,LL y){
    Mat ret(3,3);
    ret.val[0][0] = ret.val[1][1] = ret.val[2][2] = 1;
    while (y){
        if (y&1){
            ret = ret* x;
        }
        y>>=1;
        x = x*x;
    }
    return ret;
}
void solve(){
    LL A,B,C,D,P,n;
    scanf("%lld%lld%lld%lld%lld%lld",&A,&B,&C,&D,&P,&n);
//    A%=P;B%=P;C%=P;D%=P;
    if (n == 1){
        cout<<A<<endl;
        return;
    }
    if (n == 2){
        cout<<B<<endl;
        return;
    }
    Mat tmp(3,3);
    memset(tmp.val,0,sizeof tmp.val);
    tmp.val[0][0] = D;
    tmp.val[0][1] = C;
    tmp.val[1][0] = 1;
    tmp.val[2][2] = 1;
    LL N = sqrt(P);
    Mat a(3,1);
    a.val[0][0] = B;
    a.val[1][0] = A;
    a.val[2][0] = 1;
    for (int i=3;i<=min(N,n);i++){
        tmp.val[0][2] = P/i;
        a = tmp*a;
    }
    if (N>=n){
        cout<<a.val[0][0]<<endl;
        return ;
    }
    int L =1,R = N;
    for (int i = sqrt(P);i>=0;i--){
        L = max(L,R+1);
        if (i == 1){
            R = P;
        }else if (i == 0){
            R = n;
        }else{
            R = P/i;
        }
        L = max(3,L);
        tmp.val[0][2] = i;
        R = min(R,(int)n);
        if (L>R)continue;
        a = power(tmp,R-L+1)*a;
    }
    cout<<a.val[0][0]<<endl;
}
int main(){
    int T;
    for (scanf("%d",&T);T;T--){
        solve();
    }
    return 0;
}
