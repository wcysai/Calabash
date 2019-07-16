#include<bits/stdc++.h>
#define MAXN 6005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<6000> bs;
int n;
bs b[MAXN];
bool f[MAXN];
bs bas[MAXN];
char str[MAXN];
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=0;i<n;i++)
        {
            b[i].reset();
            scanf("%s",str);
            int m=strlen(str);
            for(int j=0;j<m;j++)
            {
                int x=(int)str[j]-48;
                for(int k=6*j;k<6*(j+1);k++)
                {
                    if(x&1) b[i].set(k);
                    x>>=1;
                }
            }
        }
        for(int i=0;i<n;i++) f[i]=false;
        int r=0;
        for(int i=0;i<n;i++)
        {
            for(int j=b[i]._Find_first();j<(int)b[i].size();j=b[i]._Find_next(j))
            {
                if(!f[j])
                {
                    bas[j]=b[i];
                    f[j]=true;
                    r++;
                    break;
                }
                b[i]^=bas[j];
            }
            if(r>=35) break;
        }
        double ans=0.5,t=0.5;
        for(int i=0;i<r;i++) t*=0.5;
        ans-=t;
        printf("%.10f\n",ans);
    }
    return 0;
}
