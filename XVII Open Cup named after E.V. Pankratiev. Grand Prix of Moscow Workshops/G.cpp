#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
string str;
int main()
{
    cin>>str;
    int n=(int)str.size();
    int ans=0,lid=-1,rid=-1;
    for(int i=0;i<n;i++)
    {
        if(str[i]=='L') ans++; else { lid=i; break;}
    }
    for(int i=n-1;i>=0;i--)
    {
        if(str[i]=='R') ans++; else {rid=i; break;}
    }
    if(lid>rid||lid==-1||rid==-1) printf("%d\n",ans); else printf("%d\n",ans+1);
    return 0;
}
