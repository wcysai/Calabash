//UOJ 310
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 262144;
const int MOD = 1e9+7;
const int INV2 = (MOD+1)>>1;
const int INV4 = 1LL*INV2*INV2%MOD;
int a[N],b[N];
int n;
//xor fwt : A[i] = \sigma{-1^([i&j])*a[j]}   [x]:count of 1-bit
void FWT(int *a,int n,int r){
    for (int i=1;i<n;i<<=1){
        for (int j=0;j<n;j+=(i<<1)){
            for (int k =0;k<i;k++){
                int x = a[j+k];
                int y = a[j+k+i];
                if (r){
                    a[j+k] = (x+y)%MOD;
                    a[j+k+i] = (x-y+MOD)%MOD;
                }else{
                    a[j+k] = 1LL*(x+y)*INV2%MOD;
                    a[j+k+i] = 1LL*(x-y+MOD)*INV2%MOD;
                }
            }
        }
    }
}
LL pow_mod(LL x,LL y){
    LL ret = 1;
    for (;y;y>>=1){if (y&1) ret = ret*x%MOD;x = x*x%MOD;}
    return ret;
}
int main(){
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d",a+i);
    }
    for (int i=0;i<n;i++){
        scanf("%d",b+i);
    }
    FWT(b,n,1);
    FWT(a,n,1);
    for (int i=0;i<n;i++){
        a[i] = 1LL*b[i] * pow_mod(a[i],MOD-2) %MOD;
    }
    FWT(a,n,0);
    for (int i=0;i<n;i++){
        printf("%d\n",a[i]);
    }
    return 0;
}
