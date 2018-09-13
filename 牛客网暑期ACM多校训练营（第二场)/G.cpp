#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+100;
typedef long long LL;
LL n;
LL T;
LL a[maxn];
LL sum[maxn];
LL sum2[maxn];
LL loc[maxn];
inline LL query(int l,int r){
    return sum[r]-sum[l-1];
}
inline LL query2(int l,int r){
    return sum2[r]-sum2[l-1];
}
inline LL calc(int l,int mid,int r,LL limit){
    if (mid>=l&&mid<=r){
        //geshu
        LL num = query(l,mid-1);
        LL sum = query2(l,mid-1);
        LL cost = num*loc[mid]-sum;
        LL num2 = query(mid+1,r);
        LL sum2 = query2(mid+1,r);
        cost += sum2- num2*loc[mid];
        num+=num2+a[mid];
        LL rest = limit -num;
        cost += rest*(loc[r]-loc[mid]);
        return 2*cost;
    }else{
        return 0x3f3f3f3f3f3f3f3fLL;
    }
}
inline LL calc2(int l,int mid,int r,LL limit){
    if (mid>=l&&mid<=r){
        //geshu
        LL num = query(mid+1,r);
        LL sum = query2(mid+1,r);
        LL cost = sum-num*loc[mid];
        LL num2 = query(l+1,mid-1);
        LL sum2 = query2(l+1,mid-1);
        cost += num2*loc[mid]-sum2;
        num+=num2+a[mid];
        LL rest = limit -num;
        cost += rest*(loc[mid]-loc[l]);
        return 2*cost;
    }else{
        return 0x3f3f3f3f3f3f3f3fLL;
    }
}
bool check(LL limit){
    for (int i=1,j=1,mid=1;i<=n;i++){
        while (j<=n&&sum[j]-sum[i-1]<limit)j++;
        if (j>n)break;
        while (mid<j){
            LL cost1 = calc(i,mid,j,limit);
            LL cost2 = calc(i,mid+1,j,limit);
            if (cost2<=cost1){
                mid++;
            }else{
                break;
            }
        }
        LL cost = calc(i,mid,j,limit);
        if (cost<=T){
            return true;
        }
    }
    for (int i=n,j=n,mid=n;i>=1;i--){
        while (j>=1&&sum[i]-sum[j-1]<limit)j--;
        if (j<=0)break;
        while (mid>j){
            LL cost1 = calc2(j,mid,i,limit);
            LL cost2 = calc2(j,mid-1,i,limit);
            if (cost2<=cost1){
                mid--;
            }else{
                break;
            }
        }
        LL cost = calc2(j,mid,i,limit);
        if (cost<=T){
            return true;
        }
    }
    return false;
}
int main(){
    LL l =0;
    scanf("%lld%lld",&n,&T);
    for (int i=1;i<=n;i++){
        scanf("%lld",loc+i);
    }
    for (int i=1;i<=n;i++){
        scanf("%lld",a+i);
        sum[i] = sum[i-1]+a[i];
        sum2[i] = sum2[i-1] + a[i]*loc[i];
        l = max(l,a[i]);
    }
    LL r = sum[n];
 //   check(4);
    while (r-l>1){
        LL mid = l+r >>1;
        if (check(mid)){
            l = mid;
        }else{
            r = mid;
        }
    }
    if (check(r)){
        cout<<r<<endl;
    }else{
        cout<<l<<endl;
    }
    return 0;
}
