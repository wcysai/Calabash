#include<bits/stdc++.h>
#define MAXN 100005
#define INF 8000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int T;
char sa[1100000],sb[1100000];
int lena,lenb;
int p[1100000],ex[1100000];
void exkmp()
{
    p[1]=lenb;
    int x=1;
    while(sb[x]==sb[x+1]&&x+1<=lenb) x++;
    p[2]=x-1;
    int k=2;
    for(int i=3;i<=lenb;i++)
    {
        int pp=k+p[k]-1,L=p[i-k+1];
        if(i+L<pp+1) p[i]=L;
        else
        {
            int j=pp-i+1;
            if(j<0) j=0;
            while(sb[j+1]==sb[i+j]&&i+j<=lenb) j++;
            p[i]=j;
            k=i;
        }
    }
    x=1;
    while(sb[x]==sb[x]&&x<=lenb) x++;
    ex[1]=x-1;
    k=1;
    for(int i=2;i<=lenb;i++)
    {
        int pp=k+ex[k]-1,L=p[i-k+1];
        if(i+L<pp+1) ex[i]=L;
        else
        {
            int j=pp-i+1;
            if(j<0) j=0;
            while(sb[j+1]==sb[i+j]&&i+j<=lenb&&j<=lenb) j++;
            ex[i]=j;
            k=i;
        }
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",sb+1);
        lenb=strlen(sb+1);
        exkmp();
        ll ans=0;
        for(int i=2;i<=lenb;i++) ans+=min(lenb-i+1,ex[i]+1);
        printf("%lld\n",ans);
    }
    return 0;
}
