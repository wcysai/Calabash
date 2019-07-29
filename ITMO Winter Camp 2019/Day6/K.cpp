#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)

const int maxn = 305;
const int inf = 1000000000;
int w[maxn][maxn], x[maxn], y[maxn];
int prev_x[maxn], prev_y[maxn],son_y[maxn],slack[maxn],par[maxn];
int lx, ly,pop;

void adjust(int v){ 
    son_y[v]=prev_y[v];
    if(prev_x[son_y[v]]!=-2)
        adjust(prev_x[son_y[v]]);
}

bool find(int v){
    int i;
    for(i=0;i<pop;i++)
        if(prev_y[i]==-1) {
            if(slack[i]>x[v]+y[i]-w[v][i]){
                slack[i]=x[v]+y[i]-w[v][i];
                par[i]=v;
            }
            if(x[v]+y[i]==w[v][i]){
                prev_y[i]=v;
                if(son_y[i]==-1){
                    adjust(i);
                    return true;
                }
                if(prev_x[son_y[i]]!=-1)
                    continue;
                prev_x[son_y[i]]=i;
                if(find(son_y[i]))
                    return true;
            }
        }
    return false;
}

int km() {
    int i,j,m;
    for(i=0;i<pop;i++){
        son_y[i]=-1;
        y[i]=0;
    }
    for(i=0;i<pop;i++){
        x[i]=0;
        for(j=0;j<pop;j++)
            x[i]=max(x[i],w[i][j]);
    }
    bool flag;
    for(i=0;i<pop;i++){
        for(j=0;j<pop;j++){
            prev_x[j]=prev_y[j]=-1;
            slack[j]=inf;
        }
        prev_x[i]=-2;
        if(find(i))continue;
        flag=false;
        while (!flag){
            m=inf;
            for(j=0;j<pop;j++)
                if(prev_y[j]==-1)
                    m=min(m,slack[j]);
            for(j=0;j<pop;j++) {
                if(prev_x[j]!=-1)
                    x[j]-=m;
                if(prev_y[j]!=-1)
                    y[j]+=m;
                else
                    slack[j]-=m;
            }
            for(j=0;j<pop;j++)
                if(prev_y[j]==-1&&!slack[j]) {
                    prev_y[j]=par[j];
                    if(son_y[j]==-1){
                        adjust(j);
                        flag=true;
                        break;
                    }
                    prev_x[son_y[j]]=j;
                    if(find(son_y[j])){
                        flag=true;
                        break;
                    }
                }
        }
    }
    int ans=0;
    for(int i=0;i<pop;i++)
        ans+=w[son_y[i]][i];
    return ans;
    
}

int n,m;
int ml[305], mr[305];
int main() {
    freopen("kingandroads.in","r",stdin);
    freopen("kingandroads.out","w",stdout);
    scanf("%d%d",&n,&m); pop=n;
    Rep(i,n) ml[i]=mr[i]=INT_MAX;
    vector<tuple<int,int,int>> edges;
    rep (i, m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        edges.emplace_back(u,v,w);
        ml[u]=min(ml[u],w);
        mr[v]=min(mr[v],w);
    }
    int ans=0;
    Rep(i,n){
        if(ml[i]==INT_MAX or mr[i]==INT_MAX){
            puts("NIE");
            return 0;
        }
        ans+=ml[i]+mr[i];
    }
    for(auto e:edges){
        int u,v,w;
        tie(u,v,w)=e;
        u--;v--;
        ::w[u][v]=max(::w[u][v],-w+(ml[u+1]+mr[v+1]));
    }
    ans-=km();
    cout<<ans<<endl;
    return 0;
}
