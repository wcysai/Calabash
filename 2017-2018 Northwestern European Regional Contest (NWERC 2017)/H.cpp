//
// Created by sy-chen on 18-5-31.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef unsigned long long ull;
typedef pair<int,int> P;
long long n,a,b,c,d;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a>>b>>c>>d;
        ull ans;
        if(d<=30)
        {
            ans=0;
            for(int i=0;i<=d;i++)
                for(int j=0;i+j<=d;j++)
                    for(int k=0;i+j+k<=d;k++)
                        ans=max(ans,(ull)(a+i)*(a+i)+(b+j)*(b+j)+(c+k)*(c+k)+7*min(min(a+i,b+j),c+k));
        }
        else
        {
            if(a>=b&&a>=c) a+=d;
            else if(b>=a&&b>=c) b+=d;
            else c+=d;
            ans=(ull)a*a+(ull)b*b+(ull)c*c+7*min(a,min(b,c));
        }
        cout<<ans<<endl;
    }
    return 0;
}
