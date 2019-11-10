By sy_chen, contest: 2017-2018 ACM-ICPC, NEERC, Northern Subregional Contest, problem: (E) Equal Numbers, Accepted, #
#include<bits/stdc++.h>
#define MAXN 300005
#define MAXM 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
bool has[MAXM];
int cnt[MAXM];
vector<int> v1,v2;
int ans[MAXN];
int main()
{
    freopen("equal.in","r",stdin);
    freopen("equal.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        cnt[a[i]]++;
    }
    for(int i=1;i<=1000000;i++)
    {
        has[i]=false;
        for(int j=2*i;j<=1000000;j+=i) if(cnt[j]) has[i]=true;
    }
    for(int i=1;i<=1000000;i++)
    {
        if(!cnt[i]) continue;
        v1.push_back(cnt[i]);
        if(has[i]) v2.push_back(cnt[i]);
    }
    for(int i=0;i<=n;i++) ans[i]=(int)v1.size();
    sort(v1.begin(),v1.end()); sort(v2.begin(),v2.end());
    int cur=(int)v1.size(),need=0;
    for(int i=0;i<(int)v2.size();i++)
    {
        for(int j=need;j<need+v2[i];j++) ans[j]=min(ans[j],cur);
        cur--;
        need+=v2[i];
    }
    for(int j=need;j<=n;j++) ans[j]=min(ans[j],cur);
    cur=(int)v1.size()+1,need=0;
    for(int i=0;i<(int)v1.size();i++)
    {
        for(int j=need;j<need+v1[i];j++) ans[j]=min(ans[j],cur);
        cur--;
        need+=v1[i];
    }
    for(int j=need;j<=n;j++) ans[j]=min(ans[j],cur);
    for(int i=0;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}

