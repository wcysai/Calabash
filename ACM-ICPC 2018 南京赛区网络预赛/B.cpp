#include<bits/stdc++.h>
using namespace std;
const int MAXM = 105;
const int MAXN = 1e5+10;
int mp[MAXN][MAXM];
vector<pair <int,int>> Color;
int m,n,k;
void input(){
    Color.clear();
    scanf("%d%d%d",&n,&m,&k);
    for (int i=0;i<k;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        Color.push_back({x,y});
    }
    sort(Color.begin(),Color.end());
}
vector<int> yIndex[MAXN];
int bottom[MAXN];
long long calc(){
//	cout<<"Calcing "<<col<<endl;
    memset(bottom,0,sizeof(bottom));
    for (int i = 1;i<=n;i++){
        yIndex[i].clear();
    }
    long long ans = 0;
    for (auto now:Color){
        int ni = now.first,nj = now.second;
//		cout<<"Looping "<<ni<<","<<nj<<endl;
        for (int i = 1;i<=m;i++){
            yIndex[i].clear();
        }
        for (int i = 1;i<=m;i++){
            if (bottom[i]){
                yIndex[bottom[i]].push_back(i);
            }
        }
        int yl=1,yr=m;
        bool br = false;
        for (int ii = ni;ii>=1;ii--){
//			cout<<"Findind "<<ii<<endl;
            for (vector<int>::iterator it = yIndex[ii].begin();it!=yIndex[ii].end();it++){
                int yy = *it;
                if (yy<nj){
                    yl = max(yl,yy+1);
                }else if (yy>nj){
                    yr = min (yr,yy-1);
                }else{
                    br = true;
                    break;
                }
            }
            if (br){
                break;
//				cout<<"Finding Break"<<endl;
            }
            ans+=(n-ni+1)*(nj-yl+1)*(yr-nj+1);
//			cout<<"Finding End:With"<<(n-ii+1)*(nj-yl+1)*(yr-nj+1)<<endl;
        }
        bottom[nj] = ni;
    }

    return ans;
}
long long work(){
    long long ans  = calc();
    long long num = 1LL*n*(n+1)*m*(m+1)/4;//多谢UFO___给我提出的改进建议
    return num - ans;
}
int main(){
    int Cas;
    scanf("%d",&Cas);
    for (int i=1;i<=Cas;i++){
        input();
        printf("Case #%d: %lld\n",i,work());
    }
    return 0;
}
