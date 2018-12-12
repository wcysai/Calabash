#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,k,a[8];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        int ans=INF;
        scanf("%d",&k);
        int s=0;
        for(int i=1;i<=7;i++)
        {
            scanf("%d",&a[i]);s+=a[i];
        }
        for(int i=1;i<=7;i++)
        {
            if(a[i]!=1) continue;
            int cnt=0;
            cnt=(k-1)/s*7+1;
            int now=(k-1)%s,cur=i;
            while(now>0)
            {
                cur++;if(cur>7) cur=1;
                now-=a[cur];cnt++;
            }
            ans=min(ans,cnt);
        }
        printf("%d\n",ans);
    }
    return 0;
}
