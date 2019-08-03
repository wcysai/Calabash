#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
string str;
string tt;
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        cin>>str;
        n=(int)str.size();
        cin>>tt;
        int d=0,w=0,h=0;
        for(int i=0;i<n;i++)
        {
            if(tt[str[i]-'a']=='d') d++;
            else if(tt[str[i]-'a']=='w') w++;
            else h++;
        }
        printf("Case #%d: ",t);
        if(4*h>=n) puts("Harmful");
        else if(10*h<=n) puts("Recyclable");
        else if(w*2<=d) puts("Dry"); else puts("Wet");
    }
    return 0;
}
