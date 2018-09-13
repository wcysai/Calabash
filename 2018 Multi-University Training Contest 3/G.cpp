/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-30 14:59:54
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll T,n,t;
struct node
{
    ll x,y,id;
}a[MAXN];
bool cmp(node p,node q)
{
    if(p.x!=q.x) return p.x<q.x;
    else if(p.y!=q.y) return p.y<q.y;
    else return p.id<q.id;
}
ll st[MAXN];
bool same[MAXN];
vector<ll> G[MAXN];
ll solve(ll i,ll j)
{
    //printf("%lld %lld %lld %lld\n",i,j,st[i],st[j]);
    return a[st[i]].x*a[st[j]].y-a[st[i]].y*a[st[j]].x;
}
bool check()
{
    if(t<3) return false;
    ll res1=solve(t-3,t-1);
    ll res2=solve(t-3,t-2)+solve(t-2,t-1);
    //printf("%lld %lld %lld\n",t,res1,res2);
    if(res1<res2||(res1==res2&&a[st[t-2]].id>a[st[t-1]].id)) return true; else return false;
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        for(ll i=0;i<n;i++) same[i]=false,G[i+1].clear();
        for(ll i=0;i<n;i++) 
        {
            scanf("%lld%lld",&a[i].x,&a[i].y);
            a[i].id=i+1;
        }
        sort(a,a+n,cmp);
        for(ll i=1;i<n;i++) if(a[i].x==a[i-1].x&&a[i].y==a[i-1].y) same[i]=true;
        t=0;
        st[t++]=0;
        for(ll i=1;i<n;i++)
        {
            if(same[i]) continue;
            st[t++]=i;
            while(check()) {st[t-2]=st[t-1]; t--;}
        }
        vector<ll> ans;
        ans.clear();
        for(ll i=0;i<t;i++)
        {
            //printf("id %lld\n",a[st[i]].id);
            ans.push_back(a[st[i]].id);
        }
        assert(ans[0]==1);
        assert(ans.back()==n);
        for(ll i=0;i<(ll)ans.size();i++)
            if(i!=(ll)ans.size()-1) printf("%lld ",ans[i]); else printf("%lld\n",ans[i]);
    }
    return 0;
}
