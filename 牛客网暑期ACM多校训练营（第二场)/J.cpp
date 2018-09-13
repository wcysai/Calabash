#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
int n,m,T;
typedef pair<int,int> pii;
struct BIT{
    vector<vector<int> > val;
    void init(){
        val.resize(n+1);
        for (int i=0;i<=n;i++){
            val[i].resize(m+1);
        }
        for (int i=0;i<=n;i++){
            for (int j=0;j<=m;j++){
                val[i][j]=0;
            }
        }
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int y,int delta){
        while (x<=n){
            int yy = y;
            while (yy<=m){
                val[x][yy]+=delta;
                yy+=lowbit(yy);
            }
            x += lowbit(x);
        }
    }
    int query(int x,int y){
        int ans =0;
        while (x){
            int yy =y;
            while (yy){
                ans+=val[x][yy];
                yy-=lowbit(yy);
            }
            x -= lowbit(x);
        }
        return ans;
    }
}tree;
void add(int x1,int y1,int x2,int y2,int delta){
    tree.add(x1,y1,delta);
    tree.add(x1,y2+1,-delta);
    tree.add(x2+1,y1,-delta);
    tree.add(x2+1,y2+1,delta);
}
vector<pii> points[maxn];
vector<vector<int> > alive;
vector<pair<pii,pii> >rets[maxn];
vector<vector<int> > Cnt;
int main(){
    scanf("%d%d%d",&n,&m,&T);
    tree.init();
    alive.resize(n+1);
    for (int i=1;i<=n;i++){
        alive[i].resize(m+1);
        for (int j=1;j<=m;j++){
            int temp;
            scanf("%d",&temp);
            points[temp].push_back({i,j});
            alive[i][j] =1;
        }
    }
   // cout<<"1"<<endl;
    for (int i=1;i<=T;i++){
        int x1,y1,x2,y2,color;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&color);
        rets[color].push_back({{x1,y1},{x2,y2}});
        add(x1,y1,x2,y2,1);
    }
    Cnt.resize(n+1);
    for (int i=1;i<=n;i++){
        Cnt[i].resize(m+1);
        for (int j=1;j<=m;j++){
            Cnt[i][j] = tree.query(i,j);
        }
    }
   // cout<<2<<endl;
    int ans =0;
    for (int i=1;i<=n*m;i++){
        for (auto po:points[i]){
            int cnt = tree.query(po.first,po.second);
            if(cnt!=Cnt[po.first][po.second]){
                alive[po.first][po.second]=0;
            }
        }
        for (auto ret:rets[i]){
            int x1 = ret.first.first;
            int y1 = ret.first.second;
            int x2 = ret.second.first;
            int y2 = ret.second.second;
            add(x1,y1,x2,y2,-1);
        }
        for (auto po:points[i]){
            int cnt = tree.query(po.first,po.second);
            if (cnt!=0){
                alive[po.first][po.second]=0;
            }
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (!alive[i][j]){
                ans++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
