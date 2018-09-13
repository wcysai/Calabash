/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-06-15 20:49:22
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<double,string> P;
int n;
double x[MAXN],y[MAXN];
set<P> s;
string str[MAXN];
int main()
{
    scanf("%d",&n);
    string str1,str2,str3,str4;
    string tmp[3];
    double ans=1e9;
    for(int i=0;i<n;i++)
    {
        cin>>str[i];
        scanf("%lf%lf",&x[i],&y[i]);
        s.insert(P(y[i],str[i]));
    }
    for(int i=0;i<n;i++)
    {
        s.erase(P(y[i],str[i]));
        int cnt=0;
        double res=0;
        res+=x[i];
        for(auto j=s.begin();j!=s.end();j++)
        {
            cnt++;
            tmp[cnt-1]=(*j).S;
            res+=(*j).F;
            if(cnt==3) break;
        }
        if(res<ans)
        {
            str1=str[i];
            str2=tmp[0];
            str3=tmp[1];
            str4=tmp[2];
            ans=res;
        }
        s.insert(P(y[i],str[i]));
    }
    printf("%.10f\n",ans);
    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str3<<endl;
    cout<<str4<<endl;
    return 0;
}
