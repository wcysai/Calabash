#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int n,m;
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&T);
    int last=1;
    while(T--)
    {
        scanf("%d%d",&n,&m);
        if(n==1) printf("%d\n",last);
        else
        {
            int res;
            if(m==0) res=0; else res=pow_mod(n-1,MOD-2);
            last=1LL*last*res%MOD;
            printf("%d\n",last);
        }
    }
    return 0;
}
