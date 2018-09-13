//
// Created by calabash_boy on 18-5-16.
//
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e4+100;
int a[maxn],b[maxn];
int rk[maxn];
int n;
bool cmp(int x,int y){
    return a[x]>a[y];
}
int main(){
    while (scanf("%d",&n)!=EOF){
        for (int i=0;i<n;i++){
            scanf("%d%d",a+i,b+i);
            rk[i] =i;
        }
        sort(rk,rk+n,cmp);
        LL ans =0;
        LL ans2 =0;
        LL nowV =0;
        LL nowV2=0;
        for (int i=0;i<n;i++){
           // cout<<nowV<<endl;
            LL tempV = nowV+1LL*a[rk[i]]*b[rk[i]];
            ans+=(nowV+tempV)*b[rk[i]];
            nowV = tempV;
            LL tempV2 = nowV2+1LL*a[i]*b[i];
            ans2 +=(nowV2+tempV2)*b[i];
            nowV2 = tempV2;
        }
        ans -=ans2;
        if (ans&1){
            printf("%lld.5\n",ans/2);
        }else{
            printf("%lld.0\n",ans/2);
        }
    }
    return 0;
}
