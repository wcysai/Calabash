#include<bits/stdc++.h>
#define MAXN 50005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int n,m,q;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
vector<ll> mult(vector<ll> a,vector<ll> b)
{
    vector<ll> c(m);
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
            int id=i+j;
            if(id>=m) id-=m;
            if((a[i]==-1&&b[j]!=0)||(b[j]==-1&&a[i]!=0)||c[id]==-1) c[id]=-1;
            else
            {
                c[id]+=a[i]*b[j];
                if(c[id]>=INF) c[id]=-1;
            }
        }
    return c;
}
int p10[MAXN],pp10[MAXN];
string str;
vector<int> qm;
vector<ll> poly[205];
int main()
{
    pp10[0]=1;
    for(int i=1;i<=50000;i++) pp10[i]=10LL*pp10[i-1]%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&q);
        p10[0]=1;
        for(int i=1;i<=n;i++) p10[i]=p10[i-1]*10%m;
        qm.clear();
        cin>>str;
        int sum=0,ans=0;
        for(int i=n-1;i>=0;i--)
        {
            if(str[i]!='?')
            {
                sum=(sum+(str[i]-'0')*p10[n-i-1])%m;
                add(ans,1LL*(str[i]-'0')*pp10[n-i-1]%MOD);
            }
            else qm.push_back(i);
        }
        int need=(m-sum)%m;
        vector<ll> cur;
        cur.resize(m); cur[0]=1;
        int id=-1;
        poly[0]=cur;
        for(int i=0;i<(int)qm.size();i++)
        {
            vector<ll> tmp; tmp.clear(); tmp.resize(m);
            for(int j=0;j<10;j++)
            {
                int x=p10[n-qm[i]-1]*j%m;
                tmp[x]++;
            }
            cur=mult(cur,tmp);
            poly[i+1]=cur;
            if(cur[need]==-1)
            {
                id=i;
                break;
            }
        }
        if(id==-1) id=(int)qm.size()-1;
        int save=ans;
        for(int i=0;i<q;i++)
        {
            ll k;
            int tmp=need;
            scanf("%lld",&k);
            ans=save;
            if(poly[id+1][tmp]!=-1&&poly[id+1][tmp]<k)
            {
                puts("-1");
                continue;
            }
            for(int i=id;i>=0;i--)
            {
                for(int j=0;j<10;j++)
                {
                    int x=p10[n-qm[i]-1]*j%m,to=(tmp-x+m)%m;
                    if(poly[i][to]>=k)
                    {
                        tmp=(tmp-x+m)%m;
                        add(ans,1LL*pp10[n-qm[i]-1]*j%MOD);
                        break;
                    }
                    else k-=poly[i][to];
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
