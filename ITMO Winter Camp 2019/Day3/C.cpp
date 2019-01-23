#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
int f[MAXN],g[MAXN];
vector<P> v;
bool flag;
int main()
{
    freopen("bandits.in","r",stdin);
    freopen("bandits.out","w",stdout);
    scanf("%d%d",&k,&n);
    if(k==1) printf("%d\n",n);
    else if(k==2) puts("-1");
    else
    {
        f[1]=1;f[2]=1;f[3]=n+1;
        for(int i=4;i<=k;i++)
        {
            for(int j=1;j<=i-1;j++) g[j]=f[j];
            v.clear();
            for(int j=1;j<=i-1;j++) v.push_back(P(f[j],j));
            sort(v.begin(),v.end());
            int sum=0;
            int last=v[i/2-1].F;
            if(v[i/2].F==last) flag=true; else flag=false;
            for(int j=0;j<i/2;j++) 
            {
                sum+=v[j].F;
                if(!flag||v[j].F!=last) f[v[j].S]=v[j].F+1; else f[v[j].S]=1;
            }
            for(int j=i/2;j<i-1;j++) f[v[j].S]=1;
            if(sum>n) 
            {
                f[i]=0;
                for(int j=1;j<=i-1;j++) f[j]=g[j];
            }
            else f[i]=n-sum+1;
        }
        printf("%d\n",f[k]-1);
    }
    return 0;
}

