#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
int a[MAXN],u[MAXN],v[MAXN],cnt[MAXN],p[MAXN];
const int nb=1<<20;
void out()
{
    printf("%d\n",n);
    for(int i=0;i<n-1;i++) printf("%d %d\n",p[u[i]],p[v[i]]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) p[i]=i;
    int s=n;
    for(int i=0;i<n-1;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        cnt[u[i]]++;cnt[v[i]]++;
        s^=u[i];s^=v[i];
    }
    if(s==0)
    {
        out();
        return 0;
    }
    int id1=-1,id2=-1,id3=-1;
    for(int i=1;i<=n;i++)
    {
        if(!a[i]||!(cnt[i]&1)) continue;
        if(id1==-1) id1=i;
        else if(id2==-1) id2=i;
        else {id3=i; break;}
    }
    if(id1==-1&&id2==-1)
    {
        puts("-1");
        return 0;
    }
    if(id1!=-1&&id2!=-1&&id3==-1&&(s^id1^id2)==0)
    {
        puts("-1");
        return 0;
    }
    if(id1!=-1&&id2!=-1)
    {
        if((s^id1^id2)==0)
        {
            if((s^id1^id3)!=0) swap(id2,id3);
            else if ((s^id2^id3)!=0) swap(id1,id3);
        }
        int need=s^id1^id2;
        p[id1]=nb;p[id2]=nb+need;
        out();return 0;
    }
    int cur=id1^s;
    p[id1]=cur;
    if(cur>n) {out(); return 0;}
    if(!a[cur]) {puts("-1"); return 0;}
    p[cur]=nb; out();
}
