/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-16 12:22:36
 ************************************************************************/

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
ll T,n;
string str;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        cin>>str;
        n=str.size();
        ll change=0,unchange=1;
        ll ans=0;
        for(ll i=1;i<=n;i++) ans+=(n-i+1)*i;
        for(ll i=0;i<n;i++)
        {
            if(str[i]=='0')
            {
                ans+=unchange*(n-i);
                unchange+=change+1;change=0;
            }
            else
            {
                ans+=change*(n-i);
                change+=unchange;unchange=1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

