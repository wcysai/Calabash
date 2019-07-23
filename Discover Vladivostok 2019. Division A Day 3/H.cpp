#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int a[maxn];
int b[maxn];
int n;
int calc(int num){
  vector<int> A(0),B(0);
  for (int i=0;i<num;i++){
    A.push_back(a[i]);
  }
  for (int i=n-1;i >n-1-num;i--){
    B.push_back(b[i]);
  }
  reverse(B.begin(),B.end());
  int ans = 0;
  for (int i=0;i<num;i++){
    if (A[i] > B[i])ans += 2;
    else if (A[i] == B[i])ans += 1;
  }
  return ans;
}
int main(){
  scanf("%d",&n);
  for (int i=0;i<n;i++){
    scanf("%d",b+i);
  }
  for (int i=0;i<n;i++){
    scanf("%d",a+i);
  }
  sort(a,a+n);
  sort(b,b+n);
  reverse(a,a+n);
  reverse(b,b+n);
  int l = 0;
  int r = n;
  for (int i=0;i<30;i++){
    int len = (r - l + 1) / 3;
    int mid = l + len - 1;
    int mmid = r - len + 1;
    if (calc(mid) < calc(mmid)){
      l = mid;
    }else{
      r = mmid;
    }
  }
  int ans = 0;
  for (int i=l;i <=r;i++){
    ans = max(ans,calc(i));
  }
  cout<<ans<<endl;
  return 0;
}
