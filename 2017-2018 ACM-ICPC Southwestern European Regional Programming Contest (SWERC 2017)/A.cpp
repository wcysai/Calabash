//
// Created by calabash_boy on 18-5-29.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,x;
int a[MAXN],b[MAXN];
map<int,int> mp;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<m;i++)
        scanf("%d",&b[i]);
    for(int i=0;i<n;i++)
    {
        for (int j = 0; j < m; j++)
        {
            int d = b[j] - a[i];
            if (d >= 0)
            {
                if (mp.find(d) == mp.end()) mp[d] = 1;
                else mp[d]++;
            }
        }
    }
    int res=-1,ans=0;
    for(auto it=mp.begin();it!=mp.end();it++)
    {
        if(it->S>res)
        {
            ans=it->F;
            res=it->S;
        }
        else if(it->S==res&&it->F<ans) ans=it->F;
    }
    printf("%d\n",ans);
    return 0;
}
