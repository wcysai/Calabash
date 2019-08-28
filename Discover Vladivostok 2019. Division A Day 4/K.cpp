#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,m;
int q[MAXN];
int main()
{
    scanf("%d%d%d",&n,&k,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d",&q[i]);
        q[i]=n-q[i]+1;
    }
    int most=2*(k+1);
    if(n<=most)
    {
        for(int i=0;i<m;i++)
        {
            if(q[i]==n) printf("%d %d\n",k+1-(n+1)/2,k+1-(n+1)/2);
            else if(n==most&&(q[i]==n-1||q[i]==n-2||q[i]%2==0)) puts("0 1");
            else if((q[i]+n)&1) puts("0 0"); else puts("1 1");
        }
    }
    else if(n==most+1)
    {
        for(int i=0;i<m;i++)
        {
            if(q[i]==n) puts("-1 -1");
            else if(q[i]==n-1) puts("0 0");
            else if(q[i]==most-1||q[i]==most-2||q[i]%2==0) puts("0 1");
            else if((q[i]+n+1)&1) puts("0 0"); else puts("1 1");
        }
    }
    else
    {
        int cur=most,last;
        int base=2;
        while(cur<=n)
        {
            last=cur;
            cur+=base;
            base=base*2;
        }
        for(int i=0;i<m;i++)
        {
            if(q[i]<=last-base/4) puts("0 1");
            else if(q[i]<=last) puts("0 0");
            else puts("-1 -1");
        }
    }
    return 0;
}
