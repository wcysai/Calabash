#include<bits/stdc++.h>
#define MAXN 20005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,a[105];
bool is_prime[MAXN],is_prime_small[MAXN];
int phi[MAXN],rem[MAXN];
void segment_sieve(int a,int b)
{
    for(int i=0;i*i<=b;i++) is_prime_small[i]=true;
    for(int i=0;i<b-a;i++) is_prime[i]=true,phi[i]=rem[i]=a+i;
    for(int i=2;i*i<=b;i++)
    {
        if(is_prime_small[i])
        {
            for(int j=2*i;j*j<=b;j+=i) is_prime_small[j]=false;
            for(int j=max(2,(a+i-1)/i)*i;j<b;j+=i)
            {
                is_prime[j-a]=false;
                phi[j-a]=phi[j-a]/i*(i-1);
                while(rem[j-a]%i==0) rem[j-a]/=i;
            }
        }
    }
    for(int i=0;i<b-a;i++) if(rem[i]>1) phi[i]=phi[i]/rem[i]*(rem[i]-1);
}

bool isprime(int x)
{
        for(int i=2;i*i<=x;i++) if(x%i==0) return false;
            return true;
}

void check(int pos) {
    if(pos<=0) return;
    segment_sieve(pos,pos+100);
    for(int j=0;j<100;j++) if(phi[j]!=a[j+1]) return;
    throw pos;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        for(int i=1;i<=100;i++) scanf("%d",&a[i]);
        try {
            static const int smallphi[21] = {0,
                1, 1, 2, 2, 4, 2, 6, 4, 6, 4,
                10, 4, 12, 6, 8, 8, 16, 6, 18, 8
            };
            for (int i = 1; i <= 100; i++) for (int j = 1; j <= 20; j++) {
                if (a[i] % smallphi[j]) continue;
                int pp = a[i] / smallphi[j] + 1;
                if (!isprime(pp)) continue;
                check(pp * j - i + 1);
            }
            puts("NO");
        } catch (int ans) {
            puts("YES"); printf("%d\n",ans);
        }
    }
}
