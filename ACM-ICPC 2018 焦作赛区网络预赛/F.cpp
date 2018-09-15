#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int s=505,t=506,oo=0x3f3f3f3f,mod=503;
int a[210],b[210],v[210],ord[410],newa[210],newb[210],
        fir[510],ne[50010],to[50010],w[50010],c[50010],fa[510],
        que[510],in[510],len[510],minw[510],
        n,m,num,k;
void add(int u,int v,int x,int y)
{
    num++;
    ne[num*2]=fir[u];
    fir[u]=num*2;
    to[num*2]=v;
    w[num*2]=x;
    c[num*2]=y;
    ne[num*2+1]=fir[v];
    fir[v]=num*2+1;
    to[num*2+1]=u;
    w[num*2+1]=0;
    c[num*2+1]=-y;
}
void init()
{
    int M;
    scanf("%d%d%d",&n,&k,&M);
    n = M;
    m=num=0;
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a[i],&b[i],&v[i]);
        a[i] ++;
        b[i] +=2;
//        b[i] +=2;
        ord[++m]=a[i];
        ord[++m]=b[i];
    }
    sort(ord+1,ord+m+1);
    m=unique(ord+1,ord+m+1)-ord-1;
    for (int i=1;i<=n;i++)
    {
        newa[i]=lower_bound(ord+1,ord+m+1,a[i])-ord;
        newb[i]=lower_bound(ord+1,ord+m+1,b[i])-ord;
    }
    memset(fir,0,sizeof(fir));
    for (int i=1;i<m;i++) add(i,i+1,oo,0);
    add(s,1,k,0);
    add(m,t,k,0);
    for (int i=1;i<=n;i++)
        add(newa[i],newb[i],1,-v[i]);
}
void check()
{
    for (int i=0;i<=t;i++)
        for (int j=fir[i];j;j=ne[j])
            if (w[j]) printf("%d->%d:%d,%d\n",i,to[j],w[j],c[j]);
}
bool spfa()
{
    /*check();
    printf("\n\n\n");*/
    int u,v,hd=0,tl=1;
    memset(len,0x3f,sizeof(len));
    len[s]=0;
    memset(minw,0,sizeof(minw));
    minw[s]=oo;
    que[0]=s;
    in[s]=1;
    while (hd!=tl)
    {
        u=que[hd++];
        hd%=mod;
        for (int i=fir[u];i;i=ne[i])
            if (w[i]&&len[v=to[i]]>len[u]+c[i])
            {
                len[v]=len[u]+c[i];
                minw[v]=min(minw[u],w[i]);
                fa[v]=i;
                if (!in[v])
                {
                    in[v]=1;
                    que[tl++]=v;
                    tl%=mod;
                }
            }
        in[u]=0;
    }
    return minw[t];
}
int find()
{
    for (int i=fa[t];i;i=fa[to[i^1]])
    {
        w[i]-=minw[t];
        w[i^1]+=minw[t];
    }
    return minw[t]*len[t];
}
int main()
{
    int T,ans;
    scanf("%d",&T);
    while (T--)
    {
        init();
        ans=0;
        while (spfa()) ans-=find();
        printf("%d\n",ans);
    }
}
