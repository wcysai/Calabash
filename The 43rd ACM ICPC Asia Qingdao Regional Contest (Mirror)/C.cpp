#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
char s[MAXN],t[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%s",s+1);scanf("%s",t+1);
        int l=-1,r=-1,cnt=0;
        bool f=false;
        for(int i=1;i<=n;i++)
        {
            if(s[i]!=t[i])
            {
                if(!f)
                {
                    f=true;
                    cnt++;
                    l=i;
                }
            }
            else
            {
                if(f)
                {
                    f=false;
                    r=i-1;
                }
            }
        }
        if(f) r=n;
        if(cnt==2) puts("6");
        else if(cnt==0) printf("%lld\n",1LL*(n+1)*n/2);
        else if(cnt>2) puts("0");
        else
        {
            ll ans=0;
            ans+=l-1;ans+=n-r;
            ans+=r-l;
            printf("%lld\n",2*ans);
        }
    }
    return 0;
}