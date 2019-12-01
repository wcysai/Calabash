#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
int n;
int main()
{
    cin>>str;
    n=(int)str.size();
    int l=0,r=n-1;
    while(l<=r)
    {
        if(str[l]!=str[r]) {puts("0"); return 0;}
        int cnt=0;
        char ch=str[l];
        while(r>l&&str[r]==ch) {cnt++; r--;}
        while(r>l&&str[l]==ch) {cnt++; l++;}
        if(l==r&&str[l]==ch)
        {
            if(cnt==0) puts("0");
            else printf("%d\n",cnt+2);
            return 0;
        }
        else if(cnt<3) {puts("0"); return 0;}
    }
    return 0;
}
