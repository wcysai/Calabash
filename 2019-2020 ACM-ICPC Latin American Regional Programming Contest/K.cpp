#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N;
string str;
vector<ll> v;
void mult(int val)
{
    int sz=(int)v.size();
    v.resize(sz+1); v[sz]=0;
    for(int i=sz;i>=0;i--)
    {
        v[i]=v[i]*val;
        if(i!=0) v[i]-=v[i-1];
    }
}
int main()
{
    cin>>str;
    N=(int)str.size();
    v.push_back(1);
    for(int i=1;i<N;i++)
    {
        if(str[i]!=str[i-1]) mult(2*i+1);
    }
    printf("%d\n",(int)v.size()-1);
    for(int i=(int)v.size()-1;i>=0;i--) if(str[0]=='A') printf("%lld%c",-v[i],i==0?'\n':' '); else printf("%lld%c",v[i],i==0?'\n':' ');
    return 0;
}
