#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
int N;
const int MAX=20+1;
int board[MAX][MAX];
int dist[MAX][MAX];
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
pair<pair<int,int>,pair<int,int>> robot; // {y,x},{lv,exp}
int ans=0;
int INF=122232421;
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
void Input(){
    cin>>N;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
            if(board[i][j]==9){
                board[i][j]=0;
                robot.first.first=i;
                robot.first.second=j;
                robot.second.first=2;
            }
        }
    }
}
void BFS(){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            dist[i][j]=INF;
        }
    }
    dist[robot.first.first][robot.first.second]=0;
    queue<pair<int,int>> q;
    q.push({robot.first.first, robot.first.second});
    int LV=robot.second.first;
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second;
        q.pop();
        for(int i=0;i<4;++i){
            int ny=y+dy[i];
            int nx=x+dx[i];
            if(!isRange(ny,nx)) continue;
            if(board[ny][nx]>LV) continue;
            if(dist[ny][nx]>dist[y][x]+1){
                dist[ny][nx]=dist[y][x]+1;
                q.push({ny,nx});
            }
        }
    }
}
void solve(){
    while(1){
        BFS();
        int min_dist=INF;
        int y,x;
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(!board[i][j]) continue;
                if(board[i][j]>=robot.second.first) continue;
                if(min_dist>dist[i][j]){
                    min_dist=dist[i][j];
                    y=i;
                    x=j;
                }
            }
        }
        if(min_dist==INF){
            break;
        }
        board[y][x]=0;
        robot.first.first=y;
        robot.first.second=x;
        ++robot.second.second;
        if(robot.second.second==robot.second.first){
            ++robot.second.first;
            robot.second.second=0;
        }
        ans+=min_dist;
        // break;
    }
    cout<<ans;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}