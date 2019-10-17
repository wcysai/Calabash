#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int T;
ll a,b,p;
ll mul(ll A,ll B,ll mod)
{
    return (A*B-(ll)((long double)A*B/mod)*mod+mod)%mod;
}
ll pow_mod(ll a,ll i,ll mod)
{
    if(i==0) return 1;
     ll s=1;
    while(i>0)
     {
         if(i&1) s=mul(s,a);
         a=mul(a,a);
         i>>=1;
     }
     return s;
}

vector<P> fact;

ll Pohlig_Hellman(ll g,ll x,ll p,vector<P> fact)
{
    ll q=p-1,now=g,res=1,ker=0;
    for(int i=0;i<(int)fact.size();i++)
    {
        for(int j=0;j<fact[i].S;j++)
        {
            q/=fact[i].F;
            //find dlg modulo current prime, code below is for the prime 2
            if(pow_mod(x,q,p)!=1)
            {
                x=mul(x,now,p);
                res+=ker;
            }
            now=pow_mod(now,fact[i].F,p);
            ker*=fact[i].F;
        }
    }
    return (p-1-res)%(p-1);
}
