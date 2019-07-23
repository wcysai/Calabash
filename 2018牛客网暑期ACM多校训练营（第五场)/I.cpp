/*************************************************************************
    > File Name: I.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-02 13:11:26
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
P a[MAXN];
int bit[MAXN+1];
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
bool cmp(P p,P q)
{
    if(p.y!=q.y) return p.y<q.y;
    return p.x<q.x;
}
bool cmp2(P p,P q)
{
    if(p.x!=q.x) return p.x>q.x;
    return p.y<q.y;
}
int main()
{
    scanf("%d",&n);
    int ans=n%MOD;
    for(int i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y);
    sort(a,a+n,cmp);
    vector<int> v;
    for(int i=0;i<n;i++) v.push_back(a[i].y);
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=0;i<n;i++)
    {
        int pos=lower_bound(v.begin(),v.end(),a[i].y)-v.begin();
        add(pos+1,1);
        ans=(ans+sum(pos))%MOD;
    }
    memset(bit,0,sizeof(bit));
    vector<int> cache;
    sort(a,a+n,cmp2);
    //printf("%d\n",ans);
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        if(i!=0&&a[i].x!=a[i-1].x)
        {
            cnt+=cache.size();
            for(int j=0;j<(int)cache.size();j++)
            {
                int pos=cache[j];
                add(pos+1,1);
            }
            cache.clear();
        }
        int pos=lower_bound(v.begin(),v.end(),a[i].y)-v.begin();
        int p=sum(pos),q=sum(pos+1);
        //printf("%d %d\n",p,cnt-q);
        ans=(ans+1LL*p*(cnt-q))%MOD;
        cache.push_back(pos);
    }
    printf("%d\n",ans);
    return 0;
}
