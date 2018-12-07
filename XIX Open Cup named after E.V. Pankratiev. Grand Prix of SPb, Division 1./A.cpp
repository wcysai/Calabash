#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD ((unsigned)1<<31)
#define PHI ((unsigned)1<<30)
#define F first
#define S second
#define hash dsfjidsiof
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> P;
ull Seed,Now,Hash,Salt,Start,Wait,INV,Best;
string str;
int curP[8],curG[8];
int Powers[8],Genes[8];
long double ans;
ull pow_mod(ull a,ull i)
{
    ull s=1;
    while(i)
    {
        if(i&1) s=s*a%MOD;
        a=a*a%MOD;
        i>>=1;
    }
    return s;
}
ull ReverseRandom()
{
    Seed=Seed-151515151;
    if(Seed<0) Seed+=MOD;
    Seed=Seed*INV%MOD;
}
ull Random()
{
    Seed=(Seed*1234567893+151515151)%MOD;
    return Seed;
}
ull GenerateRandomPower()
{
    ull Result=500;
    for(int i=1;i<=10000;i++) Result=Result+Random()%3-1;
    return Result;
}
void CreateRandomPet()
{
    Seed=Now^Hash^Salt;
    long double ret=0;
    for(int i=0;i<=7;i++)
    {
        curP[i]=GenerateRandomPower();
        ret+=abs(curP[i]-500);
    }
    for(int i=0;i<=7;i++) curG[i]=Random()%5;
    if(ans*8.0<ret)
    {
        Best=Now;
        ans=ret/8.0;
        for(int i=0;i<=7;i++)
        {
            Powers[i]=curP[i];
            Genes[i]=curG[i];
        }
    }
}
ull hash(string str)
{
    ull Result=0;
    for(int i=0;i<(int)str.size();i++) Result=(Result*31+(int)str[i])%MOD;
    return Result;
}
int main()
{
    Salt=1748665573;Best=0;
    scanf("%llu%llu",&Start,&Wait);
    cin>>str;
    Hash=hash(str);
    ans=0.0;
    for(ull i=0;i<=Wait;i++)
    {
        Now=Start+i;
        CreateRandomPet();
    }
    printf("%u %.10Lf\n",Best,ans);
    for(int i=0;i<=7;i++) printf("%llu%c",Powers[i],i==7?'\n':' ');
    for(int i=0;i<=7;i++) printf("%llu%c",Genes[i],i==7?'\n':' ');
    return 0;
}
