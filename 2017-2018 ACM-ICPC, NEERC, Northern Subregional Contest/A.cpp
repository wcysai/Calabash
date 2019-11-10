#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
int v[3]={1,7,4};
int w[3]={2,3,4};
int n;
int main()
{
    freopen("auxiliary.in","r",stdin);
    freopen("auxiliary.out","w",stdout);
    scanf("%d",&n);
    int ans=0;
    for(int j=0;4*j<=n;j++)
    {
        int rest=n-4*j;
        if(rest%3) continue;
        ans=max(ans,4*j+7*(rest/3));
    }
    for(int j=0;4*j+2<=n;j++)
    {
        int rest=n-4*j-2;
        if(rest%3) continue;
        ans=max(ans,4*j+1+7*(rest/3));
    }
    printf("%d\n",ans);
    return 0;
}
