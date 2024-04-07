#include <iostream>
#include <vector>
using namespace std;
int N,M,K,y,x;
const int MAX=20+1;
int board[MAX][MAX];
vector<int> dice_dir;
vector<int> dice(6,0);
int dy[4]={0,0,-1,1};
int dx[4]={1,-1,0,0};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<M);
}
vector<int> turn_dice(vector<int> cur_dice, int dir){
    vector<int> new_dice(6,0);
    if(dir==0){
        new_dice[0]=cur_dice[2];
        new_dice[1]=cur_dice[3];
        new_dice[2]=cur_dice[1];
        new_dice[3]=cur_dice[0];
        new_dice[4]=cur_dice[4];
        new_dice[5]=cur_dice[5];
    }else if(dir==1){
        new_dice[0]=cur_dice[3];
        new_dice[1]=cur_dice[2];
        new_dice[2]=cur_dice[0];
        new_dice[3]=cur_dice[1];
        new_dice[4]=cur_dice[4];
        new_dice[5]=cur_dice[5];
    }else if(dir==2){
        new_dice[0]=cur_dice[4];
        new_dice[1]=cur_dice[5];
        new_dice[2]=cur_dice[2];
        new_dice[3]=cur_dice[3];
        new_dice[4]=cur_dice[1];
        new_dice[5]=cur_dice[0];
    }else{
        new_dice[0]=cur_dice[5];
        new_dice[1]=cur_dice[4];
        new_dice[2]=cur_dice[2];
        new_dice[3]=cur_dice[3];
        new_dice[4]=cur_dice[0];
        new_dice[5]=cur_dice[1];
    }
    return new_dice;
}
void Input(){
    cin>>N>>M>>y>>x>>K;
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            cin>>board[i][j];
        }
    }
    board[y][x]=0;
    for(int i=0;i<K;++i){
        int a=0;
        cin>>a;
        dice_dir.push_back(a-1);
    }
}
void solve(){
    for(int i=0;i<K;++i){
        int dir=dice_dir[i];
        int ny=y+dy[dir];
        int nx=x+dx[dir];
        if(!isRange(ny,nx)) continue;
        y=ny;
        x=nx;
        dice=turn_dice(dice,dir);
        if(board[y][x]==0){
            board[y][x]=dice[1];
        }else{
            dice[1]=board[y][x];
            board[y][x]=0;
        }
        cout<<dice[0]<<"\n";
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}