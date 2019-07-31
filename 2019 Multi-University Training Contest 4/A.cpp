#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        bool f=true;
        if(__builtin_popcount(N+1)==1)
        {
            puts("1");
            f=false;
        }
        else puts("0");
        for(int i=2;i<=N;i++)
        {
            if(!f&&(i==N)) printf("1");
            else
            {
                for(int j=0;;j++)
                {
                    if(!((i>>j)&1))
                    {
                        printf("%d",(1<<j));
                        break;
                    }
                }
            }
            printf("%c",i==N?'\n':' ');
        }
    }
    return 0;
}
