#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,C,p[MAXN],d[MAXN],v[MAXN];
int main()
{
    scanf("%d%d",&n,&C);
    int ans=INF; 
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&p[i],&d[i],&v[i]);
        ans=min(ans,p[i]+d[i]+v[i]*C);
    }
    printf("%d\n",ans);
    return 0;
}

