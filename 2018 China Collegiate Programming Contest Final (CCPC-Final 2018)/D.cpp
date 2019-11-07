#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,s;
vector<int> G[MAXN];
int prob_back[MAXN],no_father[MAXN],no_father_twice[MAXN],no_come_back[MAXN];
int inv[MAXN],a[MAXN],sz[MAXN],son[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void dfs(int v,int p)
{
    sz[v]=(int)G[v].size();
    son[v]=sz[v]-(p>0?1:0);
    if(!son[v])
    {
        no_father[v]=no_father_twice[v]=a[v]; no_come_back[v]=0;
        prob_back[v]=1;
        printf("%d %d %d %d %d\n",v,no_come_back[v],prob_back[v],no_father[v],no_father_twice[v]);
        return;
    }
    if(p) prob_back[v]=inv[sz[v]];
    int sum=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        int direct_back=inv[sz[to]];
        int no_direct_back=prob_back[to]; dec(no_direct_back,direct_back);
        if(p)
        {
            add(prob_back[v],1LL*direct_back*inv[sz[v]]%MOD*inv[sz[v]]%MOD);
            add(prob_back[v],1LL*no_direct_back*inv[sz[v]-1]%MOD*inv[sz[v]]%MOD);
        }
        add(no_father_twice[v],no_father[to]);
        add(sum,no_father[to]);
    }
    no_father_twice[v]=1LL*no_father_twice[v]*inv[son[v]]%MOD;
    for(auto to:G[v])
    {
        if(to==p) continue;
        int direct_back=inv[sz[to]];
        int no_direct_back=prob_back[to]; dec(no_direct_back,direct_back);

        add(no_father[v],no_come_back[to]); // don't go back
        if(son[v]==1) add(no_father[v],1LL*no_direct_back*a[v]%MOD); //don't directly go back(trapped in current vertex)
        else add(no_father[v],1LL*no_direct_back*(sum-no_father[to]+MOD)%MOD*inv[son[v]-1]%MOD); //don't directly go back(not trapped)
        add(no_father[v],1LL*direct_back*(sum-no_father[to]+MOD)%MOD*inv[son[v]]%MOD); //directly go back then to another subtree
        add(no_father[v],1LL*direct_back*no_father_twice[to]%MOD*inv[son[v]]%MOD); //directly go back and return

        add(no_come_back[v],no_come_back[to]); // don't go back
        if(son[v]!=1) add(no_come_back[v],1LL*no_direct_back*(sum-no_father[to]+MOD)%MOD*inv[son[v]]%MOD);  //don't directly go back(not trapped)
        if(son[v]!=1) add(no_come_back[v],1LL*direct_back*(sum-no_father[to]+MOD)%MOD*inv[son[v]+1]%MOD); //directly go back then to another subtree
        add(no_come_back[v],1LL*direct_back*no_father_twice[to]%MOD*inv[son[v]+1]%MOD); //directly go back and return
    }
    no_father[v]=1LL*no_father[v]*inv[son[v]]%MOD;
    no_come_back[v]=1LL*no_come_back[v]*inv[son[v]+1]%MOD;
    printf("%d %d %d %d %d\n",v,no_come_back[v],prob_back[v],no_father[v],no_father_twice[v]);
}
int main()
{
    for(int i=1;i<=100000;i++) inv[i]=pow_mod(i,MOD-2);
    scanf("%d",&t);
    for(int _=1;_<=t;_++)
    {
        memset(prob_back,0,sizeof(prob_back));
        memset(no_father,0,sizeof(no_father));
        memset(no_father_twice,0,sizeof(no_father_twice));
        memset(no_come_back,0,sizeof(no_come_back));
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        scanf("%d",&s);
        if(n==1) { printf("Case %d: %d\n",_,a[1]); continue;}
        dfs(s,0);
        printf("Case %d: %d\n",_,no_father[s]);
    }
    return 0;
}
