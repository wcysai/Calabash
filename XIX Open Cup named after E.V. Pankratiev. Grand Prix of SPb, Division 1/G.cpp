#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int N,d;
bool check(int digit,int sum,int banned)
{
    if(digit==0&&sum!=0) return false;
    if(digit==1&&sum==banned) return false;
    if(digit*9<sum) return false;
    if(banned==9&&digit*8<sum) return false;
    if(banned==0&&sum<digit) return false;
    if(banned==1&&sum==1) return false;
    if(banned==8&&digit*9-1==sum) return false;
    return true;
}
vector<int> ans;
int main()
{
    scanf("%d%d",&N,&d);
    int l=0,r=N;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        bool f=false;
        for(int i=1;i<=9;i++)
        {
            if(i==d) continue;
            if(check(mid-1,N-i,d)) f=true;
        }
        if(f) r=mid; else l=mid;
    }
    int dig=r;
    for(int i=1;i<=dig;i++)
    {
        int j=(i==1?1:0);
        for(;j<=9;j++)
        {
            if(j==d) continue;
            if(check(r-1,N-j,d))
            {
                ans.push_back(j);
                r--;N-=j;
                break;
            }
        }
    }
    assert(N==0);
    for(int i=0;i<(int)ans.size();i++) printf("%d",ans[i]);
    return 0;
}
