/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-06 12:25:32
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll T,n,k;
ll get(vector<ll> &v)
{
    ll s=0;
    for(int i=0;i<(int)v.size();i++) s=s*10+v[i];
    return s;
}
unordered_map<ll,ll> mp;
ll cnt[20],a[20];
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&k);
        mp.clear();
        ll Min=INT_MAX,Max=-INT_MAX;
        if(k>8)
        {
            memset(cnt,0,sizeof(cnt));
            while(n) {cnt[n%10]++; n/=10;}
            int id=-1;
            for(int i=1;i<=9;i++) 
            {
                if(cnt[i]>0)
                {
                    cnt[i]--;
                    id=i;
                    break;
                }
            }
            printf("%d",id);
            for(int i=0;i<=9;i++)
                for(int j=0;j<cnt[i];j++)
                    printf("%d",i);
            cnt[id]++;
            printf(" ");
            for(int i=9;i>=0;i--)
                for(int j=0;j<cnt[i];j++)
                    printf("%d",i);
            printf("\n");
            continue;
        }
        queue<P> que;
        while(que.size()) que.pop();
        que.push(P(n,0));
        while(que.size())
        {
            P p=que.front();que.pop();
            if(p.S>k) break;
            Min=min(Min,p.F);Max=max(Max,p.F);
            ll v=p.F;
            vector<ll> vv;
            vv.clear();
            while(v) {vv.push_back(v%10); v=v/10;}
            reverse(vv.begin(),vv.end());
            for(ll i=0;i<(ll)vv.size();i++)
                for(ll j=i+1;j<(ll)vv.size();j++)
                {
                    if(i==0&&vv[j]==0) continue;
                    swap(vv[i],vv[j]);
                    ll val=get(vv);
                    swap(vv[i],vv[j]);
                    if(val>=Min&&val<=Max) continue;
                    if(mp[val]!=1)
                    {
                        mp[val]=1;
                        que.push(P(val,p.S+1));
                    }
                }
        }
        printf("%lld %lld\n",Min,Max);
    }
    return 0;
}
