#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int k,n,m,a[MAXN],ans[MAXN];
int main()
{
    scanf("%d%d%d",&k,&n,&m);
    for(int i=1;i<=k;i++) scanf("%d",&a[i]);
    a[k+1]=INF+1;
    if(a[1]==-1) a[1]=1;
    for(int i=2;i<=k;i++) if(a[i]==-1) a[i]=a[i-1];
    for(int i=2;i<=k;i++)
    {
        if(a[i]<a[i-1])
        {
            puts("-1");
            return 0;
        }
    }
    if(n<k) {puts("-1"); return 0;}
    for(int i=n-k+1;i<=n;i++) ans[i]=a[i-n+k];
    int cur=1,lim=n-k;
    for(int i=m;i>=1;i--)
    {
        if(cur>lim) break;
        int has=lower_bound(a+1,a+k+2,i)-a-1;
        if(has==0) {puts("-1"); return 0;}
        for(int j=cur;j<=min(cur+has-1,lim);j++) ans[j]=i;
        cur=min(cur+has-1,lim)+1;
    }
    //if(cur<=lim) {puts("-1"); return 0;}
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}
