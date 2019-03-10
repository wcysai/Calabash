#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
typedef long long ll;
typedef tuple<int,int,int> tp3i;
vector<tuple<int,int,int>> person_neg,person_pos ;
int n;
int l;
int m;
tuple<int,int,int> room[maxn];
vector<int> Ans[maxn];
int main(){
    scanf("%d%d%d",&n,&m,&l);
    for (int i=0;i<n;i++){
        int p,c;
        scanf("%d%d",&p,&c);
        room[i] = make_tuple(p,c,i+1);
        //scanf("%d%d",&room[i].first,&room[i].second);
    }
    sort(room,room+n,[](tp3i x,tp3i y){
        int px,cx,idx;
        int py,cy,idy;
        tie(px,cx,idx) = x;
        tie(py,cy,idy) = y;
        return px > py;  
    });
    ll ans = 0;
    for (int i=0;i<m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        if (a-b < 0){
            person_neg.push_back(make_tuple(a,b,i+1));
        }else{
            person_pos.push_back(make_tuple(a,b,i+1));
        }
        //person[i] = make_tuple(a,b,i+1);
        //scanf("%d%d",&person[i].first,&person[i].second);
        ans += 1ll * l *b;
    }
    sort(person_neg.begin(),person_neg.end(),[](tp3i x,tp3i y){
        int ax,bx,idx;
        int ay,by,idy;
        tie(ax,bx,idx) = x;
        tie(ay,by,idy) = y;
        return ax - bx < ay - by; 
    });
    sort(person_pos.begin(),person_pos.end(),[](tp3i x,tp3i y){
       int ax,bx,idx;
       int ay,by,idy;
       tie(ax,bx,idx) = x;
       tie(ay,by,idy) = y;
       return ax - bx > ay - by; 
    });
    for (int j=0,i = 0;j<person_neg.size();j++){
        while (i < n && get<1>(room[i]) == 0)i ++;
        int p,c,id;
        tie(p,c,id) = room[i];
        room[i] = make_tuple(p,c-1,id);
        int a,b,id_p;
        tie(a,b,id_p) =  person_neg[j];
        Ans[id].push_back(id_p);
        ans += 1ll * (a -b) * p;
    }
    for (int j=0,i=n-1;j<person_pos.size();j++){
        while (i >=0 && get<1>(room[i]) == 0)i--;
        int p,c,id;
        tie(p,c,id) = room[i];
        room[i] = make_tuple(p,c-1,id);
        int a,b,id_p;
        tie(a,b,id_p) = person_pos[j];
        ans += 1ll * (a-b ) * p;
        Ans[id].push_back(id_p);
    }


    printf("%lld\n",2*ans);
    for (int i=1;i<=n;i++){
        printf("%d ",(int)Ans[i].size());
        for (int x : Ans[i]){
            printf("%d ",x);
        }
        puts("");
    }
    return 0;
}
