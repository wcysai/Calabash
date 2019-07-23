#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef __int128_t ll;
typedef pair<int,int> P;
int N; 
long long cnt[MAXN];
ll add;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        int x;
        long long y;
        scanf("%d%lld",&x,&y);
        if(x>1000000)
        {
            puts("No");
            return 0;
        }
        cnt[x]+=y;
    }
    for(int i=1000000;i>=2;i--)
    {
        if((cnt[i]+add)%i)
        {
            puts("No");
            return 0;
        }
        add+=(cnt[i]+add)/i;
    }
    puts("Yes");
    return 0;
}
