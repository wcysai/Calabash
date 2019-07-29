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
int n,k,a[MAXN];
int perm[MAXN],p[MAXN],q[MAXN];
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) perm[i]=i;
        bool f=false;
        for(int iter=0;iter<100;iter++)
        {
            random_shuffle(perm+1,perm+n+1);
            for(int j=1;j<=n;j++) p[j]=a[perm[j]];
            for(int j=1;j<=n;j++) q[j]=perm[a[j]];
            for(int j=1;j<=n;j++)
            {
                if(p[j]!=q[j])
                {
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(f)
        {
            puts("Yes");
            for(int j=1;j<=n;j++) printf("%d%c",perm[j],j==n?'\n':' ');
        }
        else puts("No");
    }
    return 0;
}
