#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,now;
string str;
int main()
{
    scanf("%d",&n);now=0;
    for(int i=0;i<n;i++)
    {
        cin>>str;
        if(str[0]=='L') now^=1;
    }
    if(now) puts("LIE"); else puts("TRUTH");
    return 0;
}
