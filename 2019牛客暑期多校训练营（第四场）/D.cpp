#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll n;
vector<ll> ones,twos;
vector<ll> need;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        if(n%3==0) {printf("1 %lld\n",n); continue;}
        printf("2 ");
        ones.clear(); twos.clear(); need.clear();
        for(int i=0;i<=60;i++)
        {
            if(n&(1LL<<i))
            {
                if(i&1) twos.push_back((1LL<<i));
                else ones.push_back((1LL<<i));
            }
        }
        ll x=n,y=0;
        if(n%3==1)
        {
            if(ones.size()&&twos.size())
            {
                x^=ones[0];
                y^=ones[0]; y^=twos[0];
            }
            else if(ones.size()>=3)
            {
                x^=ones[0];
                y^=ones[0]; y^=ones[1]; y^=ones[2];
            }
            else if(twos.size()>=3)
            {
                x^=twos[0]; x^=twos[1];
                y^=twos[0]; y^=twos[1]; y^=twos[2];
            }
            else assert(0);
        }
        else
        {
            if(ones.size()&&twos.size())
            {
                x^=twos[0];
                y^=ones[0]; y^=twos[0];
            }
            else if(ones.size()>=3)
            {
                x^=ones[0]; x^=ones[1];
                y^=ones[0]; y^=ones[1]; y^=ones[2];
            }
            else if(twos.size()>=3)
            {
                x^=twos[0];
                y^=twos[0]; y^=twos[1]; y^=twos[2];
            }
            else assert(0);
        }
        printf("%lld %lld\n",x,y);
    }
    return 0;
}
