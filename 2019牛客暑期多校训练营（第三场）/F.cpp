#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int maxn = 505;
int mp[maxn][maxn];
int n,m,T;
const int inf = 1e9;
pair<int,int> num[maxn];
int sm[maxn],lsm,rsm;
int bg[maxn],lbg,rbg;
bool check(int len){
    if (len == 0)return true;
     
    lsm = lbg = 0;
    rsm = rbg = -1;
    for (int i=0;i<len;i++){
        while (rsm >= lsm && num[sm[rsm]].first >= num[i].first)rsm --;
        sm[++rsm] = i;
        while (rbg >= lbg && num[bg[rbg]].second <= num[i].second) rbg--;
        bg[++rbg] = i;
    }
    //printf("sm = %d,bg = %d\n",num[sm[rsm]].first,num[bg[rbg]].second);
    if (num[bg[lbg]].second - num[sm[lsm]].first <= m)return true;
     
    for (int i=len;i<n;i++){
        int st = i - len;
        while (rsm >= lsm && sm[lsm] <= st)lsm ++;
        while (rbg >= lbg && bg[lbg] <= st)lbg ++;
        while (rsm >= lsm && num[sm[rsm]].first >= num[i].first)rsm --;
        sm[++rsm] = i;
        while (rbg >= lbg && num[bg[rbg]].second <= num[i].second) rbg--;
        bg[++rbg] = i;
        if (num[bg[lbg]].second - num[sm[lsm]].first <= m)return true;
    }
    return false;
}
int gao(int l){
    if (l > n)return 0;
    if (!check(l))return 0;
    int r = n;
    while (r-l > 1){
        int mid = l + r >> 1;
        //  printf("mid = %d\n",mid);
        if (check(mid)){
            //  printf("ok\n");
            l = mid;
        }else{
            r = mid;
        }
    }
    for (int i=r;i>=l;i--)if (check(i)){
        //  printf("ret = %d\n",i);
        return i;
         
    }
    assert(0);
}
void solve(){
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d",&mp[i][j]);
        }
    }
    int ans = 0;
    for (int l = 0;l < n;l ++){
        for (int j=0;j<n;j++){
            num[j] = make_pair(inf,-inf);
        }
        for (int r = l;r < n;r ++){
            int width = r-l + 1;
            for (int j=0;j<n;j++){
                int sm,bg;
                tie(sm,bg) = num[j];
                sm = min(sm,mp[r][j]);
                bg = max(bg,mp[r][j]);
                num[j] = make_pair(sm,bg);
            }
            //     printf("l=%d,r=%d\n",l,r);
            //     for (int i=0;i<n;i++){
            //         printf("[%d,%d] ",num[i].first,num[i].second);
            //     }
            //     puts("");
            ans = max(ans,width * gao((ans + width - 1) / width));
        }
    }
    printf("%d\n",ans);
}
int main(){
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
