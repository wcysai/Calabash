#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5+100;
const int inf = 0x3f3f3f3f;
set<pair<int,int > > area;
int n;
pair<int,int> fish[maxn];
char s[10];
vector<tuple<int,int,int> > points;
int cnt[5];
long long ans =0;
long long now_area = 0;
void add(const tuple<int,int,int> &tp){
    int a,b,c;
    tie(a,b,c) = tp;
    pair<int,int> pr = make_pair(b,c);
    //right check
    auto it = area.lower_bound(pr);
    if (it->second >= pr.second)return;

    //remove left
    while (1) {
        auto it = prev(area.upper_bound(pr));
        if (it->second > pr.second)break;
        pair<int,int> mid = *it;
        auto lit  = it;
        lit --;
        pair<int,int> left = *lit;
        auto rit = it;
        rit ++;
        pair<int,int> right = *rit;
        long long delta_area = 1ll * (mid.first - left.first) * (mid.second - right.second );
        now_area -= delta_area;
        area.erase(mid);
    }

    //add myself
    it = area.lower_bound(pr);
    auto rit = it;
    auto lit = it;
    lit --;
    long long delta_area = 1ll * (pr.first - lit->first )*(pr.second - rit->second);
    now_area += delta_area;
    area.insert(pr);
}

int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d%s",&fish[i].first,s);
        if (s[0] == 'R')fish[i].second = 0;
        else if (s[0] == 'G')fish[i].second = 1;
        else if (s[0] == 'B')fish[i].second = 2;
        else assert(0);
    }
    sort(fish+1,fish +n+1,[](const pair<int,int> &x,const pair<int,int>&y){
        return x.first < y.first;
    });
    for (int i=1,j=1;i<=n;i++){
        if (i!=1){
            cnt[fish[i-1].second] --;
        }
        while (j<=n&&fish[j].first < fish[i].first *2){
            cnt[fish[j].second] ++;
            j++;
        }
        points.push_back(make_tuple(cnt[0]+1,cnt[1]+1,cnt[2]+1));
    }
    sort(points.begin(),points.end(),[](const tuple<int,int,int> &a,const tuple<int,int,int> &b){
        return get<0>(a) < get<0>(b);
    });
    area.insert({0,inf});
    area.insert({inf,0});
    for (int i=n;i>=0;i--){
        while (!points.empty() && get<0>(points.back()) == i+1){
            add(points.back());
            points.pop_back();
        }
        ans += now_area;

    }
    cout<<ans-1<<endl;
    return 0;
}
/*
i=1
1 1 0
i=0
1 2 0
*/
