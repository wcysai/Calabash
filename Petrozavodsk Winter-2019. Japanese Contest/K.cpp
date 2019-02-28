#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 5005
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
int n,f[MAXN],p[MAXN];
vector<int> v1,v2;
int ans[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {scanf("%d",&p[i]); v1.push_back(p[i]);} 
    for(int i=1;i<=n;i++) {scanf("%d",&f[i]); v2.push_back(f[i]);}
    sort(v1.begin(),v1.end());sort(v2.begin(),v2.end());
    int id=0;
    for(int i=1;i<=n;i++)
    {
        bool f=true;
        for(int j=0;j<i;j++)
        {
            if(v2[n-1-j]<=v1[i-1-j])
            {
                f=false;
                break;
            }
        }
        if(f) id=i; else break;
    }
    for(int i=1;i<=n;i++)
    {
        int pos=lower_bound(v1.begin(),v1.end(),p[i])-v1.begin();
        //v1.erase(v1.begin()+pos);
        if(pos<id)
        {
            int ppos=(int)v2.size()-id+pos;
            int opos=pos;
            while(ppos<(int)v2.size()-1&&v2[ppos]>v1[opos+1])
            {
                ppos++;
                opos++;
            }
            ans[i]=v2[ppos];
            v1.erase(v1.begin()+pos);v2.erase(v2.begin()+ppos);
            id--;
        }
        else
        {
            int ppos=(int)v2.size()-1-id;
            int opos=0,cnt=0,save=ppos;
            while(ppos<(int)v2.size()-1)
            {
                if(v2[ppos]<=v1[opos]) cnt++;
                ppos++;
                opos++;
                if(cnt==0||(v2[ppos]>v1[pos])) save=max(save,ppos);
            }
            ans[i]=v2[save];
            if(v2[save]>v1[pos]) id--;
            v1.erase(v1.begin()+pos);v2.erase(v2.begin()+save);
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
