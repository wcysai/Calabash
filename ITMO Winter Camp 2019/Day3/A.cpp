#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,a[MAXN][MAXN];
int main()
{
    freopen("cut.in","r",stdin);
    freopen("cut.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    if(n*m%k!=0) {puts("-1"); return 0;}
    int now=1,cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(i&1)
        {
            for(int j=1;j<=m;j++)
            {
                a[i][j]=now;
                cnt++; if(cnt==k) {cnt=0; now++;}
            }
        }
        else
        {
            for(int j=m;j>=1;j--)
            {
                a[i][j]=now;
                cnt++; if(cnt==k) {cnt=0; now++;}
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            printf("%d%c",a[i][j],j==m?'\n':' ');
    return 0;
}

