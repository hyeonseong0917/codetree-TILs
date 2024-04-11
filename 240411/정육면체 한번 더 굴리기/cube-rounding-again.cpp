#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N,M;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,0};
const int MAX=20+1;
int board[MAX][MAX];
bool visited[MAX][MAX];
vector<int> dice{1,2,3,4,5,6};
pair<int,pair<int,int>> dice_info;
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
vector<int> turn_dice(vector<int> cur_dice, int dir){
    // dir방향으로 주사위를 굴려줌
    vector<int> tmp(6,0);
    if(dir==0){
        tmp[0]=cur_dice[1];
        tmp[1]=cur_dice[5];
        tmp[2]=cur_dice[2];
        tmp[3]=cur_dice[3];
        tmp[4]=cur_dice[0];
        tmp[5]=cur_dice[4];       
    }else if(dir==1){
        tmp[0]=cur_dice[3];
        tmp[1]=cur_dice[1];
        tmp[2]=cur_dice[0];
        tmp[3]=cur_dice[5];
        tmp[4]=cur_dice[4];
        tmp[5]=cur_dice[2];       
    }else if(dir==2){
        tmp[0]=cur_dice[4];
        tmp[1]=cur_dice[0];
        tmp[2]=cur_dice[2];
        tmp[3]=cur_dice[3];
        tmp[4]=cur_dice[5];
        tmp[5]=cur_dice[1];       
    }else if(dir==3){
        tmp[0]=cur_dice[2];
        tmp[1]=cur_dice[1];
        tmp[2]=cur_dice[5];
        tmp[3]=cur_dice[0];
        tmp[4]=cur_dice[4];
        tmp[5]=cur_dice[3];       
    }
    return tmp;
}
int cnt=0;
int ans=0;
void dfs(int y, int x, int cur_num){
    for(int i=0;i<4;++i){
        int ny=y+dy[i];
        int nx=x+dx[i];
        if(visited[ny][nx]) continue;
        if(!isRange(ny,nx)) continue;
        visited[ny][nx]=1;
        if(board[ny][nx]==cur_num){
            ++cnt;
            dfs(ny,nx,cur_num);
        }
    }
}
void solve(){
    cin>>N>>M;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
        }
    }
    dice_info.first=1;
    dice_info.second.first=0;
    dice_info.second.second=0;
    for(int i=0;i<M;++i){
        int ny=dice_info.second.first+dy[dice_info.first];
        int nx=dice_info.second.second+dx[dice_info.first];
        if(!isRange(ny,nx)){
            dice_info.first=(dice_info.first+2)%4;
            ny=dice_info.second.first+dy[dice_info.first];
            nx=dice_info.second.second+dx[dice_info.first];
        }
        // 주사위 굴림
        dice=turn_dice(dice,dice_info.first);
        // ny,nx로 이동했음 
        int bottom_num=dice[5];
        dice_info.second.first=ny;
        dice_info.second.second=nx;
        if(bottom_num>board[ny][nx]){
            dice_info.first=(dice_info.first+1)%4;
        }else if(bottom_num<board[ny][nx]){
            dice_info.first=(dice_info.first+3)%4;
        }
        for(int j=0;j<N;++j){
            for(int k=0;k<N;++k){
                visited[j][k]=0;
            }
        }
        cnt=1;
        visited[ny][nx]=1;
        dfs(ny,nx,board[ny][nx]);
        // cout<<cnt<<" "<<ny<<" "<<nx<<endl;
        ans+=board[ny][nx]*cnt;
    }
    cout<<ans;
}

int main() {
    // 여기에 코드를 작성해주세요.
    solve();
    return 0;
}