#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll x;
vector<int> a;
string str;
int n;
ll ans,num,res;
void dfs(int now,ll cur,int mask)
{
    if(now==n)
    {
        ll ab=max(cur-x,x-cur);
        if(min(ab,num-ab)>ans)
        {
            ans=min(ab,num-ab);
            res=cur;
        }
    }
    for(int i=0;i<=9;i++)
        if(!(mask&(1<<i)))
            dfs(now+1,cur*10+i,mask|(1<<i));
}
int main()
{
    cin>>str;
    n=(int)str.size();
    x=0; num=1;
    for(int i=0;i<n;i++) x=10*x+(str[i]-'0');
    for(int i=0;i<n;i++) num=num*10;
    ans=0;
    dfs(0,0,0);
    int cnt=0;
    ll tmp=res;
    while(tmp)
    {
        cnt++;
        tmp/=10;
    }
    if(cnt==n) printf("%lld\n",res); else printf("0%lld\n",res);
    return 0;
}
}
