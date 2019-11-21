#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int s,d,t,n;
vector<int> endpoints;
vector<int> dis;
int l[MAXN],r[MAXN];
vector<int> regionid;
vector<ll> dp;
int getid(int x)
{
    return lower_bound(endpoints.begin(),endpoints.end(),x)-endpoints.begin();
}
int getregionid(int x)
{
    int id=getid(x);
    return (id+1)/2;
}
bool on_land(int x)
{
    if(x<0||x>s) return true;
    int id=getid(x);
    if(id>=(int)endpoints.size()) return false;
    if(x==endpoints[id]) return false;
    return (id&1?true:false);
}
bool same_region(int x,int y)
{
    return getregionid(x)==getregionid(y);
}
ll compute_dist(int x,int y)
{
    int dist=y-x;
    ll jump=min(1LL*(dist/d)*t+(dist%d),1LL*((dist-1)/d+1)*t);
    return min(1LL*dist,jump);
}
void add_all(int x)
{
    dis.push_back(x);
    int now=x;
    do
    {
        if(on_land(now+d)) break;
        if(!same_region(now,now+d)) now+=d,dis.push_back(now);
        else
        {
            int id=getid(now);
            if(id>=(int)endpoints.size()) break;
            if(endpoints[id]==now) id++;
            if(id>=(int)endpoints.size()) break;
            int dist=endpoints[id]-now;
            assert(dist>=d);
            now+=(dist/d)*d;
            dis.push_back(now);
        }
    }while(true);
    now=x;
    do
    {
        if(on_land(now-d)) break;
        if(!same_region(now,now-d)) now-=d,dis.push_back(now);
        else
        {
            int id=getid(now);
            if(id==0) break;
            int dist=now-endpoints[id-1];
            assert(dist>=d);
            now-=(dist/d)*d;
            dis.push_back(now);
        }
    }while(true);
}
void update(ll &a,ll b) {a=min(a,b);}
int main()
{
    scanf("%d%d%d",&s,&d,&t);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&l[i],&r[i]);
        endpoints.push_back(l[i]);
        endpoints.push_back(r[i]);
    }
    sort(endpoints.begin(),endpoints.end());
    for(int i=0;i<n;i++)
    {
        add_all(l[i]);
        add_all(r[i]);
    }
    add_all(0); add_all(s);
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int sz=(int)dis.size();
    regionid.resize(sz);
    for(int i=0;i<sz;i++) regionid[i]=getregionid(dis[i]);
    if((int)dis.size()>=1000000)
    {
        vector<int> tmp;
        tmp.push_back(dis[0]);
        int last=regionid[0];
        for(int i=1;i<(int)dis.size()-1;i++)
        {
            if(regionid[i]!=last||dis[i]-tmp.back()>=5)
            {
                tmp.push_back(dis[i]);
                last=regionid[i];
            }
        }
        tmp.push_back(dis.back());
        swap(tmp,dis);
        sz=(int)dis.size();
        regionid.resize(sz);
        for(int i=0;i<sz;i++) regionid[i]=getregionid(dis[i]);
    }
    dp.resize(sz);
    fill(dp.begin(),dp.end(),INF);
    dp[0]=0;
    for(int i=0;i<sz-1;i++)
    {
        int id=lower_bound(dis.begin(),dis.end(),dis[i]+d)-dis.begin();
        if(id==sz||dis[id]!=dis[i]+d) id--;
        update(dp[id],dp[i]+t);
        if(dp[i]!=INF)
        {
            for(int j=i+1;j<=sz-1;j++)
            {
                if(regionid[i]!=regionid[j]) break;
                int x=dis[i],y=dis[j];
                update(dp[j],dp[i]+compute_dist(x,y));
            }

        }
    }
    printf("%lld\n",dp[sz-1]);
    return 0;
}
