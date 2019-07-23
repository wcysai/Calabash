#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5+100;
const LL mod = 1e9+7;
char s[maxn];
map<LL,LL> mp;
LL power(LL x,LL y,LL p){
  LL res =1;
  while (y){
    if (y&1){
      res = res*x%p;
    }
    y>>=1;
    x = x*x%p;
  }
  return res;
}
LL calc(int i,LL p){
  if (p==0)return 0;
  if (i==-1){
    return 0;
  }
  if (s[i]=='0'){
    return (calc(i-1,p)+1)%p;
  }else if (s[i]=='1'){
    return 2LL*(calc(i-1,p)+1)%p;
  }else{
    return (6LL*power(2,calc(i-1,mp[p]),p)-3+p)%p;
  }
}
int main(){
    mp[mod]=mod-1;
    mp[mod-1]=500000002;
    mp[500000002]=243900800;
    mp[243900800]=79872000;
    mp[79872000]=19660800;
    mp[19660800]=5242880;
    mp[5242880]=2097152;
    mp[2097152]=1048576;
    mp[1048576]=524288;
    mp[524288]=262144;
    mp[262144]=131072;
    mp[131072]=65536;
    mp[65536]=32768;
    mp[32768]=16384;
    mp[16384]=8192;
    mp[8192]=4096;
    mp[4096]=2048;
    mp[2048]=1024;
    mp[1024]=512;
    mp[512]=256;
    mp[256]=128;
    mp[128]=64;
    mp[64]=32;
    mp[32]=16;
    mp[16]=8;
    mp[8]=4;
    mp[4]=2;
  int T;
  scanf("%d",&T);
  while (T--){
    scanf("%s",s);
    int n = strlen(s);
    LL ans =calc(n-1,mod);
    printf("%d\n",ans);
  }
  return 0;
}
