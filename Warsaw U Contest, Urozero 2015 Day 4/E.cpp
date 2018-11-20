/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-17 20:38:35
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 fjsdoifk
#define x2 fdsiofsk
#define y1 kjsidof
#define y2 cdoisakjf
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,a[MAXN];
ll x1,y1,x2,y2;
int ans[MAXN];
ll x[MAXN],y[MAXN];
int bit[MAXN+1],k[MAXN];
bool f;
ll sum(ll i)
{
    ll s=0;
    while(i>0)
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
struct node
{
    int x,y,t;
};
vector<node> all;
bool cmp(node p,node q)
{
    if(p.x!=q.x) return p.x<q.x;
    return p.y<q.y;
}
void solve(vector<node> &v,ll l,ll r)
{
    if(l==r)
    {
        for(auto it:v) ans[it.t]=l;
        return;
    }
    ll mid=(l+r)/2;
    sort(v.begin(),v.end(),cmp);
    vector<node> lit;lit.shrink_to_fit();
    vector<node> notlit;notlit.shrink_to_fit();
    vector<node> tobeadded;tobeadded.shrink_to_fit();
    vector<node> realnotlit;realnotlit.shrink_to_fit();
    vector<ll> save;save.shrink_to_fit();
    for(auto it:v) if(it.t<=mid) lit.push_back(it); else notlit.push_back(it);
    ll now=0;
    for(ll i=0;i<(int)notlit.size();i++)
    {
        while(now<(int)lit.size()&&lit[now].x<=notlit[i].x) {add(lit[now].y,1); save.push_back(lit[now].y); now++;}
        ll cnt=((not f)?sum(notlit[i].y):sum(notlit[i].y)-sum(notlit[i].y-1));
        if(cnt<k[notlit[i].t]) 
        {
            k[notlit[i].t]-=cnt;
            realnotlit.push_back(notlit[i]);
        }
        else
        {
            add(notlit[i].y,1);save.push_back(notlit[i].y);
            tobeadded.push_back(notlit[i]);
        }
    }
    for(auto it:tobeadded) lit.push_back(it);
    for(auto it:save) add(it,-1);
    notlit.clear();notlit.shrink_to_fit();
    tobeadded.clear();tobeadded.shrink_to_fit();
    save.clear();save.shrink_to_fit();
    solve(lit,l,mid);solve(realnotlit,mid+1,r);
}
int main()
{
    scanf("%lld",&n);
    scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
    if(x1*y2-x2*y1<0)
    {
        swap(x1,x2);
        swap(y1,y2);
    }
    f=false;
    vector<ll> cmp1,cmp2;
    if(x1*y2==x2*y1)
    {
        f=true;
        for(ll i=1;i<=n;i++)
        {
            ll a,b;
            scanf("%lld%lld",&a,&b);
            y[i]=x1*b-y1*a;
            if(x1==0)
            {
                if(y1>0) x[i]=b; else x[i]=-b;
            }
            else if(x1>0) x[i]=a;
            else x[i]=-a;
            cmp1.push_back(x[i]);cmp2.push_back(y[i]);
        }
    }
    else
    {
        for(ll i=1;i<=n;i++) 
        {
            ll a,b;
            scanf("%lld%lld",&a,&b);
            x[i]=x1*b-y1*a;
            y[i]=y2*a-x2*b;
            cmp1.push_back(x[i]);cmp2.push_back(y[i]);
        }
    }
    sort(cmp1.begin(),cmp1.end());
    cmp1.erase(unique(cmp1.begin(),cmp1.end()),cmp1.end());
    sort(cmp2.begin(),cmp2.end());
    cmp2.erase(unique(cmp2.begin(),cmp2.end()),cmp2.end());
    for(ll i=1;i<=n;i++)
    {
        x[i]=lower_bound(cmp1.begin(),cmp1.end(),x[i])-cmp1.begin()+1;
        y[i]=lower_bound(cmp2.begin(),cmp2.end(),y[i])-cmp2.begin()+1;
        all.push_back((node){(int)x[i],(int)y[i],i});
    }
    for(ll i=1;i<=n;i++) scanf("%d",&k[i]);
    solve(all,1,n);
    for(ll i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}

