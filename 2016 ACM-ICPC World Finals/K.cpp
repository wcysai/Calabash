#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
int n;
int a[maxn];
void answer(int ans){
    printf("%d\n",ans);
    exit(0);
}
void no(){
    puts("no quotation");
    exit(0);
}
int tot;
bool check(int k){
    if (k== 1)return tot == 2;
    int remain = a[0];
    int idx = 0;
    for (int j=k;j>=1;j--){
        if (j > remain)return false;
        remain -= j;
        if (remain == 0){
            idx ++;
            remain = a[idx];
        }
    }
    remain = a[n-1];
    idx = n-1;
    for (int j=k;j>=1;j--){
        if (j > remain)return false;
        remain -= j;
        if (remain == 0){
            idx --;
            remain = a[idx];
        }
    }
    return true;
}
int main(){
    scanf("%d",&n);
    tot = 0;
    for (int i=0;i<n;i++){
        scanf("%d",a+i);
        tot += a[i];
    }
    if (tot &1)no();
    for (int i=100;i>=1;i--){
        int need = i * i + i;
        if (need > tot) continue;
        else if (check(i)){
            answer(i);
        }
    }
    no();
    return 0;
}
