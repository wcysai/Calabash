#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
mt19937 wdy(time(0));
const int N = 100000000;
vector<pair<int,int> > P;
int n;
 
void solve(){
    P.clear();
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        P.push_back(make_pair(x,y));
    }
    sort(P.begin(),P.end(),[](pair<int,int> x,pair<int,int> y){
        if (x.first != y.first)
            return x.first < y.first;
        return x.second < y.second;
    });
    int sp = n >> 1;
    int xlow = P[sp-1].first;
    int xhig = P[sp].first;
    if (xhig - xlow >= 2){
        printf("%d %d %d %d\n",xlow+1,0,xlow+1,1);
        return;
    }else if (xhig - xlow == 1){
        printf("%d %d %d %d\n",xlow,1000000000,xhig,-1000000000);
        return;
    }else{
        int ylow = P[sp-1].second;
        int yhig = P[sp].second;
        if (yhig - ylow >=2){
            int centerx = xlow;
            int centery = ylow + 1;
            int delta = 1000000000 - 5000;
            printf("%d %d %d %d\n",centerx-1,centery + delta,centerx+1,centery - delta);
            return;
        }else if (yhig - ylow == 1){
            int centerx = xlow;
            double delta = 1000000000 - 5000 + 0.5;
            double centery = ylow + 0.5;
            int righty = (int)(centery - delta);
            int lefty = (int)(centery + delta);
            printf("%d %d %d %d\n",centerx-1,lefty,centerx + 1,righty);
            return;
        }else assert(0);
    }
 
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
