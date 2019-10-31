#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 2000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
int maxi[MAXN],mini[MAXN],dp[MAXN],st[MAXN],s1,t1,s2,t2,s3,t3,opt;
int get_res(int id)
{
    while(maxi[s1]<=id&&s1<t1) s1++;
    while(mini[s2]<=id&&s2<t2) s2++;
    while(st[s3]<id&&s3<t3) s3++;
    return max(dp[st[s3]],a[maxi[s1]]-a[mini[s2]]);
}
int main()
{
    scanf("%d%d",&n,&k);
    s1=t1=s2=t2=0; t3=1;
    int tmp=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        a[i]^=tmp;
        while(s1<t1&&a[maxi[t1-1]]<=a[i]) t1--;
        maxi[t1++]=i;
        while(s2<t2&&a[mini[t2-1]]>=a[i]) t2--;
        mini[t2++]=i;
        if(i<k) {dp[i]=INF; tmp=0;}
        else
        {
            int last=i-k;
            while(s3<t3&&dp[st[t3-1]]>=dp[last]) t3--;
            st[t3++]=last;
            int curval=max(dp[st[s3]],a[maxi[s1]]-a[mini[s2]]);
            while(opt<last)
            {
                int _s1=s1,_s2=s2,_s3=s3;
                int nxtval=get_res(opt+1);
                if(nxtval<=curval) {curval=nxtval; opt++;}
                else {s1=_s1; s2=_s2; s3=_s3; break;}
            }
            dp[i]=tmp=curval;
        }
    }
    for(int i=1;i<=n;i++) if(dp[i]==INF) puts("0"); else printf("%d\n",dp[i]);
    return 0;
}
