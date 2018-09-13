#include<bits/stdc++.h>
#define F first
#define S second
#define PB(x) push_back(x)
#define debug(x) cout<<"[debug] "<<#x<<":"<<x<<endl
#define PB push_back
#define PF push_front
using namespace std;
typedef long long LL;
const int MAXN = 2e4+100;
LL A[MAXN];
LL vis[MAXN];
LL circle[MAXN*2];
LL pre[MAXN*2];
LL tot;
LL n,s,m,k;
LL calc(LL rst){
    deque<LL> q;
    LL res=0;
    q.PF(0);
    for(LL i=1;i<=tot;i++){
        while(!q.empty() && pre[q.front()]>pre[i])q.pop_front();
        q.PF(i);
        while(!q.empty() && i-q.back()>rst)q.pop_back();
        res=max(res,pre[i]-pre[q.back()]);
    }
    return res;
}
LL sum,ans;
void work(int cur,LL &Tans){
    while(!vis[cur]){
        circle[++tot]=A[cur];
        sum+=A[cur];
        vis[cur]=1;
        cur=(cur+k)%n;
    }
    LL rest=0;
    sum>0?ans+=(m/tot)*sum,rest = m%tot:rest = min(m,tot);
    LL up=tot;pre[0]=0;
    for(int j=1;j<=up;j++)circle[++tot]=circle[j];
    for(int i=1;i<=tot;i++)pre[i]=pre[i-1]+circle[i];
    Tans=max(Tans,ans+ calc(rest));
    if (sum < 0) return;
    ans=(m/up-1)*sum;
    rest=up;
    Tans=max(Tans,ans+ calc(rest));
}
void solve(){
    memset(vis,0,sizeof(vis));
    scanf("%lld%lld%lld%lld",&n,&s,&m,&k);
    for (int i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }
    LL Tans=0;
    for(LL ii=0;ii<n;ii++){
        if(!vis[ii]){
            tot=sum=ans=0;
            work(ii,Tans);
        }
    }
    printf("%lld\n",max(0LL,s-Tans));
}
int main(){
    int T;
    scanf("%d",&T);
    for (int Cas =1;Cas <=T;Cas ++){
        printf("Case #%d: ",Cas);
        solve();
    }
    return 0;
}
