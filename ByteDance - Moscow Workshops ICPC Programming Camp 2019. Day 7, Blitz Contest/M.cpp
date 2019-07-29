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
int w,h,n;
int main()
{
    while(scanf("%d%d%d",&w,&h,&n)==3)
    {
        if(!w&&!h&&!n) break;
        if(!n) puts("1");
        else if(n==1)
        {
            int ans=w*(w+1)/2*h*(h+1)/2+1;
            printf("%d\n",ans);
        }
        else
        {
            int now=w*(w+1)/2*h*(h+1)/2;
            int ans=(now*now-now)/2;
            for(int i=1;i<=w;i++)
            {
                for(int j=1;j<=h;j++)
                {
                    int cnt=0,cnt2=0,cnt3=0;
                    cnt+=i-1;cnt+=j-1;
                    cnt+=w-i;cnt+=h-j;
                    cnt2+=6*(i-1)*(j-1);
                    int len1=w-i,len2=h-j;
                    for(int k=0;k<=len1;k++)
                        for(int l=0;l<=len2;l++)
                        {
                            cnt3+=k*(len1-k);
                            cnt3+=l*(len2-l);
                        }
                    ans-=cnt*(w-i+1)*(h-j+1);
                    ans-=2*cnt2*(w-i+1)*(h-j+1);
                    ans-=2*cnt3;
                }
            }
            printf("%d\n",ans+now+1);
        }
    }
    
    return 0;
}

