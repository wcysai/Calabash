#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXK 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,cur,tot,maxi,a[MAXN],cnt[MAXK],fact[MAXN],invf[MAXN];
int tmp[MAXK];
unordered_map<ll,int> dp;
vector<P> encode[1500005];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
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
int get_sum(vector<P> &v)
{
    int s=0;
    for(auto p:v) s+=p.F*p.S;
    return s;
}
int get_cnt(vector<P> &v)
{
    int s=0;
    for(auto p:v) s+=p.S;
    return s;
}
void dfs(int now,int sum)
{
    if(now==51)
    {
        encode[++tot].clear();
        for(int j=0;j<50;j++) if(tmp[j+1]) encode[tot].push_back(P(j+1,tmp[j+1]));
        return;
    }
    for(int i=0;sum+i*now<maxi-cur;i++)
    {
        dfs(now+1,sum+i*now);
        tmp[now]++;
    }
    tmp[now]=0;
}
ll get_hash(vector<P> &v)
{
    ll res=0;
    for(auto p:v)
    {
        int x=p.F;
        for(int i=0;i<p.S;i++)
        {
            res=(res<<1)|1;
            res=(res<<(p.F-1));
        }
    }
    return res;
}
int get_dp(vector<P> &v)
{
    vector<P> tmp; tmp.clear();
    for(auto p:v) if(p.S!=0) tmp.push_back(p);
    if(tmp.size()==0) return 1;
    ll hsh=get_hash(v);
    if(dp.find(hsh)!=dp.end()) return dp[hsh];
    int s=get_sum(tmp);
    for(auto &p:tmp)
    {
        int x=p.F;
        if(p.S&&x<=s+cur-x)
        {
            p.S--;
            add(dp[hsh],1LL*get_dp(tmp)*(p.S+1)%MOD);
            p.S++;
        }
    }
    return dp[hsh];
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=100000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100000]=pow_mod(fact[100000],MOD-2);
    for(int i=99999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d",&n,&cur);
    maxi=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        cnt[a[i]]++;
        maxi=max(maxi,a[i]);
    }
    if(maxi<=cur)
    {
        printf("%d\n",fact[n]);
        return 0;
    }
    tot=0;
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=tot;i++)
    {
        int s=get_sum(encode[i]);
        bool f=true;
        int coef=1;
        for(auto p:encode[i])
        {
            int x=p.F;
            coef=1LL*coef*comb(cnt[x],p.S)%MOD;
            cnt[x]-=p.S;
            if(cnt[x]<0) f=false;
        }
        if(f)
        {
            int val=get_dp(encode[i]),c=get_cnt(encode[i]);
            int cursum=s+cur;
            for(int j=maxi-cursum;j<=50;j++)
            {
                if(!cnt[j]) continue;
                if(j>s+cur) continue;
                add(ans,1LL*val*fact[n-cnt[0]-c-1]%MOD*coef%MOD*cnt[j]%MOD);
            }
        }
        for(auto p:encode[i]) cnt[p.F]+=p.S;
    }
    ans=1LL*ans*comb(n,cnt[0])%MOD;
    ans=1LL*ans*fact[cnt[0]]%MOD;
    printf("%d\n",ans);
    return 0;
}
