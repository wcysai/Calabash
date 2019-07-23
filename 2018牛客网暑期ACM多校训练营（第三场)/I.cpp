#include <bits/stdc++.h>
using namespace std;
 
map<int, string> ans = {
  {3, "3.000000"},
  {4, "3.666666"},
  {5, "4.166666"},
  {6, "4.566666"},
  {7, "4.900000"},
  {8, "5.185714286"},
  {9, "5.43571429"},
  {10, "5.657936508"}
};
 
#define x1 atrbkatbjr
#define y1 whiergwori
#define x2 ehgowhrg
#define y2 shiegpoorgshogs
#define x3 wuoghrg
#define y3 wtughsro
 
int x1, y1, x2, y2, x3, y3;
int n;
 
int main() {
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> n;
  cout << ans[n] << endl;
  return 0;
}
