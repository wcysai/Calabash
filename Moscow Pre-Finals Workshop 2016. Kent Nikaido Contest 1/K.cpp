#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],sum;
int main()
{
    scanf("%d",&n);
    int minx=INF;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        minx=min(minx,a[i]);
        sum+=a[i];
    }
    if(n&1)
    {
        if(sum&1) puts("Iori"); else puts("Yayoi");
    }
    else
    {
        if(minx&1) puts("Iori"); 
        else 
        {
            if(sum&1) puts("Iori"); else puts("Yayoi");
        }
    }
    return 0;
}
