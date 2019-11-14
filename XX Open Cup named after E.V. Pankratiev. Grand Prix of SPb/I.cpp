#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
string s,t;
int n,m,now;
int parity=0;
int main()
{
    cin>>s;
    cin>>t;
    n=(int)s.size(); m=(int)t.size();
    if((n&1)!=(m&1)) {puts("NO"); return 0;}
    for(int i=0;i<m;i++)
    {
        if(((i&1)==parity)&&(s[now]==t[i]))
        {
            now++;
            if(now==n) break;
            parity^=1;
        }
    }
    if(now==n) puts("YES"); else puts("NO");
    return 0;
}
