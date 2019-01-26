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
int N,T;
int main()
{
    freopen("local.in","r",stdin);
    freopen("local.out","w",stdout);
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        int ans=0;
        scanf("%d",&T);
        for(int j=0;j<T;j++)
        {
            int type,p,q;
            scanf("%d%d",&type,&p);
            if(type==1)
            {
                scanf("%d",&q);
                ans+=p*q;
            }
            else ans+=p;
        }
        printf("Day %d: %d dollars.\n",i,ans);
    }
    return 0;
}

