#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,K,a[MAXN];
int main()
{
    scanf("%d%d",&n,&K);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    sort(a,a+n);
    int ans=1,last=a[n-1];
    for(int i=n-2;i>=0;i--)
    {
        if(last-a[i]>K) break;
        else {ans++; last=a[i];}
    }
    printf("%d\n",ans);
    return 0;
}
