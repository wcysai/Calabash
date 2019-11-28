#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int N,X,a[MAXN];
int main()
{
    scanf("%d%d",&N,&X);
    for(int i=1;i<=N;i++) scanf("%d",&a[i]);
    int ans=0,cnt=0;
    for(int i=1;i<=N;i++)
    {
        if(i==1||a[i]-a[i-1]<=X) cnt++;
        else cnt=1;
        ans=max(ans,cnt);
    }
    printf("%d\n",ans);
    return 0;
}
