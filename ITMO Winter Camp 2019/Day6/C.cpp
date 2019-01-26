#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> P;
//int n,k,a[MAXN];
const int maxn = 25;
const int STEP_NUM = 100;
const db STEP = 1.0 / STEP_NUM;
typedef tuple<int,int,int> Circle;
vector<tuple<int,int,int> > circles;
map<tuple<int,int,int>,pair<db,db> > key_point;
inline bool check(int x,int y,int r){
    return x-r >=0 and x+r <=20 and y-r >=0 and y+r <=20;
}
inline bool in(tuple<int,int,int> ca,tuple<int,int,int> cb){
    int xa,xb,ra,ya,yb,rb;
    tie(xa,ya,ra) = ca;
    tie(xb,yb,rb) = cb;
    ll dis = (xa - xb) * (xa - xb) + (ya - yb )*(ya - yb);
    ll del = abs(ra - rb);
    del *= del;
    return ra < rb and del <=dis;
}
inline bool intersect(tuple<int,int,int> ca,tuple<int,int,int> cb){
    int xa,xb,ya,yb,ra,rb;
    tie(xa,ya,ra) = ca;
    tie(xb,yb,rb) = cb;
    ll dis = (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb);
    ll Min = abs(ra - rb);
    ll Max = ra + rb;
    Min *= Min;
    Max *= Max;
    return Min < dis and dis <= Max;
}
inline db random_db(){
    db x = rand()%20;
    //int y = rand()%20;
    x += STEP * (rand()%STEP_NUM);
    //y += STEP * rand()%STEP_NUM;
    return x; 
}
inline bool point_in_circle(pair<db,db> point,Circle circle){
    int x,y,r;
    tie(x,y,r) = circle;
    db dis = (point.first - x) *(point.first - x) + (point.second - y) * (point.second - y);
    return dis <= r * r;
}
pair<db,db> search_key_point(Circle key_circle,const vector<Circle> & others){
    int T = 1000000;
    while (T--){
        db x = random_db(),
           y = random_db();
        if (point_in_circle(make_pair(x,y),key_circle)){
            bool ok = true;
            for (Circle c : others){
                if (!point_in_circle(make_pair(x,y),c)){
                    ok = false;
                    break;
                }
            }
            if (ok)return make_pair(x,y);
        }
    }
    return make_pair(-1,-1);
}
set<Circle> all;
vector<Circle> ac;
void init(){
    for (int x=0;x<=20;x++){
        for (int y=0;y<=20;y++){
            for (int r = 0;r <=20;r++){
                if (check(x,y,r)){
                    circles.push_back(make_tuple(x,y,r));
                }
            }
        }
    }
    cerr<<"total circle "<<circles.size()<<endl;
    /*for (int i=0;i<circles.size();i++){
        cerr<<i<<endl;
        vector<tuple<int,int,int> > others;
        for (int j=0;j<circles.size();j++){
            //vector<tuple<int,int,int> > others;
            if (in(circles[j],circles[i]) or intersect(circles[j],circles[i])){
                others.push_back(circles[j]);
            }
        }
        key_point[circles[i]] = search_key_point(circles[i],others);
    }
    */
    //for (Circle c : circles){
    //    all.insert(c);
   // }
    for (int i=0;i<circles.size();i++){
        cerr<<i<<endl;
        for (int j=0;j<circles.size();j++){
            //used
            if (all.find(circles[j]) != all.end())continue;
            //check
            vector<Circle> others;
            for (int k = 0;k < circles.size();k++){
                if (all.find(circles[k]) != all.end() or k == j)continue;
                if (in(circles[k],circles[j]) or intersect(circles[k],circles[j])){
                    others.push_back(circles[k]);
                }
            }
            pair<db,db> key_point = search_key_point(circles[j],others);
            if (key_point.first >0 and key_point.first > 0){
                all.insert(circles[j]);
                ac.push_back(circles[j]);
                break;
            }
        }
    }
    assert(ac.size() == circles.size());
}
int main()
{
    init();
    cerr<<"finished random"<<endl;
    return 0;
}

