#include<bits/stdc++.h>
#define MAXN 100005
#define INF 8000000000000000000LL
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct frac
{
    ll p,q;

    frac(){}
    frac( ll tp, ll tq){ p = tp, q = tq;}
    bool pton()
    {
        ll g=__gcd(p,q);
        p/=g; q/=g;
        if(q<0) {p=-p; q=-q;}
    }
    bool operator < (const frac &rhs) const
    {
        return p*rhs.q<rhs.p*q;
    }
    bool operator <= (const frac &rhs) const
    {
        return p*rhs.q<=rhs.p*q;
    }
    bool operator == (const frac &rhs) const
    {
        return p*rhs.q==rhs.p*q;
    }
    void print()
    {
        pton();
        printf("%lld/%lld",p,q);
    }
};
struct event
{
    frac tt;
    ll da,db;
    bool operator < (const event &rhs) const
    {
        return tt<rhs.tt;
    }

};
vector<event> v;
ll T,N,C,a[MAXN],b[MAXN];
vector<frac> dis;
vector<frac> ans;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&N,&C);
        assert(C<=1000000000);
        for(ll i=1;i<=N;i++)
        {
            scanf("%lld%lld",&a[i],&b[i]);
            assert(1<=a[i]&&a[i]<=1000);
            assert(b[i]>=-1000&&b[i]<=1000);
        }
        v.clear(); dis.clear();
        ll suma=0,sumb=0;
        for(ll i=1;i<=N;i++)
        {
            if(a[i]==0)
            {
                sumb+=abs(b[i]);
                continue;
            }
            frac f(-b[i],a[i]);
            suma-=a[i]; sumb-=b[i];
            f.pton();
            v.push_back((event){f,2*a[i],2*b[i]});
            dis.push_back(f);
        }
        sort(dis.begin(),dis.end());
        sort(v.begin(),v.end());
        dis.erase(unique(dis.begin(),dis.end()),dis.end());
        bool inf=false;
        ans.clear();
        if(suma==0)
        {
            if(sumb==C) inf=true;
        }
        else
        {
            frac x=frac(C-sumb,suma);
            x.pton();
            if(x<=dis[0]) ans.push_back(x);
        }
        ll now=0;
        for(ll i=0;i<(int)dis.size()-1;i++)
        {
            while(now<(int)v.size()&&v[now].tt==dis[i])
            {
                suma+=v[now].da; sumb+=v[now].db;
                now++;
            }
            if(suma==0)
            {
                if(sumb==C) inf=true;
            }
            else
            {
                frac x=frac(C-sumb,suma);
                x.pton();
                if(x<=dis[i+1]&&dis[i]<x) ans.push_back(x);
            }
        }
        while(now<(int)v.size()&&v[now].tt==dis.back())
        {
            suma+=v[now].da; sumb+=v[now].db;
            now++;
        }
        if(suma==0)
        {
            if(sumb==C) inf=true;
        }
        else
        {
            frac x=frac(C-sumb,suma);
            x.pton();
            if(dis.back()<x) ans.push_back(x);
        }
        if(inf) puts("-1");
        else
        {
            if(!ans.size()) puts("0");
            else
            {
                assert((int)ans.size()<=2);
                printf("%d ",(int)ans.size());
                for(ll i=0;i<(int)ans.size();i++)
                {
                    ans[i].print();
                    printf("%c",i==(int)ans.size()-1?'\n':' ');
                }
            }
        }
    }
    return 0;
}
