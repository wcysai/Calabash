#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,x,y;
int a[MAXN][MAXN];
string getpath(int n,int m)
{
    string t="";
    if(n&1)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m-1;j++) if(i&1) t+='R'; else t+='L';
            if(i!=n) t+='D';
        }
    }
    else
    {
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n-1;j++) if(i&1) t+='D'; else t+='U';
            if(i!=m) t+='R';
        }
    }
    return t;
}
string rotate(string str)
{
    string t="";
    for(int i=0;i<(int)str.size();i++)
    {
        if(str[i]=='R') t+='D';
        else if(str[i]=='D') t+='R';
        else if(str[i]=='U') t+='L';
        else t+='U';
    }
    return t;
}
string construct_ans(int n,int m)
{
    if(n==2&&m==2) return "DR";
    if(m==2)
    {
        string t="DRDLD";
        t+=getpath(n-3,m);
        return t;
    }
    string t="DRRUR";
    t+=getpath(2,m-3);
    if(n==2) return t;
    else
    {
        t+="D";
        for(int i=1;i<=m-1;i++) t+="L";
        t+="D";
        t+=getpath(n-3,m);
        return t;
    }
}
string ans;
int main()
