#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k;
vector<int> ans[MAXN];
int save[3][MAXN];
void go()
{
    for(int i=1;i<=k;i++)
    {
        for(auto x:ans[i]) printf("%d ",x);
        puts("");
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        if(n==1&&k==1)
        {
            puts("yes");
            puts("1");
            continue;
        }
        if(n==k)
        {
            puts("no");
            continue;
        }
        if((1LL*n*(n+1)/2)%k!=0)
        {
            puts("no");
            continue;
        }
        puts("yes");
        for(int i=1;i<=k;i++) ans[i].clear();
        int round=n/k;
        if(round%2==0)
        {
            for(int i=1;i<=round;i++)
            {
                if(i&1) for(int j=1;j<=k;j++) ans[j].push_back((i-1)*k+j);
                else for(int j=1;j<=k;j++) ans[j].push_back(i*k+1-j);
            }
        }
        else
        {
            assert(k&1);
            for(int i=1;i<=round-3;i++)
            {
                if(i&1) for(int j=1;j<=k;j++) ans[j].push_back((i-1)*k+j);
                else for(int j=1;j<=k;j++) ans[j].push_back(i*k+1-j);
            }
            int cur=k/2;
            for(int i=1;i<=k;i++)
            {
                save[0][i]=cur;
                cur--;
            }
            cur=0;
            for(int i=1;i<=(k+1)/2;i++)
            {
                save[1][i]=cur;
                cur--;
            }
            cur=k/2;
            for(int i=(k+1)/2+1;i<=k;i++)
            {
                save[1][i]=cur;
                cur--;
            }
            for(int i=1;i<=k;i++) save[2][i]=0-save[0][i]-save[1][i];
            for(int i=0;i<3;i++)
            {
                int offset=(k+1)/2+(round-3+i)*k;
                for(int j=1;j<=k;j++) ans[j].push_back(offset+save[i][j]);
            }
        }
        go();
    }
    return 0;
}
