#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int a[30];
vector<int> ans[(1<<22)+1];
int T,d1,d2,d3,d4,n;
void dfs(int now)
{
    if(now>=2&&a[now]<(1<<(now-2))) return;
    if(now>25) return;
    if(__builtin_popcount(a[now])<=4&&(!ans[a[now]].size()||now<(int)ans[a[now]].size()))
    {
        ans[a[now]].clear();
        ans[a[now]]=vector<int>(a,a+now+1);
    }
    for(int i=0;i<=now;i++)
    {
        a[now+1]=a[now]+a[i];
        if(a[now+1]>(1<<22)) break;
        dfs(now+1);
    }
}
int main()
{
    a[0]=1;
    dfs(0);
    for(int i=1;i<(1<<22);i++)
    {
        if(__builtin_popcount(i)>4||ans[i].size()) continue;
        int j;
        for(j=0;(1<<j)<=i;j++) ans[i].push_back(1<<j);
        j--;
        int now=1<<j;
        for(int k=0;k<j;++k)
        {
            if((i>>k)&1)
            {
                now|=1<<k;
                ans[i].push_back(now);
            }
        }
    }
    freopen("dividing.in","r",stdin);
    freopen("dividing.out","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&d1,&d2,&d3,&d4);
        n=(1<<d1)+(1<<d2)+(1<<d3)+(1<<d4);
        printf("%d\n",(int)ans[n].size()-1);
        for(int i=(int)ans[n].size()-1;i>=1;i--) printf("%d %d %d\n",ans[n][i],ans[n][i-1],ans[n][i]-ans[n][i-1]);
    }
    return 0;
}
