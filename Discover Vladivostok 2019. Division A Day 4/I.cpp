#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 1e16 + 100;
const int maxm = 1000 + 5;
const int maxk = 400000 + 5;
//ll C[maxk][maxm];
int cnt[maxm];
vector<vector<ll>> CCC(1,vector<ll>(maxk,1));
void init(){
  for (int m=1;m < maxm; m ++){
    CCC.push_back(vector<ll>(m,0));
    for (int i= CCC[m].size();i < maxk && CCC[m].back() < maxn;i ++){
      CCC[m].push_back(CCC[m-1][i-1] + CCC[m][i-1]);
    }
  }
/*
  for (int i=1;i<=5;i++){
    for (int j=1;j<=i;j++){
      cout<<i<<" "<<j<<" "<<CCC[j][i]<<endl;
    }
  }
  */
}
inline ll C(int a,int b){
  return CCC[b][a];
}
void gao(ll n,ll m){
  int k = CCC[m].size() - 1;
  for (int i=m;i>=1;i--){
    k = min(k-1,(int)CCC[i].size() - 1);
    while (C(k,i) > n)k--;
    cout<<k<<" ";
    n -= C(k,i);
  }
  cout<<endl;
  assert(!n);
}
int main(){
  init();
  ll n,m;
  cin>>n>>m;
  if (m == 1){
    cout<<n<<endl;
  }else if (m == 2){
    ll A = 1;
    ll B = 2;
    while (A + B <= n){
      A += B;
      B ++;
    }
    n -= A;
    cout<< B << " "<< n<<endl;
  }else{
    gao(n,m);
  }
  return 0;
}
