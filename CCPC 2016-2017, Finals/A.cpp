#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN];
int main()
{
    scanf("%d",&t);
    int kase=0;
    while(t--)
    {
        kase++;
        printf("Case #%d: ",kase);
        scanf("%d",&n);
        int sum=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        sort(a,a+n);
        for(int i=n-3;i>=0;i-=3)
            sum-=a[i];
        printf("%d\n",sum);
    }
    return 0;
}
