/*************************************************************************
   >File Name: F.cpp
   >Author: Roundgod
   >Mail: wcysai@foxmail.com 
   >Created Time: 2018-10-26 14:36:44
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define prev daiskoda
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> VI;
int n,m,MOD;
ll pow_MOD(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=s*a%MOD;
        a=a*a%MOD;
        i>>=1;
    }
    return s;
}
namespace linear_seq
{
    const int N=10010;
    ll res[N],base[N],_c[N],_md[N];
    vector<ll> Md;
    void mul(ll *a,ll *b,int k)
    {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if(a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%MOD;
        for(int i=k+k-1;i>=k;i--)
            if(_c[i]) rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%MOD;
        rep(i,0,k) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b)//a:coefficient b:initial value b[n+1]=a[0]*b[n]+...
    {
        ll ans=0,pnt=0;
        int k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];
        _md[k]=1;
        Md.clear();
        rep(i,0,k) if(_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while((1ll<<pnt)<=n) pnt++;
        for(int p=pnt;p>=0;p--)
        {
            mul(res,res,k);
            if((n>>p)&1)
            {
                for(int i=k-1;i>=0;i--) res[i+1]=res[i];
                res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%MOD;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%MOD;
        if(ans<0) ans+=MOD;
        return ans;
    }
    VI BM(VI s)
    {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        rep(n,0,SZ(s))
        {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%MOD;
            if(d==0) ++m;
            else if(2*L<=n)
            {
                VI T=C;
                ll c=MOD-d*pow_MOD(b,MOD-2)%MOD;
                while(SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%MOD;
                L=n+1-L;B=T;b=d;m=1;
            }
            else
            {
                ll c=MOD-d*pow_MOD(b,MOD-2)%MOD;
                while(SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%MOD;
                ++m;
            }
        }
        return C;
    }
    int gao(VI a,ll n)
    {
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(MOD-c[i])%MOD;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
}
ll h(const vector<int> &a)
{
    ll ret=1;
    for(int x:a) ret=15*ret+(x+1);
    return ret;
}
void unite(int u,int v,vector<int> &p)
{
    if(p[u]==-1||p[v]==-1) return;
    int cur=p[u];
    for(int &x:p) if(x==cur) x=p[v];
}
void fix(vector<int> &p)
{
    vector<int> a(2*p.size(),-1);
    int cur=0;
    for(int &x:p)
    {
        if(x!=-1)
        {
            if(a[x]==-1) a[x]=cur++;
            x=a[x];
        }
    }
}
void solve()
{
    int states=1;
    queue<vector<int>>q;
    unordered_map<ll,int> mp;
    mp[h(vector<int>(n,-1))]=states++;
    q.push(vector<int>(n,-1));
    vector<pair<int,int>>ed;
    vector<int> masks;
    for(int i=0;i<(1<<n);i++)
    {
        bool f=true;
        for(int j=0;j<n-1;j++)
            if((i&(1<<j))&&(i&(1<<(j+1)))) f=false;
        if(f) masks.push_back(i);
    }
    vector<vector<int>>masks2(masks.size());
    for(int i=0;i<(int)masks.size();i++)
    {
        for(int nmask:masks)
        {
            if(!(masks[i]&nmask)) masks2[i].push_back(nmask);
        }
    }
    masks2.push_back(masks);masks.push_back((1<<n)-1);
    while (!q.empty()) 
    {
        auto vct=q.front();q.pop();
        int fr=mp[h(vct)];
        int cmask=0;
        for(int i=0;i<n;i++) if (vct[i]==-1) cmask|=1<<i;
        int id=lower_bound(masks.begin(),masks.end(),cmask)-masks.begin();
        assert(masks[id]==cmask);
        for(int mask:masks2[id])
        {
            auto nvct=vct;
            for(int i=0;i<n;i++) if (mask&(1<<i)) nvct.push_back(-1);
            else nvct.push_back(n+i);
            for(int i=0;i<n;i++) 
            {
                unite(i,i+n,nvct);
                if (i<n-1) unite(i+n,i+1+n,nvct);
            }
            vector<vector<int>>cnt(2,vector<int>(2*n));
            for(int i=0;i<2*n;i++) if (nvct[i]!=-1) cnt[i/n][nvct[i]]++;
            bool f=true;
            for(int i=0;i<2*n;i++) if (cnt[0][i]>0&&cnt[1][i]==0) f=false;
            if (!f) continue;
            nvct.erase(nvct.begin(),nvct.begin()+n);
            fix(nvct);
            ll ch=h(nvct);
            if (!mp.count(ch)) 
            {
                mp[ch]=states++;
                q.push(nvct);
            }
            ed.push_back({fr,mp[ch]});
        }
        set<int> st;
        for(int x:vct) if (x!=-1) st.insert(x);
        if (st.size()==1) 
        {
            ed.push_back({fr,0});
        }
    }
    sort(ed.begin(), ed.end());
    int prev=900;
    int vals=2*prev+100;
    vector<int> t;
    vector<int> dp(states);
    dp[1]=1;
    for(int i=0;i<vals+1;i++) 
    {
        vector<ll> ndp(states);
        for(auto o:ed) 
        {
            ndp[o.second]+=dp[o.first];
        }
        for(int j=0;j<states;j++) dp[j]=ndp[j]%MOD;
        if (i>0) t.push_back(dp[0]);
    }
    printf("%d\n",linear_seq::gao(t,m-1));
}
int main()
{
    scanf("%d%d%d",&n,&m,&MOD);
    solve();
    return 0;
}

