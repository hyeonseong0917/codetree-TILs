#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N,M,H;
int board[300+1][10+1];
bool flag=0;
int board_cnt=1;

void Input(){
    cin>>N>>H>>M;
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            board[i][j]=0;
        }
    }
    for(int i=0;i<N;++i){
        int a,b;
        cin>>a>>b;
        --a;
        --b;
        board[a][b]=board_cnt;
        board[a][b+1]=board_cnt++;
    }
    // for(int i=0;i<M;++i){
    //     for(int j=0;j<N;++j){
    //         cout<<board[i][j];
    //     }cout<<"\n";
    // }
    // cout<<endl;
}
// bool visited[300+1][10+1];
bool simul(){
    bool flag=1;
    for(int i=0;i<N;++i){
        // for(int j=0;j<M;++j){
        //     for(int k=0;k<N;++k){
        //         visited[j][k]=0;
        //     }
        // }
        int y=0;
        int x=i;
        // visited[y][x]=1;
        while(1){
            if(y==M){
                break;
            }
            if(board[y][x]==0){
                ++y;
            }else{
                bool f=0;
                if(x+1<N){
                    if(board[y][x]==board[y][x+1]){
                        f=1;
                        ++x;
                    }
                }
                if(x-1>=0 && !f){
                    if(board[y][x]==board[y][x-1]){
                        --x;
                    }
                }
                ++y;
            }
        }
        if(x!=i){
            flag=0;
            break;
        }
    }
    return flag;
}
int ans=122232421;
void dfs(int y, int x,int init_cnt, int cnt, int cur_num){
    if(cnt==0){
        // for(int i=0;i<M;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<board[i][j];
        //     }cout<<endl;
        // }cout<<endl;
        //
        bool cur_flag=simul();
        // cout<<cur_flag<<" "<<init_cnt<<endl;
        if(cur_flag){
            ans=min(ans,init_cnt);
        }
        return;
    }
    if(y==M){
        return;
    }
    // y,x에 사다리 설치 x
    if(x+1==N-1){
        dfs(y+1,0,init_cnt,cnt,cur_num);
    }else{
        dfs(y,x+1,init_cnt,cnt,cur_num);
    }
    // y,x에 사다리 설치
    if(board[y][x]==0 && board[y][x+1]==0){
        board[y][x]=cur_num;
        board[y][x+1]=cur_num;
        if(x+1==N-1){
            dfs(y+1,0,init_cnt,cnt-1,cur_num+1);
        }else{
            dfs(y,x+1,init_cnt,cnt-1,cur_num+1);
        }
        board[y][x]=0;
        board[y][x+1]=0;
    }
}
void solve(){   
    int cnt=0;
    int tmp_board[300+1][10+1];
    while(cnt<=3){
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                tmp_board[i][j]=board[i][j];
            }
        }
        dfs(0,0,cnt,cnt,board_cnt);
        // cout<<cnt<<endl;
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                board[i][j]=tmp_board[i][j];
            }
        }
        ++cnt;
    }
    if(ans==122232421){
        cout<<-1;
    }else{
        cout<<ans;
    }
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}