#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 4005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<2001> bs;
int T,n,m;
int d[MAXN][MAXM];
bs b[1001];
bs dp[1001];
int main()
{
    scanf("%d",&T);
    dp[0].set(0);
    for(int i=0;i<1000;i++)
        for(int j=1;i+j<=1000;j++)
            for(int k=1;j*k+i<=1000;k++)
                dp[i+(j*k)]|=dp[i]<<(j+k);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        if(m&1) {puts("No"); continue;}
        m/=2;
        if(!dp[n].test(m)) {puts("No"); continue;}
        vector<P> ans; ans.clear();
        while(n)
        {
            bool f=false;
            for(int i=1;i<=n;i++)
            {
                if(f) break;
                for(int j=1;i*j<=n;j++)
                    if(i+j<=m)
                    {
                        if(dp[n-i*j].test(m-(i+j)))
                        {
                            ans.push_back(P(i,j));
                            m-=i+j;
                            n-=i*j;
                            f=true;
                            break;
                        }
                    }
            }
            assert(f);
        }
        puts("Yes");
        printf("%d\n",(int)ans.size());
        for(auto p:ans) printf("%d %d\n",p.F,p.S);
    }
    return 0;
}
