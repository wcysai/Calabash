//
// Created by calabash_boy on 18-5-9.
//

#include<bits/stdc++.h>
#define MAXN 5005
#pragma GCC optimize("O3")
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
multiset<ll> s1,s2,s3;
ll s;
ll n,cost[MAXN];
string str1,str2;
int main()
{
    scanf("%lld",&n);
    for(int i=0;i<n;i++) scanf("%lld",&cost[i]);
    cin>>str1>>str2;
    s=0;
    for(ll i=0;i<n;i++)
    {
        if(str1[i]=='1') s+=cost[i];
        if(str1[i]=='1'&&str2[i]=='0') s1.insert(cost[i]);
        if(str2[i]=='1'&&str1[i]=='0') s2.insert(cost[i]);
        if(str1[i]=='1'&&str2[i]=='1') s3.insert(cost[i]);
    }
    ll ans=INF;
    ll st=s,ret=0;
    for(auto it=s1.rbegin();it!=s1.rend();it++)
        st-=*it,ret+=st;
    for(auto it=s2.begin();it!=s2.end();it++)
        st+=*it,ret+=st;
    ans=min(ans,ret);
    for(auto it=s3.rbegin();it!=s3.rend();it++)
    {
        s1.insert(*it);
        s2.insert(*it);
        st=s,ret=0;
        for(auto it=s1.rbegin();it!=s1.rend();it++)
            st-=*it,ret+=st;
        for(auto it=s2.begin();it!=s2.end();it++)
            st+=*it,ret+=st;
        ans=min(ans,ret);
    }
    printf("%lld\n",ans);
    return 0
