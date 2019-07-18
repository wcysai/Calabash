#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll a[MAXN],bas[62];
int n;
vector<ll> masks;
int p2[MAXN];
ll m[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int main()
{
    p2[0]=1;
    for(int i=1;i<=100000;i++) p2[i]=2LL*p2[i-1]%MOD;
    while(scanf("%d",&n)==1)
    {
        memset(bas,0,sizeof(bas));
        masks.clear();
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++)
        {
            bool f=true;
            ll x=a[i],mask=0;
            for(int j=60;j>=0;j--)
            {
                if(x&(1LL<<j))
                {
                    if(!bas[j])
                    {
                        bas[j]=x;
                        m[j]=mask^(1LL<<j);
                        f=false;
                        break;
                    }
                    x^=bas[j];
                    mask^=m[j];
                }
            }
            if(f) masks.push_back(mask);
        }
        int ans=1LL*p2[(int)masks.size()-1]*((int)masks.size())%MOD;
        for(int j=60;j>=0;j--)
        {
            int cnt=0;
            for(auto mask:masks) if(mask&(1LL<<j)) cnt++;
            if(cnt) add(ans,p2[(int)masks.size()-1]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
