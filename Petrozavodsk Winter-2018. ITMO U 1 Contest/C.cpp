#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<db,int> P;
set<P> s1,s2;
int t,N,n;
int main()
{
    scanf("%d%d",&t,&N);
    while(t--)
    {
        int nb;
        s1.clear();s2.clear();
        n=(N+1)/2;
        if(n==1)
        {
            printf("0 %.10Lf\n",(db)2.0/3);
            fflush(stdout);
            continue;
        }
        else
        {
            n--;
            printf("0 %.10Lf\n",(db)1.0/3);
            fflush(stdout);
            int id;db x;
            scanf("%d %Lf",&id,&x);
            s1.insert(make_pair(1.0/9,1));
            s2.insert(make_pair(2.0/3,0));
            s2.insert(make_pair(2.0/9,2));
            int cnt=3;
            while(n--)
            {
                if (!n)
                {
                    printf("0 %.10Lf\n", (db) 2.0 / 3);
                    fflush(stdout);
                    break;
                }
                auto it=s2.end();it--;it--;
                auto p=*it;
                s2.erase(it);printf("%d %.10Lf\n",p.S,(db)2.0/3);fflush(stdout);
                s2.insert(make_pair(p.F*1.0/3,p.S));
                s1.insert(make_pair(p.F*2.0/3,cnt));
                scanf("%d %Lf",&id,&x);
                for(auto it=s1.begin();it!=s1.end();it++)
                {
                    if(it->S==id)
                    {
                        p = *it;
                        s1.erase(it);
                        break;
                    }
                }
                s1.insert(make_pair(p.F*1.0/3,p.S));
                s2.insert(make_pair(p.F*2.0/3,cnt+1));
                cnt+=2;
            }
        }
        scanf("%d",&nb);
    }
    return 0;
}
