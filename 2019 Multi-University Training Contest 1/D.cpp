#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,l[MAXN],s[MAXN],v[MAXN];
double t1[MAXN],t2[MAXN];
double solve(int cur,int to)
{
    if(cur==n) return (double)(to+s[cur])/v[cur];
    return max((double)(to+s[cur])/v[cur],solve(cur+1,to+l[cur+1]));
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=0;i<=n;i++) scanf("%d",&l[i]);
        for(int i=0;i<=n;i++) scanf("%d",&s[i]);
        for(int i=0;i<=n;i++) scanf("%d",&v[i]);
        printf("%.10f\n",solve(0,0));
    }
    return 0;
}
