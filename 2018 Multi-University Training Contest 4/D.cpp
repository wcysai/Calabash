#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,n,m;
const int maxn = 150;
int a[maxn];
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        int x,y;
        for (int i=0;i<n;i++){
            scanf("%d%d",&x,&y);
            a[i] = y+1;
        }
        sort(a,a+n);
        LL ans =1;
        int cnt =0;
        for (int i=0;i<n;i++){
            ans *=a[i];
            if (ans<=m){
                cnt++;
            }else{
                break;
            }
        }
        printf("%d\n",cnt);

    }
    return 0;
}
