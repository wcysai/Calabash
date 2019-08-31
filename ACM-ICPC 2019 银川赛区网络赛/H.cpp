#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
int cnt[MAXN],need[MAXN],atk[MAXN],hp[MAXN];
int id[MAXN];
bool cmp(int x,int y)
{
    return 1LL*need[y]*atk[x]>1LL*need[x]*atk[y];
}
int main()
{
    for(int i=1;i<=500;i++) cnt[i]=cnt[i-1]+i;
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        scanf("%d",&n);
        ll ans=0,sum=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&hp[i],&atk[i]); sum+=atk[i];
            need[i]=lower_bound(cnt+1,cnt+501,hp[i])-cnt;
        }
        for(int i=0;i<n;i++) id[i]=i;
        sort(id,id+n,cmp);
        for(int i=0;i<n;i++)
        {
            ans+=sum*need[id[i]];
            sum-=atk[id[i]];
        }
        printf("Case #%d: %lld\n",tot,ans);
    }
    return 0;
}
