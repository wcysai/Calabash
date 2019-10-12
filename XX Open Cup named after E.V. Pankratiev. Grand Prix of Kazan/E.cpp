#include<bits/stdc++.h>
#define MAXN 65
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<125> bs;
int n,q;
bs basis[130];
int weight[130];
void add_basis(bs b,int v)
{
    for(int i=b._Find_first();i!=(int)b.size();i=b._Find_next(i))
    {
        if(!weight[i])
        {
            basis[i]=b;
            weight[i]=v;
            return;
        }
        if(weight[i]<v)
        {
            swap(weight[i],v);
            swap(basis[i],b);
        }
        b^=basis[i];
    }
}
ll get_ans()
{
    ll ans=0;
    for(int i=0;i<125;i++) ans+=weight[i];
    return ans;
}
int main()
{
    memset(weight,0,sizeof(weight));
    scanf("%d%d",&n,&q);
    for(int i=0;i<q;i++)
    {
        bs b; b.reset();
        int u,v,w;
        ll a;
        scanf("%d%d%lld%d",&u,&v,&a,&w);
        b.set(u-1); b.set(v-1);
        for(int j=59;j>=0;j--)
            if((a>>j)&1) b.set(n+59-j);
        add_basis(b,w);
        printf("%lld\n",get_ans());
    }
    return 0;
}
