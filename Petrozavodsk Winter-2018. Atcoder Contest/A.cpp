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
int n,k,a[MAXN];
string str;
int ask(int x)
{
    printf("%d\n",x);fflush(stdout);
    cin>>str;
    if(str=="Vacant") exit(0);
    if(str=="Male") return 0; else return 1;
}
void solve(int l,int r,int cur)
{
    assert(l<=r);
    int len=(r-l+1);
    int mid=(l+r)/2;
    int now=ask(mid);
    int rest=(len-1)/2;
    if(rest&1)
    {
        if(now==cur) solve(mid+1,r,now);
        else solve(l,mid-1,cur);
    }
    else
    {
        if(now==cur) solve(l,mid-1,cur);
        else solve(mid+1,r,now);
    }
}
int main()
{
    scanf("%d",&n);
    int now=ask(0);ask(n-1);
    solve(1,n-2,now);
    return 0;
}

