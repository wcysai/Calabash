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
int n;
void solve(int from,int to,int cnt)
{
    if(cnt==1)
    {
        printf("%d %d\n",from,to);
        return;
    }
    int pos=6-from-to;
    solve(from,pos,cnt-1);
    printf("%d %d\n",from,to);
    solve(pos,to,cnt-1);
}
int main()
{
    scanf("%d",&n);
    solve(1,2,n);
    return 0;
}

