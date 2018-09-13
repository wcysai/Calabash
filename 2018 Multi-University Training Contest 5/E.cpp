#include<bits/stdc++.h>
using namespace std;
typedef long double db;
const db PI = 3.1415926535897932384;
const db pi = PI;
const double eps=1e-8;
typedef long long LL;
bool intersect(int x1,int y1,int r1,int x2,int y2,int r2){
    LL dis = (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    LL dis_sum = (r1+r2)*(r1+r2);
    LL dis_di = (r2-r1)*(r2-r1);
    return dis<dis_sum&&dis>=dis_di;
}
db calc(int x1,int y1,int r1,int x2,int y2,int r2){
    db d = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
//    db xc,xd,yc,yd;
    db cosR = (pow(r2,2)+pow(d,2)-pow(r1,2))/(2.0*r2*d);
    db cosr = (pow(r1,2)+pow(d,2)-pow(r2,2))/(2.0*r1*d);
    db ret =0;
    if (cosR>0){
        ret += 2.0*r2*acos(cosR);
    }else{
        ret+=PI*2.0*r2-2.0*r2*acos(-cosR);
    }

    if (cosr>0){
        ret-= 2.0*r1*acos(cosr);
    }else{
        ret-= PI*2.0*r1-2.0*r1*acos(-cosr);
    }
    return ret;
}
void solve(){
    int m,r,R;
    scanf("%d%d",&m,&R);
    db ans = PI*R*2;
    while (m--){
        int x,y;
        scanf("%d%d%d",&x,&y,&r);
        //cout<<ans<<endl;
        if (intersect(x,y,r,0,0,R)){
           // cout<<"a"<<endl;
            ans-= calc(x,y,r,0,0,R);
        }
    }
    printf("%.9f\n",(double)ans);
}
int main(){
    int T;
    for (scanf("%d",&T);T;T--){
        solve();
    }
    return 0;
}
/*
 *
 * 1
4 10
6 3 5
10 -4 3
-2 -4 4
0 9 1
 */
