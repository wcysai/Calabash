#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string s,t;
int q,n,m;
vector<int> kmp(string a,string b) // a=pattern, b=text
{
    int n=a.size();
    vector<int> next(n+1,0);
    for(int i=1;i<n;++i)
    {
        int j=i;
        while(j>0)
        {
            j=next[j];
            if(a[j]==a[i])
            {
                next[i+1]=j+1;
                break;
            }
        }
    }
    vector<int> p;//p=positions
    int m=b.size();
    for(int i=0,j=0;i<m;++i)
    {
        if(j<n&&b[i]==a[j])
        {
            j++;
        }
        else
        {
            while(j>0)
            {
                j=next[j];
                if(b[i]==a[j])
                {
                    j++;
                    break;
                }
            }
        }
        if(j==n)
        {
            p.push_back(i-n+1);
        }
    }
    return p;
}
int main()
{
    cin>>s;
    n=(int)s.size();
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        cin>>t;
        m=(int)t.size();
        if(n>m)
        {
            if(kmp(t,s).size()) puts("my child!"); else puts("oh, child!");
        }
        else if(n==m)
        {
            if(kmp(t,s).size()) puts("jntm!"); else puts("friend!");
        }
        else
        {
            if(kmp(s,t).size()) puts("my teacher!"); else puts("senior!");
        }
    }
    return 0;
}
