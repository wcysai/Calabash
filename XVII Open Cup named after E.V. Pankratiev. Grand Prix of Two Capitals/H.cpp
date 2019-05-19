#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<100> bs;
int fact[105],invf[105];
int n,m,k,sz,sgn,ans;
vector<int> v;
bs a[18];
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
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
void dfs(int now,bs x,bs y)
{
    if(x.count()<k||y.count()<k) return;
    if(now==sz)
    {
        int cnt1=(int)x.count(),cnt2=(int)y.count();
        int res=1LL*comb(cnt1,k)*comb(cnt2,k)%MOD;
        if(sgn==1) add(ans,res); else dec(ans,res);
        return;
    }
    int id=v[now];
    dfs(now+1,x&a[id],y&(~a[id]));
    dfs(now+1,x&(~a[id]),y&a[id]);
}
bs mm;
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=100;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100]=pow_mod(fact[100],MOD-2);
    for(int i=99;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<n;i++) mm.set(i);
    for(int i=0;i<m;i++)
    {
        int x;
        scanf("%d",&x);
        for(int j=0;j<x;j++) 
        {
            int d; scanf("%d",&d);
            a[i].set(d-1);
        }
    }
    for(int mask=1;mask<(1<<m);mask++)
    {
        sgn=(__builtin_popcount(mask)&1?1:-1);
        v.clear();
        for(int i=0;i<m;i++) if(mask&(1<<i)) v.push_back(i);
        sz=(int)v.size();
        bs x,y;
        x=y=mm;
        dfs(0,x,y);
    }
    printf("%d\n",ans);
    return 0;
    return 0;
}
