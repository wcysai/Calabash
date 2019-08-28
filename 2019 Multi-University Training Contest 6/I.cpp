#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXK 5
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
map<int,ll> mp[6];
int a[MAXN];
ll ans;
void ins(int x)
{
    vector<P> v,tmp;
    v.clear(); tmp.clear();
    v.push_back(P(x,x));
    for(int i=1;i<=5;i++)
    {
        for(auto p:v)
        {
            mp[i][p.F]+=p.S; ans+=p.S;
            auto it=mp[i].upper_bound(p.F);
            ll rem=p.S;
            while(it!=mp[i].end())
            {
                if(!rem) break;
                ll minx=min(rem,it->S);
                tmp.push_back(P(it->F,minx));
                it->S-=minx; ans-=minx; rem-=minx;
                if(!(it->S)) it=mp[i].erase(it);
                else break;
            }
        }
        swap(v,tmp); tmp.clear();
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=5;i++) mp[i].clear();
        ans=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            ins(a[i]);
            printf("%lld%c",ans,i==n?'\n':' ');
        }
    }
    return 0;
}
