#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N,M;
const int MAX=200+1;
int board[MAX][MAX];
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<M);
}
void Input(){
    cin>>N>>M;
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            cin>>board[i][j];
        }
    }
}
// y,x가 제일 왼쪽 위
vector<pair<int,int>> v;
bool visited[MAX][MAX];
int ans=0;
void dfs(int y, int x){
    if(v.size()==4){
        int sum=0;
        for(int i=0;i<v.size();++i){
            int y=v[i].first;
            int x=v[i].second;
            sum+=board[y][x];
        }
        ans=max(ans,sum);
        return;
    }
    for(int i=0;i<4;++i){
        int ny=y+dy[i];
        int nx=x+dx[i];
        if(!isRange(ny,nx)) continue;
        if(visited[ny][nx]) continue;
        visited[ny][nx]=1;
        v.push_back({ny,nx});
        dfs(ny,nx);
        v.pop_back();
        visited[ny][nx]=0;
    }
    
}
void solve(){
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            for(int k=0;k<N;++k){
                for(int p=0;p<M;++p){
                    visited[k][p]=0;
                }
            }
            v.clear();
            visited[i][j]=1;
            v.push_back({i,j});
            dfs(i,j);
        }
    }
    cout<<ans;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}