#include<bits/stdc++.h>
#define MAXN 100005
#define INF 10000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n;
ll p[MAXN];
map<ll,int> mp;
set<P> s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&p[i]);
        if(i!=1) mp[p[i]]++;
    }
    for(auto et:mp) s.insert(P(et.F,et.S));
    ll ans=0;
    while(true)
    {
        if(s.size()>1)
        {
            auto it=s.end(); it--; ll x=it->F;
            int num1=it->S;
            it--; ll y=it->F; int num2=it->S;
            ll gap=x-y;
            int need=log2(num1)+1;
            ll steps=1LL*need*gap;
            if(p[1]-steps>=y)
            {
                p[1]-=steps;ans+=steps;
                s.erase((--s.end()));
                s.erase((--s.end()));
                s.insert(P(y,num1+num2));
            }
            else
            {
                ll l=0,r=gap;
                while(r-l>1)
                {
                    ll mid=(l+r)/2;
                    if(p[1]-mid*need>=x-mid) l=mid; else r=mid;
                }
                p[1]-=l*need;
                x-=l;
                ans+=l*need;
                ans+=p[1]-x;
                break;
            }
        }
        else
        {
            auto it=s.end(); it--;
            ll x=it->F;assert(it->S==n-1);
            int need=log2(n-1)+1;
            ll l=0,r=INF+1;
            while(r-l>1)
            {
                ll mid=(l+r)/2;
                if(p[1]-mid*need>=x-mid) l=mid; else r=mid;
            }
            p[1]-=l*need;
            x-=l;
            ans+=l*need;
            ans+=p[1]-x;
            break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
