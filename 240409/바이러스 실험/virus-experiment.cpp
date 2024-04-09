#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int N,M,K;
const int MAX=10+1;
int board[MAX][MAX];
int add_board[MAX][MAX];
map<pair<int,int>,vector<pair<int,int>>> v;
int dy[8]={-1,-1,-1,0,0,1,1,1};
int dx[8]={-1,0,1,-1,1,-1,0,1};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
bool comp(pair<int,int> a, pair<int,int> b){
    return a.first<b.first;
}
void Input(){
    cin>>N>>M>>K;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>add_board[i][j];
            board[i][j]=5;
        }
    }
    for(int i=0;i<M;++i){
        int a,b,c;
        cin>>a>>b>>c;
        --a;
        --b;
        // a,b에 c의 나이를 가지는 바이러스 존재
        v[{a,b}].push_back({c,1});
        sort(v[{a,b}].begin(),v[{a,b}].end(),comp);
    }
}
void solve(){
    vector<pair<int,int>> tmp;
    vector<pair<int,int>> die_virus;
    vector<pair<int,pair<int,int>>> vt;
    while(K--){
        vt.clear();
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(!v[{i,j}].empty()){
                    int vs=v[{i,j}].size();
                    die_virus.clear();
                    for(int k=0;k<vs;++k){
                        int cur_age=v[{i,j}][k].first;
                        if(cur_age<=board[i][j]){
                            board[i][j]-=cur_age;
                            ++v[{i,j}][k].first;
                            die_virus.push_back(v[{i,j}][k]);
                        }else{
                            v[{i,j}][k].second=0;
                            vt.push_back({cur_age,{i,j}});
                        }
                    }
                    v[{i,j}]=die_virus;
                }
            }
        }
        // 2
        for(int i=0;i<vt.size();++i){
            int cur_age=vt[i].first;
            int y=vt[i].second.first;
            int x=vt[i].second.second;
            board[y][x]+=cur_age/2;
        }
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         if(!v[{i,j}].empty()){
        //             int vs=v[{i,j}].size();
        //             tmp.clear();
        //             for(int k=0;k<vs;++k){
        //                 if(v[{i,j}][k].second==0){
        //                     board[i][j]+=(v[{i,j}][k].first/2);
        //                 }else{
        //                     tmp.push_back(v[{i,j}][k]);
        //                 }
        //             }
        //             v[{i,j}]=tmp;
        //         }
        //     }
        // }
        // 3
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(!v[{i,j}].empty()){
                    int vs=v[{i,j}].size();
                    for(int k=0;k<vs;++k){
                        if(v[{i,j}][k].first%5==0){
                            for(int p=0;p<8;++p){
                                int ny=i+dy[p];
                                int nx=j+dx[p];
                                if(!isRange(ny,nx)) continue;
                                v[{ny,nx}].push_back({1,1});
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(!v[{i,j}].empty()){
                    sort(v[{i,j}].begin(),v[{i,j}].end(),comp);
                }
            }
        }
        //4
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                board[i][j]+=add_board[i][j];
            }
        }
    }
    int cnt=0;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(!v[{i,j}].empty()){
                cnt+=v[{i,j}].size();
            }
        }
    }
    cout<<cnt;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}