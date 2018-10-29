#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int n,a[MAXN];
string str;
int main()
{
    cin>>str;n=str.size();
    for(int i=0;i<(int)str.size();i++)
        if(str[i]=='1') a[n-1-i]++;
    cin>>str;n=str.size();
    for(int i=0;i<(int)str.size();i++)
        if(str[i]=='1') a[n-1-i]++;
    for(int i=0;i<=2000000;i++)
        if(a[i]>=2)
        {
            a[i+2]+=a[i]/2;a[i+3]+=a[i]/2;
            a[i]%=2;
        }
    bool f=false;
    for(int i=2000000;i>=0;i--)
    {
        if(a[i]) f=true;
        if(f) printf("%d",a[i]);
    }
    if(!f) puts("0");
    return 0;
}
