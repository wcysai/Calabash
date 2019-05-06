#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k;
int a[MAXN],b[MAXN],c[MAXN];
int p[MAXN];
bool chosen[MAXN];
bool opt[MAXN];
ll get_res(int x,int y,int z)
{
    return 1LL*x*x+1LL*y*y+1LL*z*z;
}
int main()
{
    srand(time(NULL));
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) p[i]=i;
        for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&b[i],&c[i]);
        ll ans=0;
        for(int _=0;_<200;_++)
        {
            random_shuffle(p+1,p+n+1);
            memset(chosen,false,sizeof(chosen));
            int x=0,y=0,z=0;
            ll res=0;
            for(int i=1;i<=k;i++) 
            {
                chosen[i]=true;
                x+=a[p[i]]; y+=b[p[i]]; z+=c[p[i]];
            }
            res=get_res(x,y,z);
            bool changed;
            do
            {
                changed=false;
                for(int i=1;i<=n;i++)
                {
                    if(changed) break;
                    if(!chosen[i]) continue;
                    for(int j=1;j<=n;j++)
                    {
                        if(chosen[j]) continue;
                        int nx=x+a[p[j]]-a[p[i]],ny=y+b[p[j]]-b[p[i]],nz=z+c[p[j]]-c[p[i]];
                        if(get_res(nx,ny,nz)>res)
                        {
                            res=get_res(nx,ny,nz);
                            changed=true;
                            chosen[j]=true; chosen[i]=false;
                            x=nx; y=ny; z=nz;
                            break;
                        }
                    }
                }
            }while(changed);
            if(res>ans)
            {
                ans=res;
                memset(opt,false,sizeof(opt));
                for(int i=1;i<=n;i++) if(chosen[i]) opt[p[i]]=true;
            }
        }
        printf("%lld\n",ans);
        for(int i=1;i<=n;i++) if(opt[i]) printf("%d ",i);
        printf("\n");
    }
    return 0;
}
