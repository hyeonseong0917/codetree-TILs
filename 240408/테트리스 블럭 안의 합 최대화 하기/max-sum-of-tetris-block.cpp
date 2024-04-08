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
            int cy=v[i].first;
            int cx=v[i].second;
            sum+=board[cy][cx];
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
vector<pair<int,int>> pos[4];
void solve(){
    pos[0].push_back({1,0});
    pos[0].push_back({2,0});
    pos[0].push_back({1,1});

    pos[1].push_back({-1,1});
    pos[1].push_back({0,1});
    pos[1].push_back({1,1});

    pos[2].push_back({-1,1});
    pos[2].push_back({0,1});
    pos[2].push_back({0,2});

    pos[3].push_back({0,1});
    pos[3].push_back({0,2});
    pos[3].push_back({1,1});
    for(int k=0;k<N;++k){
        for(int p=0;p<M;++p){
            visited[k][p]=0;
        }
    }
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            v.clear();
            visited[i][j]=1;
            v.push_back({i,j});
            dfs(i,j);
            visited[i][j]=0;
        }
    }
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            for(int k=0;k<4;++k){
                // k번째 모형을 넣을 수 있는지?
                int sum=board[i][j];
                for(int p=0;p<3;++p){
                    int ny=i+pos[k][p].first;
                    int nx=j+pos[k][p].second;
                    if(!isRange(ny,nx)){
                        sum=-1;
                        break;
                    }
                    sum+=board[ny][nx];
                }
                ans=max(sum,ans);
            }
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