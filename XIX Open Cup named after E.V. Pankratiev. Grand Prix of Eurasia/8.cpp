#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int T,n,m,s,a[MAXN],p[MAXN],cnt[MAXN];
const db eps=1e-12;
bool C(db x)
{
    db ans=0;
    for(int i=0;i<n;i++)
    {
        db need=max((db)0,x*cnt[i]-a[i]);
        ans+=need*p[i];
    }
    return ans<=s;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&s);
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<m;i++)
        {
            int x;
            scanf("%d",&x);x--;
            cnt[x]++;
        }
        for(int i=0;i<n;i++) scanf("%d%d",&a[i],&p[i]);
        db l=0,r=1e9+1e5;
        for(int i=0;i<100;i++)
        {
            db mid=(l+r)/2;
            if(C(mid)) l=mid; else r=mid;
        }
        printf("%.12Lf\n",l);
    }
    return 0;
}
