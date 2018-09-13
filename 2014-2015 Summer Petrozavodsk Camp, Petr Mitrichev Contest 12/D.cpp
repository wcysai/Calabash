/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-31 16:01:12
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
int n,m;
char a[55],b[55];
map<ll,int> mp[105];
//mp[i][mask]:string length i, 
//j-th bit in mask set to 1=> 
//string can be formed by interleaving first j chars in a and first i-j chars in b
//the map saves the number of such strings
//it can be conjectured the number of reachable states won't be too many
int main()
{
    freopen("interleave.in","r",stdin);
    freopen("interleave.out","w",stdout);
    scanf("%s%s",a,b);
    n=strlen(a);m=strlen(b);
    for(int i=0;i<=n+m;i++) mp[i].clear();
    mp[0][1]=1;
    for(int i=0;i<n+m;i++)
    {
        for(auto it=mp[i].begin();it!=mp[i].end();it++)
        {
            ll s=it->F,t=it->S;
            for(int j=0;j<2;j++)
            {
                ll u=0;char ch=j+'0';
                for(int k=0;k<=n;k++)
                {
                    if(s>>k&1)
                    {
                        if(k<n&&a[k]==ch) u|=1LL<<k+1;
                        if(i-k<m&&b[i-k]==ch) u|=1LL<<k;
                    }
                }
                mp[i+1][u]=(mp[i+1][u]+t)%MOD;
            }
        }
    }
    printf("%d\n",mp[n+m][1LL<<n]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
