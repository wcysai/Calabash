#include<bits/stdc++.h>
#define MAXN 1005
#define INF 2000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int res=INF;
        for(int j=1;j<=n;j++) res=min(res,max(a[i]-b[j],b[j]-a[i]));
        ans=max(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}
