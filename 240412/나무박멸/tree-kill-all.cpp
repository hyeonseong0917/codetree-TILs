#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
const int MAX=20+1;
int board[MAX][MAX];
int tmp_board[MAX][MAX];
int drug[MAX][MAX];
int N,M,K,C;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
int ans=0;
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
void Input(){
    cin>>N>>M>>K>>C;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
            drug[i][j]=-1;
        }
    }
}
void solve(){
    while(M--){
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(board[i][j]>0){
                    int tree_cnt=0;
                    for(int k=0;k<4;++k){
                        int ny=i+dy[k];
                        int nx=j+dx[k];
                        if(!isRange(ny,nx)) continue;
                        if(board[ny][nx]>0){
                            ++tree_cnt;
                        }
                    }
                    board[i][j]+=tree_cnt;
                }
            }
        }
        // 번식
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                tmp_board[i][j]=0;
            }
        }
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(board[i][j]<=0) continue;
                // i,j에 대해
                int can_tree_cnt=0;
                for(int k=0;k<4;++k){
                    int ny=i+dy[k];
                    int nx=j+dx[k];
                    if(!isRange(ny,nx)) continue;
                    if(board[ny][nx]!=0) continue;
                    if(drug[ny][nx]!=-1) continue;
                    ++can_tree_cnt;
                }
                for(int k=0;k<4;++k){
                    int ny=i+dy[k];
                    int nx=j+dx[k];
                    if(!isRange(ny,nx)) continue;
                    if(board[ny][nx]!=0) continue;
                    if(drug[ny][nx]!=-1) continue;
                    tmp_board[ny][nx]+=board[i][j]/can_tree_cnt;
                }
            }
        }
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                board[i][j]+=tmp_board[i][j];
            }
        }
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<board[i][j]<<" ";
        //     }cout<<endl;
        // }
        // break;
        // 제초제 뿌려보기
        // 1. -1 아닌 칸들에 대해 ++
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(drug[i][j]!=-1){
                    ++drug[i][j];
                    if(drug[i][j]==C){
                        drug[i][j]=-1;
                    }
                }
            }
        }
        // 2. 제초제 뿌리기
        int max_sum=0;
        int max_y, max_x;
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(board[i][j]<=0) continue;
                int cur_sum=0;
                // 왼쪽 대각선에 뿌려보기
                int y=i;
                int x=j;
                cur_sum+=board[i][j];
                int ny=y-1;
                int nx=x-1;
                int nk=K;
                while(isRange(ny,nx) && nk){
                    --nk;
                    if(board[ny][nx]>0){
                        cur_sum+=board[ny][nx];
                        --ny;
                        --nx;
                    }else{
                        break;
                    }
                }
                // 오른쪽 대각선에 뿌려보기
                ny=y-1;
                nx=x+1;
                nk=K;
                while(isRange(ny,nx) && nk){
                    --nk;
                    if(board[ny][nx]>0){
                        cur_sum+=board[ny][nx];
                        --ny;
                        ++nx;
                    }else{
                        break;
                    }
                }
                // 왼쪽 아래 대각선에
                ny=y+1;
                nx=x-1;
                nk=K;
                while(isRange(ny,nx) && nk){
                    --nk;
                    if(board[ny][nx]>0){
                        cur_sum+=board[ny][nx];
                        ++ny;
                        --nx;
                    }else{
                        break;
                    }
                }
                // 오른쪽 아래 대각선에
                ny=y+1;
                nx=x+1;
                nk=K;
                while(isRange(ny,nx) && nk){
                    --nk;
                    if(board[ny][nx]>0){
                        cur_sum+=board[ny][nx];
                        ++ny;
                        ++nx;
                    }else{
                        break;
                    }
                }
                if(cur_sum>max_sum){
                    max_y=y;
                    max_x=x;
                    max_sum=cur_sum;
                }
            }
        }
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<board[i][j]<<" ";
        //     }cout<<endl;
        // }cout<<endl;
        ans+=max_sum;
        // y,x에 살충제 설치
        drug[max_y][max_x]=0;
        board[max_y][max_x]=0;
        // 왼쪽 위 대각선
        int ny=max_y-1;
        int nx=max_x-1;
        int nk=K;
        while(isRange(ny,nx) && nk){
            --nk;
            if(board[ny][nx]>0){
                drug[ny][nx]=0;
                board[ny][nx]=0;
                --ny;
                --nx;
            }else{
                break;
            }
        }
        // 오른쪽 위 대각선
        ny=max_y-1;
        nx=max_x+1;
        nk=K;
        while(isRange(ny,nx) && nk){
            --nk;
            if(board[ny][nx]>0){
                drug[ny][nx]=0;
                board[ny][nx]=0;
                --ny;
                ++nx;
            }else{
                break;
            }
        }
        // 왼쪽 아래 대각선
        ny=max_y+1;
        nx=max_x-1;
        nk=K;
        while(isRange(ny,nx) && nk){
            --nk;
            if(board[ny][nx]>0){
                drug[ny][nx]=0;
                board[ny][nx]=0;
                ++ny;
                --nx;
            }else{
                break;
            }
        }
        // 오른쪽 아래 대각선
        ny=max_y+1;
        nx=max_x+1;
        nk=K;
        while(isRange(ny,nx) && nk){
            --nk;
            if(board[ny][nx]>0){
                drug[ny][nx]=0;
                board[ny][nx]=0;
                ++ny;
                ++nx;
            }else{
                break;
            }
        }
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<board[i][j]<<" ";
        //     }cout<<endl;
        // }cout<<endl;
    }
    cout<<ans;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}