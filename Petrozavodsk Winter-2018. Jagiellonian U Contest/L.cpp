#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,k;
string s,t;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        cin>>s;cin>>t;
        int ans=0,cnt=0,l1,l2,now;
        for(int st=0;st<m;st++)
        {
            l1=0;l2=st;cnt=0;now=0;
            while(l1<n&&l2<m)
            {
                while(l1+now<n&&l2+now<m&&cnt<=k)
                {
                    if(s[l1+now]!=t[l2+now]) cnt++;
                    now++;
                    if(cnt>k) break;
                }
                if(cnt>k) ans=max(ans,now-1); else ans=max(ans,now);
                if(s[l1]!=t[l2]) cnt--;
                l1++;l2++;now--;
            }
        }
        for(int st=0;st<n;st++)
        {
            l1=st;l2=0;cnt=0;now=0;
            while(l1<n&&l2<m)
            {
                while(l1+now<n&&l2+now<m&&cnt<=k)
                {
                    if(s[l1+now]!=t[l2+now]) cnt++;
                    now++;
                    if(cnt>k) break;
                }
                if(cnt>k) ans=max(ans,now-1); else ans=max(ans,now);
                if(s[l1]!=t[l2]) cnt--;
                l1++;l2++;now--;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

