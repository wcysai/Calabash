#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define rep(i,a,n) for (ll i=a;i<n;i++)
#define per(i,a,n) for (ll i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
using namespace std;
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=s*a%mod;
        a=a*a%mod;
        i>>=1;
    }
    return s;
}
namespace linear_seq
{
    const ll N=10010;
    ll res[N],base[N],_c[N],_md[N];
    vector<ll> Md;
    void mul(ll *a,ll *b,ll k)
    {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if(a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for(ll i=k+k-1;i>=k;i--)
            if(_c[i]) rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    ll solve(ll n,VI a,VI b)//a:coefficient b:initial value b[n+1]=a[0]*b[n]+...
    {
        ll ans=0,pnt=0;
        ll k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];
        _md[k]=1;
        Md.clear();
        rep(i,0,k) if(_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while((1ll<<pnt)<=n) pnt++;
        for(ll p=pnt;p>=0;p--)
        {
            mul(res,res,k);
            if((n>>p)&1)
            {
                for(ll i=k-1;i>=0;i--) res[i+1]=res[i];
                res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if(ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s)
    {
        VI C(1,1),B(1,1);
        ll L=0,m=1,b=1;
        rep(n,0,SZ(s))
        {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if(d==0) ++m;
            else if(2*L<=n)
            {
                VI T=C;
                ll c=mod-d*pow_mod(b,mod-2)%mod;
                while(SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L;B=T;b=d;m=1;
            }
            else
            {
                ll c=mod-d*pow_mod(b,mod-2)%mod;
                while(SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    ll gao(VI a,ll n)
    {
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
}
ll T,n,k;
vector<int> v;
ll f[MAXN];
void add(ll &a,ll b) {a+=b; if(a>=MOD) a-=MOD;}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&k,&n);
        ll inv=pow_mod(k,MOD-2);
        if(n==-1)
        {
            ll res=2LL*pow_mod(k+1,MOD-2)%MOD;
            printf("%lld\n",res);
            continue;
        }
        v.clear();
        memset(f,0,sizeof(f));
        f[0]=1;
        v.push_back(f[0]);
        for(ll i=1;i<=2*k;i++)
        {
            for(ll j=max(0LL,i-k);j<=i-1;j++) add(f[i],f[j]);
            f[i]=1LL*f[i]*inv%MOD;
            v.push_back(f[i]);
        }
        printf("%lld\n",linear_seq::gao(v,n));
    }
    return 0;
}
