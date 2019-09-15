#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,b;
int sum[MAXN][11];
vector<int> v;
int main()
{
   // memset(sum,0,sizeof(sum));
    for(int i=1;i<=1000000;i++)
    {
        for(int b=2;b<=10;b++)
        {
            sum[i][b]=sum[i-1][b];
            int tmp=i;
            while(tmp) sum[i][b]+=tmp%b,tmp/=b;
        }
    }
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        scanf("%d%d",&N,&b);
        printf("Case #%d: %d\n",tot,sum[N][b]);
    }
}
