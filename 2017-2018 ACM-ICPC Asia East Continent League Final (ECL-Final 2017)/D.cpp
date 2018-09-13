//
// Created by calabash_boy on 18-5-24.
//
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll prime[MAXN];
bool is_prime[MAXN];
ll pow10[20];
ll t,p;
set<ll> s;
map<ll,ll> mp;
ll L,R;
ll sieve(ll n)
{
    for(ll i=1;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    ll p=0;
    for(ll i=2;i<=n;i++)
    {
        if(!is_prime[i]) continue;
        prime[p++]=i;
        for(ll j=2*i;j<=n;j+=i) is_prime[j]=false;
    }
    return p;
}
ll cnt_dig(ll x)
{
    if(x==0) return 0;
    return 1+cnt_dig(x/10);
}
void check(ll num,ll tg)
{
    ll nxt=tg*tg/num;
    ll a=cnt_dig(num),b=cnt_dig(tg),c=cnt_dig(nxt);
    ll digit_cnt=a+b+c;
    if(digit_cnt>=16) return;
    ll res=num*pow10[b+c]+tg*pow10[c]+nxt;
    while(digit_cnt<16)
    {
        s.insert(res);
        if((nxt*nxt)%tg!=0) break;
        num=tg;tg=nxt;nxt=tg*tg/num;
        ll d=cnt_dig(nxt);
        digit_cnt+=d;
        if(digit_cnt<=15) res=res*pow10[d]+nxt;
    }
}
void dfs(ll now,vector<P> &v,ll num,ll tg)
{
    if(now==v.size()) {check(num,tg); return;}
    for(ll i=0;i<=v[now].S;i++)
    {
        dfs(now+1,v,num,tg);
        num=num*v[now].F;
        if(num>=tg) return;
    }
}
void add_to_set(ll x)
{
    vector<P> v;
    ll dummy=x;
    v.clear();
    for(ll i=0;i<p;i++)
    {
        if(is_prime[x])
        {
            v.push_back(P(x,1));
            break;
        }
        ll cnt=0;
        while(x%prime[i]==0)
        {
            x/=prime[i];
            cnt++;
        }
        if(cnt) v.push_back(P(prime[i],cnt));
        if(x==1) break;
    }
    for(ll i=0;i<v.size();i++) v[i].S*=2;
    dfs(0,v,1,dummy);
}
int main()
{
    p=sieve(100000);
    pow10[0]=1;
    for(ll i=1;i<=18;i++) pow10[i]=pow10[i-1]*10;
    for(ll i=2;i<=100000;i++)
        add_to_set(i);
    scanf("%I64d",&t);
    ll kase=0,cnt=0;
    s.insert(10000000000000000LL);
    for(auto it=s.begin();it!=s.end();it++)
    {
        cnt++;
        mp[*it]=cnt;
    }
    while(t--)
    {
        kase++;
        scanf("%I64d%I64d",&L,&R);
        auto it1=mp.lower_bound(L);
        auto it2=mp.upper_bound(R);
        printf("Case #%I64d: %I64d\n",kase,(*it2).S-(*it1).S);
    }
    return 0;
}
