#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
string chara="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
string str="1121001101000200000000000000111111100000000000000000";
string s;
ll n;
ll k;
ll cost[55][4],num[MAXN];
ll getid(char ch)
{
    if(ch>='A'&&ch<='Z') return 2*(ch-'A');
    return 2*(ch-'a')+1;
}
ll getval(char ch)
{
    if(ch>='A'&&ch<='Z') return str[2*(ch-'A')]-'0';
    return str[2*(ch-'a')+1]-'0';
}
struct st
{
    ll a,b,id;
};
bool cmp1(st p,st q)
{
    if(p.a!=q.a) return p.a<q.a;
    return p.b<q.b;
}
bool cmp2(st p,st q)
{
    if(p.a+p.b!=q.a+q.b) return p.a+p.b<q.a+q.b;
    return p.a>q.a;
}
vector<st> v;
vector<st> gr,sm;
ll f[MAXN],g[MAXN];
ll change[MAXN];
ll a[MAXN],b[MAXN];
int main()
{
    scanf("%lld%lld",&n,&k);
    for(ll i=0;i<52;i++)
    {
        cost[i][0]=cost[i][1]=cost[i][2]=INF;
        for(ll j=0;j<52;j++)
        {
            ll val=str[j]-'0';
            cost[i][val]=min(cost[i][val],(j+52-i)%52);
        }
    }
    ll now=0;
    cin>>s;
    assert((ll)s.size()==n);
    for(ll i=0;i<n;i++) assert((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z'));
    if(k<0||k>2*n) {puts("-1"); return 0;}
    for(ll i=0;i<n;i++) now+=getval(s[i]);
    if(k>now)
    {
        for(ll i=0;i<n;i++)
        {
            if(getval(s[i])==2) continue;
            else if(getval(s[i])==1) v.push_back((st){cost[getid(s[i])][2],INF,i});
            else v.push_back((st){cost[getid(s[i])][1],cost[getid(s[i])][2]-cost[getid(s[i])][1],i});
        }
    }
    else
    {
        for(ll i=0;i<n;i++)
        {
            if(getval(s[i])==0) continue;
            else if(getval(s[i])==1) v.push_back((st){cost[getid(s[i])][0],INF,i});
            else v.push_back((st){cost[getid(s[i])][1],cost[getid(s[i])][0]-cost[getid(s[i])][1],i});
        }
    }
    for(auto p:v)
    {
        a[p.id]=p.a;
        b[p.id]=p.b;
    }
    for(auto p:v) if(p.a>p.b) gr.push_back(p); else sm.push_back(p);
    sort(gr.begin(),gr.end(),cmp2); sort(sm.begin(),sm.end(),cmp1);
    ll ans=INF,id=-1,need=max(k-now,now-k);
    fill(f,f+need+1,INF); fill(g,g+need+1,INF);
    f[0]=0;
    priority_queue<P,vector<P>,greater<P> > pque;
    for(ll i=0;i<(ll)sm.size();i++) pque.push(P(sm[i].a,sm[i].id)),pque.push(P(sm[i].b,sm[i].id));
    for(ll i=1;i<=min(need,2*(ll)sm.size());i++)
    {
        P p=pque.top(); pque.pop();
        if(p.F==INF) break;
        f[i]=f[i-1]+p.F; 
    }
    multiset<ll> ms1,ms2,ms3;
    ll cur=0;
    for(ll i=0;i<(ll)gr.size();i++)
    {
        ms1.insert(gr[i].a);
        ms2.insert(gr[i].a+gr[i].b);
    }
    g[0]=0;
    for(ll i=0;i<min((need+1)/2,(ll)gr.size());i++)
    {
        ll res1=INF,res2;
        if(ms3.size())
        {
            auto it=ms3.end(); it--; assert(ms2.size());
            auto id=ms2.begin();
            res1=cur-*it+*id;
        }
        assert(ms1.size()); assert(ms2.size());
        auto it=ms1.begin(); res2=cur+*it;
        g[2*i+1]=min(res1,res2);
        ms1.erase(ms1.find(gr[i].a));
        ms2.erase(ms2.find(gr[i].a+gr[i].b));
        ms3.insert(gr[i].b);
        cur+=gr[i].a+gr[i].b;
        g[2*i+2]=cur;
    }  
    for(ll i=0;i<=need;i++) 
    {
        if(f[i]+g[need-i]<ans)
        {
            ans=f[i]+g[need-i];
            id=i;
        }
    }
    assert(ans<INF&&ans>=0);
    printf("%lld\n",ans);
    while(pque.size()) pque.pop();
    for(ll i=0;i<(ll)sm.size();i++) pque.push(P(sm[i].a,sm[i].id)),pque.push(P(sm[i].b,sm[i].id));
    for(ll i=1;i<=id;i++)
    {
        P p=pque.top(); pque.pop();
        assert(p.F!=INF);
        ans-=p.F;
        change[p.S]++;
    }
    ll moves=need-id;
    multiset<P> mms1,mms2,mms3;
    for(ll i=0;i<(ll)gr.size();i++)
    {
        mms1.insert(P(gr[i].a,gr[i].id));
        mms2.insert(P(gr[i].a+gr[i].b,gr[i].id));
    }
    for(ll i=0;i<moves/2;i++)
    {
        change[gr[i].id]=2;
        ans-=gr[i].a+gr[i].b;
        mms1.erase(mms1.find(P(gr[i].a,gr[i].id)));
        mms2.erase(mms2.find(P(gr[i].a+gr[i].b,gr[i].id)));
        mms3.insert(P(gr[i].b,gr[i].id));
    }
    if(moves&1)
    {
        auto it=mms1.begin();
        if(it->F==ans)change[it->S]=1;
        else
        {
            auto it=mms3.end(); it--;
            auto id=mms2.begin(); change[id->S]=2; change[it->S]--;
        }
    }
    ll res=0;
    for(ll i=0;i<n;i++)
    {
        ll cur=getval(s[i]);
        ll to=(k>now?cur+change[i]:cur-change[i]);
        ll id=(getid(s[i])+cost[getid(s[i])][to])%52;
        res+=str[id]-'0';
        printf("%c",chara[id]);
    }
    printf("\n");
    return 0;
}
