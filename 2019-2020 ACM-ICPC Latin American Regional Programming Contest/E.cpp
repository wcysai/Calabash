#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
int n,k;
ll ans;
int main()
{
    cin>>str;
    scanf("%d",&k);
    n=(int)str.size();
    ans=1LL*n*min(k,n);
    if(k>=n) ans-=(n-1);
    int pos=-1;
    for(int i=0;i<n;i++)
    {
        if(str[i]=='E') {pos=i; break;}
    }
    if(pos==-1) {puts("0"); return 0;}
    int cnt=0;
    for(int i=0;i<n-1;i++)
    {
        pos=(pos+1)%n;
        if(str[pos]=='P') cnt++;
        else
        {
            if(cnt>=k) ans-=1LL*(2*cnt-k+1)*k/2;
            else ans-=1LL*(cnt+1)*cnt/2;
            cnt=0;
        }
    }
    if(cnt>=k) ans-=1LL*(2*cnt-k+1)*(k)/2;
    else ans-=1LL*(cnt+1)*cnt/2;
    printf("%lld\n",ans);
}
