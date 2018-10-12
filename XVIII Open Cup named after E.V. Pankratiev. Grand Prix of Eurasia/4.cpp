//
// Created by calabash on 10/12/18.
//

#include <bits/stdc++.h>
#define rep(i,l,r) for (int i=l,_ = r;i<_;i++)
#define REP(i,l,r) for (int i=l,_ = r;i<=_;i++)
using namespace std;
typedef pair<int,int> pii;
const int maxn = 3005;
const int maxm = 55;
const int maxk = 30005;
const int maxt = 10005;
int n,k,m,t;
int v[maxn];
vector<pii>Stu[maxn];
vector<pii> Tar;
double p[maxt][maxm];
vector<int> tests;
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&t);
    REP(i,1,n)scanf("%d",v+i);
    REP(i,1,k){
        int p,q,r;
        scanf("%d%d%d",&p,&q,&r);
        Stu[p].push_back({q,r});
        if (q == m){
            tests.push_back(r);
            Tar.push_back({p,r});
        }
    }
    tests.erase(unique(tests.begin(),tests.end()),tests.end());
    REP(i,1,t)REP(j,1,m-1){
        scanf("%lf",&p[i][j]);
        p[i][j] += p[i-1][j];
    }
    double maxVal = 0;
    int ans =1;
    for (int i=0;i<tests.size();i++){
        int day = tests[i];
        double temp = 0;
        for (pii pair: Tar){
            if (pair.second > day)continue;
            double tt = 1;
            for (pii pr : Stu[pair.first]){
                if (pr.first == m)continue;
                if (pr.second > day)continue;
                int pre = pr.second;
                int sch = pr.first;
                tt *= (p[t][sch] - p[day-1][sch] + p[pre-1][sch] );
            }
            temp += tt * v[pair.first];
        }
        if (temp > maxVal){
            maxVal = temp;
            ans = day;
        }
    }
    printf("%.8lf %d\n",maxVal,ans);
    return 0;
}
/*
4 4 7 6
4 666 5 3
1 1 2
3 1 5
4 4 6
1 4 4
4 2 4
3 4 3
3 2 2
0.2 0 0.01
0.2 0.7 0.17
0.2 0 0.03
0.2 0 0.25
0.1 0.3 0.09
0.1 0 0.45

 */
