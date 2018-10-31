#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
vector<bool> v;

int main()
{
    cin>>str;
    int n=str.size();
    bool f=true;
    v.resize(n);
    for(int i=n-1;i>=0;i--)
    {
        v[i]=f;
        if(str[i]!='9') f=false;
    }
    int cur=9;
    for(int i=0;i<n;i++)
    {
        if(str[i]=='0') continue;
        if(v[i]) cur=min(cur,max(1,str[i]-'0'));
        else cur=min(cur,max(1,str[i]-'0'-1));
    }
    printf("%d\n",cur);
    return 0;
}
