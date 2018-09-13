/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-02 16:09:18
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q;
vector<int> a;
int dp1[MAXN],dp2[MAXN];
int st[10*MAXN],s,t;
vector<int> v;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        a.push_back(x);
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    n=(int)a.size();
    memset(dp1,-1,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            v.push_back(a[j]-a[i]);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    int sz=(int)v.size();
    dp1[0]=0;
    s=0;t=0;st[0]=0;
    while(s<=t)
    {
        int p=st[s];
        s++;
        for(int i=0;i<sz;i++)
        {
            if(p+2*v[i]<=20000&&dp1[p+2*v[i]]==-1)
            {
                dp1[p+2*v[i]]=dp1[p]+2;
                t++;
                st[t]=p+2*v[i];
            }
            if(p-2*v[i]>=0&&dp1[p-2*v[i]]==-1)
            {
                dp1[p-2*v[i]]=dp1[p]+2;
                t++;
                st[t]=p-2*v[i];
            }
        }
    }
    s=1;t=0;
    for(int i=0;i<n;i++) 
    {
        dp2[2*a[i]]=1;
        t++;st[t]=2*a[i];
    }
    while(s<=t)
    {
        int p=st[s];
        s++;
        for(int i=0;i<sz;i++)
        {
            if(p+2*v[i]<=20000&&dp2[p+2*v[i]]==-1)
            {
                dp2[p+2*v[i]]=dp2[p]+2;
                t++;
                st[t]=p+2*v[i];
            }
            if(p-2*v[i]>=0&&dp2[p-2*v[i]]==-1)
            {
                dp2[p-2*v[i]]=dp2[p]+2;
                t++;
                st[t]=p-2*v[i];
            }
        }
    }
    scanf("%d",&q);
    int l,r;
    for(int i=0;i<q;i++)
    {
        scanf("%d%d",&l,&r);
        if((l+r)&1) {puts("-1"); continue;}
        int ans=INF;
        if(dp1[max(r-l,l-r)]!=-1) ans=min(ans,dp1[max(r-l,l-r)]);
        if(dp2[l+r]!=-1) ans=min(ans,dp2[l+r]);
        if(ans==INF) puts("-1"); else printf("%d\n",ans);
    }
    return 0;
}
