#include<bits/stdc++.h>
#define MAXN 5000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p,q,m;
unsigned int SA,SB,SC;
unsigned int rng61()
{
    SA^=SA<<16;
    SA^=SA>>5;
    SA^=SA<<1;
    unsigned int t=SA; SA=SB;
    SB=SC;
    SC^=t^SA;
    return SC;
}
int T,t;
unsigned int st[MAXN],maxi[MAXN];
void PUSH(unsigned int x)
{
    st[t]=x;
    if(!t) maxi[t]=st[t]; else maxi[t]=max(maxi[t-1],st[t]);
    t++;
}
void POP()
{
    if(t) t--;
}
unsigned int getans()
{
    if(t==0) return 0; else return maxi[t-1];
}
int main()
{
    scanf("%d",&T);
    for(int _=1;_<=T;_++)
    {
        ll ans=0;
        t=0;
        scanf("%d%d%d%d%u%u%u",&n,&p,&q,&m,&SA,&SB,&SC);
        for(int i=1;i<=n;i++)
        {
            if(rng61()%(p+q)<p) PUSH(rng61()%m+1); else POP();
            ans^=1LL*i*getans();
        }
        printf("Case #%d: %lld\n",_,ans);
    }
    return 0;
}
