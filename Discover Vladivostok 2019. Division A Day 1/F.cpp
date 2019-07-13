#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int pos[MAXN],p[MAXN];
int n;
string str;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int main()
{
    p[0]=1;
    for(int i=1;i<=100000;i++) p[i]=2LL*p[i-1]%MOD;
    scanf("%d",&n);
    cin>>str;
    for(int i=0;i<n;i++) pos[i+1]=(int)(str[i]-'A'+1);
    int need=2,ans=0;
    bool flag=false;
    for(int i=n;i>=1;i--)
    {
        if(pos[i]==need) continue;
        need=6-pos[i]-need;
        add(ans,p[i-1]);
    }
    printf("%d\n",ans);
    return 0;
}
