#include<bits/stdc++.h>
#define MAXN 100005
#define INF 100000000
#define MOD 100000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
int pow_mod(int a,int i,int m)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
int quadratic_residue(int n,int p)
{
    if(p==2) return (n&1)?1:-1;
    if(pow_mod(n,p>>1,p)!=1) return -1;
    return 1;
}
int get_mod(string str,int p)
{
    int ret=0,sz=(int)str.size();
    for(int i=0;i<sz;i++) ret=(10LL*ret+(str[i]-'0'))%p;
    return ret;
}
int primes[]={
    954854573, 967607731, 973215833,
    975831713, 978949117, 980766497,
    983879921,985918807, 986608921,
    991136977, 991752599, 997137961,
    1003911991, 1009775293, 1012423549
};
int main()
{
    cin>>str;
    for(int i=0;i<15;i++)
    {
        int s=get_mod(str,primes[i]);
        if(quadratic_residue(s,primes[i])==-1)
        {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
