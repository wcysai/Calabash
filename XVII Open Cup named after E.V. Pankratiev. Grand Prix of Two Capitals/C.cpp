#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,l,r;
string str;
int main()
{
    scanf("%d%d%d",&n,&l,&r);
    for(int i=0;i<(r-l+1)/2;i++) str+="[]";
    int a=l-1,b=n-r;
    while(a>b) str="()"+str,a-=2;
    while(b>a) str=str+"()",b-=2;
    while(a) str="("+str+")",a--;
    cout<<str<<endl;
    return 0;
}
