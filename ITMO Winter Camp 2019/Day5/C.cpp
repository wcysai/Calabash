#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,t,pre[MAXN],suf[MAXN];
struct node
{
    int val,len,height;
}st[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&suf[i]);
        for(int i=1;i<=n;i++) scanf("%d",&pre[i]);
        t=0;
        int ans=0;
        st[t++]=(node){INF,1,INF};
        for(int i=1;i<=n;i++)
        {
            while(t>1&&suf[i]>=st[t-2].val&&st[t-2].val<=st[t-1].height)
            {
                ans+=(st[t-2].val-st[t-1].val)*st[t-1].len;
                int minn=st[t-1].height,l=st[t-1].len;
                t--;
                st[t-1].height=min(st[t-1].height,minn);
                st[t-1].len+=l;
            }
            if(suf[i]<st[t-1].val) st[t++]=(node){suf[i],1,pre[i]};
            else if(t>1&&suf[i]<st[t-2].val&&suf[i]>=st[t-1].val)
            {
                if(suf[i]>st[t-1].height)
                {
                    ans+=(st[t-1].height-st[t-1].val)*st[t-1].len;
                    t=1;
                    st[t++]=(node){suf[i],1,suf[i]};
                }
                else
                {
                    ans+=(suf[i]-st[t-1].val)*st[t-1].len;
                    st[t-1].val=suf[i];
                    st[t-1].height=min(st[t-1].height,pre[i]);
                    st[t-1].len++;
                }
            }
            else
            {
                assert(t>1&&st[t-2].val>st[t-1].height&&suf[i]>st[t-1].height);
                ans+=(st[t-1].height-st[t-1].val)*st[t-1].len;
                t=1;
                st[t++]=(node){suf[i],1,suf[i]};
            }
        }
        while(t>1)
        {
            if(st[t-1].height<st[t-2].val)
            {
                ans+=(st[t-1].height-st[t-1].val)*st[t-1].len;
                break;
            }
            else
            {
                ans+=(st[t-2].val-st[t-1].val)*st[t-1].len;
                int minn=st[t-1].height,l=st[t-1].len;
                t--;
                st[t-1].height=min(st[t-1].height,minn);
                st[t-1].len+=l;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

