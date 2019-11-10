#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x[MAXN],y[MAXN];
int minx,maxx,miny,maxy,ans;
int getdis(int i,int j)
{
    return max(x[i]-x[j],x[j]-x[i])+max(y[i]-y[j],y[j]-y[i]);
}
int main()
{
    freopen("intel.in","r",stdin);
    freopen("intel.out","w",stdout);
    ans=0;
    minx=miny=INF; maxx=maxy=-INF;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        minx=min(minx,x[i]); maxx=max(maxx,x[i]);
        miny=min(miny,y[i]); maxy=max(maxy,y[i]);
        if(i>1) ans+=getdis(i,i-1);
    }
    ans+=getdis(1,n);
    ans-=2*(maxx-minx)+2*(maxy-miny);
    printf("%d\n",ans);
    return 0;
}
