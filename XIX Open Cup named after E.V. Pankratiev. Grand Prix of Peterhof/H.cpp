#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int main()
{
    int l=1,r=INF;
    for(int i=1;i<=100;i++)
    {
        int x;scanf("%d",&x);
        int mid=(l+r)/2;
        if(l==r&&x==r)
        {
            printf("=\n"); fflush(stdout);
            return 0;
        }
        if(x<=mid) 
        {
            printf(">\n"); fflush(stdout);
            l=max(l,x+1);
        }
        else
        {
            printf("<\n"); fflush(stdout);
            r=min(r,x-1);
        }
    }
    return 0;
}
