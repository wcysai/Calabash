#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN],b[MAXN];
struct seg
{
    ll l,r,id;
};
vector<ll> dis;
vector<seg> v;
vector<P> eve[4*MAXN];
int dp[4*MAXN];
P opt[4*MAXN];
vector<int> v1,v2;
int main()
{
    freopen("shelves.in","r",stdin);
    freopen("shelves.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        seg newseg;
        newseg.l=sum;
        newseg.r=sum+a[i];
        newseg.id=i;
        dis.push_back(newseg.l);dis.push_back(newseg.r);
        v.push_back(newseg);
        sum+=a[i];
    }
    sum=0;
    for(int i=1;i<=m;i++)
    {
        seg newseg;
        newseg.l=sum;
        newseg.r=sum+b[i];
        newseg.id=n+i;
        dis.push_back(newseg.l);dis.push_back(newseg.r);
        v.push_back(newseg);
        sum+=b[i];
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(auto s:v)
    {
        s.l=lower_bound(dis.begin(),dis.end(),s.l)-dis.begin()+1;
        s.r=lower_bound(dis.begin(),dis.end(),s.r)-dis.begin()+1;
        eve[s.r].push_back(P(s.l,s.id));
    }
    int sz=(int)dis.size();
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=sz;i++)
    {
        opt[i]=P(0,i-1);dp[i]=dp[i-1];
        for(auto p:eve[i])
        {
            if(dp[p.F]+1>dp[i])
            {
                dp[i]=dp[p.F]+1;
                opt[i]=P(p.F,p.S);
            }
        }
    }
    int now=sz;
    while(now)
    {
        if(opt[now].F==0) now--;
        else
        {
            int id=opt[now].S;
            if(id<=n) v1.push_back(id); else v2.push_back(id-n);
            now=opt[now].F;
        }
    }
    printf("%d %d\n",(int)v1.size(),(int)v2.size());
    sort(v1.begin(),v1.end()); sort(v2.begin(),v2.end());
    for(auto v:v1) printf("%d ",v); 
    puts("");
    for(auto v:v2) printf("%d ",v); 
    puts("");
    return 0;
}

