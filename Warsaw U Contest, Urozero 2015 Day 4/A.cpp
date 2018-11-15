#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
char a[MAXN];
int sum[MAXN],L[MAXN],R[MAXN],st[MAXN];
set<int> s;
vector<P> v;
int main()
{
    scanf("%d",&n);
    scanf("%s",a+1);
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1];
        if(a[i]=='p') sum[i]++; else sum[i]--;
    }
    int t=0;
    for(int i=n;i>=0;i--)
    {
        while(t>0&&sum[st[t-1]]>=sum[i]) t--;
        R[i]=t==0?n+1:st[t-1];
        st[t++]=i;
    }
    for(int i=n;i>=1;i--)
    {
        sum[i]=sum[i+1];
        if(a[i]=='p') sum[i]++; else sum[i]--;
    }
    t=0;
    for(int i=1;i<=n+1;i++)
    {
        while(t>0&&sum[st[t-1]]>=sum[i]) t--;
        L[i]=t==0?0:st[t-1];
        st[t++]=i;
    }
    for(int i=n;i>=1;i--) R[i]=min(n,R[i-1]-1);
    for(int i=1;i<=n;i++) L[i]=max(1,L[i+1]+1);
    int ans=0;
    for(int i=1;i<=n;i++) v.push_back(P(L[i],i));
    sort(v.begin(),v.end());
    int now=0;
    for(int i=1;i<=n;i++)
    {
        while(now<n&&v[now].F<=i) {s.insert(v[now].S); now++;}
        if((int)s.size()<=0) continue;
        auto it=s.upper_bound(R[i]);
        if(it==s.begin()) continue;
        it--;
        ans=max(ans,*it-i+1);
    }
    printf("%d\n",ans);
    return 0;
}
