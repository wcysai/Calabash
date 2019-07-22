#include<bits/stdc++.h>
#define MAXN 500005
#define MAXM 20000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
int a[2*MAXN];
int bas[2*MAXN][30],pos[2*MAXN][30];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            memset(bas[i],0,sizeof(bas[i]));
            memset(pos[i],0,sizeof(pos[i]));
            int x=a[i],p=i;
            for(int j=29;j>=0;j--) bas[i][j]=bas[i-1][j],pos[i][j]=pos[i-1][j];
            for(int j=29;j>=0;j--)
            {
                if(x&(1<<j))
                {
                    if(!bas[i][j])
                    {
                        bas[i][j]=x;
                        pos[i][j]=p;
                        break;
                    }
                    if(pos[i][j]<p) swap(bas[i][j],x),swap(pos[i][j],p);
                    x^=bas[i][j];
                }
            }
        }
        int lastans=0;
        for(int i=0;i<m;i++)
        {
            int type,l,r,x;
            scanf("%d",&type);
            if(!type)
            {
                scanf("%d%d",&l,&r);
                l=(l^lastans)%n+1,r=(r^lastans)%n+1;
                if(l>r) swap(l,r);
                lastans=0;
                for(int j=29;j>=0;j--) if(pos[r][j]>=l) lastans=max(lastans,lastans^bas[r][j]);
                printf("%d\n",lastans);
            }
            else
            {
                n++;
                scanf("%d",&x); x^=lastans;
                a[n]=x;
                memset(bas[n],0,sizeof(bas[n]));
                memset(pos[n],0,sizeof(pos[n]));
                int p=n;
                for(int j=29;j>=0;j--) bas[n][j]=bas[n-1][j],pos[n][j]=pos[n-1][j];
                for(int j=29;j>=0;j--)
                {
                    if(x&(1<<j))
                    {
                        if(!bas[n][j])
                        {
                            bas[n][j]=x;
                            pos[n][j]=p;
                            break;
                        }
                        if(pos[n][j]<p) swap(bas[n][j],x),swap(pos[n][j],p);
                        x^=bas[n][j];
                    }
                }
            }
        }
    }
}
