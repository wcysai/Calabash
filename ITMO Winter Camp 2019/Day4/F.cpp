#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll N,V,D,a[50];
ll bit[MAXN+1];
ll sum(ll i)
{
    ll s=0;
    while(i)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(ll i,ll x)
{
    while(i<=MAXN)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
struct query
{
    ll x,y,type;
};
bool cmp(query p,query q)
{
    return p.x<q.x;
}
int main()
{
    scanf("%lld",&N);
    for(ll tot=1;tot<=N;tot++)
    {
        scanf("%lld%lld",&V,&D);
        for(ll i=0;i<V;i++)  scanf("%lld",&a[i]); 
        vector<query> v1; vector<P> v2; v1.clear(); v2.clear(); 
        ll sz=V/2;
        for(ll i=0;i<(1<<sz);i++)
        {
            ll sum=0,curmin=D+1;
            for(ll j=0;j<sz;j++)
                if(i&(1<<j)) sum+=a[j]; else curmin=min(curmin,a[j]);
            ll val=max(0LL,D-sum);
            if(D>=sum)v1.push_back((query){D-sum,val,1}); 
            if(D>=sum+curmin) v1.push_back((query){D-sum-curmin,val,-1});
        }
        for(ll i=0;i<(1<<(V-sz));i++)
        {
            ll sum=0,curmin=D+1;
            for(ll j=0;j<V-sz;j++)
                if(i&(1<<j)) sum+=a[sz+j]; else curmin=min(curmin,a[sz+j]);
            v2.push_back(P(sum,sum+curmin));
        }
        sort(v1.begin(),v1.end(),cmp); sort(v2.begin(),v2.end());
        ll ans=0,now=0,cnt=0;
        memset(bit,0,sizeof(bit));
        for(ll i=0;i<(int)v1.size();i++)
        {
            query q=v1[i];
            while(now<(int)v2.size()&&v2[now].F<=q.x)
            {
                add(v2[now].S,1);cnt++;now++;
            }
            ans+=q.type*(cnt-sum(q.y));
            //printf("%lld %lld\n",v1[i].x,cnt-sum(x));
        }
        printf("%lld %lld\n",tot,ans);
    }
    return 0;
}

