#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N,M;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
const int MAX=29+1;
int board[MAX][MAX];
int group[MAX][MAX];
int near[MAX][MAX];
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
void Input(){
    cin>>N;
    M=N/2;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
        }
    }
}
int sum=0;
bool flag=0;
void dfs(int y, int x, int group_num, int board_num){
    for(int i=0;i<4;++i){
        int ny=y+dy[i];
        int nx=x+dx[i];
        if(!isRange(ny,nx)) continue;
        if(board[ny][nx]!=board_num) continue;
        if(group[ny][nx]) continue;
        group[ny][nx]=group_num;
        dfs(ny,nx,group_num,board_num);
    }
}
int grouping(){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            group[i][j]=0;
        }
    }
    int group_num=1;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(!group[i][j]){
                group[i][j]=group_num;
                dfs(i,j,group_num,board[i][j]);
                ++group_num;
            }
        }
    }
    return group_num-1;
    // for(int i=0;i<N;++i){
    //     for(int j=0;j<N;++j){
    //         cout<<group[i][j]<<" ";
    //     }cout<<endl;
    // }
}
int calc(int group_cnt){
    // 그룹의 개수 group_cnt
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            near[i][j]=0;
        }
    }
    // 
    int sum=0;
    vector<pair<int,int>> group_pos;
    for(int i=1;i<=group_cnt;++i){
        for(int j=i+1;j<=group_cnt;++j){
            // i번째 그룹과 j번째 그룹의 맞닿은 변이 몇 개인지?
            int cnt=0;
            group_pos.clear();
            int fst_num,sed_num;
            int fst_cnt=0, sed_cnt=0;
            for(int p=0;p<N;++p){
                for(int k=0;k<N;++k){
                    if(group[p][k]==i){
                        fst_num=board[p][k];
                        ++fst_cnt;
                        group_pos.push_back({p,k});
                    }
                    if(group[p][k]==j){
                        sed_num=board[p][k];
                        ++sed_cnt;
                    }
                }
            }
            for(int k=0;k<group_pos.size();++k){
                int y=group_pos[k].first;
                int x=group_pos[k].second;
                for(int p=0;p<4;++p){
                    int ny=y+dy[p];
                    int nx=x+dx[p];
                    if(!isRange(ny,nx)) continue;
                    if(group[ny][nx]==j){
                        ++cnt;
                    }
                }
            }
            if(cnt>0){
                // i번째 그룹의 값?
                // j번째 그룹의 값?
                sum+=(fst_cnt+sed_cnt)*fst_num*sed_num*cnt;
            }
        }
    }
    return sum;

}
vector<vector<int>> turn(vector<vector<int>> cur_sq){
    vector<vector<int>> turned_sq;
    for(int i=0;i<M;++i){
        vector<int> tmp;
        for(int j=0;j<M;++j){
            tmp.push_back(cur_sq[M-j-1][i]);
        }
        turned_sq.push_back(tmp);
    }
    return turned_sq;
}
int ans=0;
void solve(){
    //grouping
    int group_cnt=grouping();
    int cur_num=calc(group_cnt);
    if(!flag){
        // sum 계산
        ans+=cur_num;
        // cout<<cur_num;
        flag=1;
    }
    // 십자 회전
    vector<int> u,l,d,r;
    //u
    for(int i=0;i<N;++i){
        u.push_back(board[i][M]);
    }
    //l ---->
    for(int i=0;i<N;++i){
        l.push_back(board[M][i]);
    }
    //d
    for(int i=N-1;i>=0;--i){
        d.push_back(board[i][M]);
    }
    //r <-----
    for(int i=N-1;i>=0;--i){
        r.push_back(board[M][i]);
    }
    //u
    for(int i=0;i<N;++i){
        board[i][M]=r[i];
        // u.push_back(board[i][M]);
    }
    //l ---->
    for(int i=0;i<N;++i){
        board[M][i]=u[i];
        // l.push_back(board[M][i]);
    }
    //d
    for(int i=N-1;i>=0;--i){
        board[i][M]=l[N-1-i];
        // d.push_back(board[i][M]);
    }
    //r <-----
    for(int i=N-1;i>=0;--i){
        board[M][i]=d[N-1-i];
        // r.push_back(board[M][i]);
    }
    // for(int i=0;i<N;++i){
    //     for(int j=0;j<N;++j){
    //         cout<<board[i][j]<<" ";
    //     }cout<<endl;
    // }
    // 정사각형 회전
    // 왼쪽 위
    vector<vector<int>> cur_sq;
    for(int i=0;i<M;++i){
        vector<int> tmp;
        for(int j=0;j<M;++j){
            tmp.push_back(board[i][j]);
        }
        cur_sq.push_back(tmp);
    }
    vector<vector<int>> turned_sq=turn(cur_sq);
    for(int i=0;i<M;++i){
        for(int j=0;j<M;++j){
            board[i][j]=turned_sq[i][j];
        }
    }
    // 오른쪽 위
    cur_sq.clear();
    for(int i=0;i<M;++i){
        vector<int> tmp;
        for(int j=M+1;j<N;++j){
            tmp.push_back(board[i][j]);
        }
        cur_sq.push_back(tmp);
    }
    turned_sq.clear();
    turned_sq=turn(cur_sq);
    for(int i=0;i<M;++i){
        for(int j=M+1;j<N;++j){
            board[i][j]=turned_sq[i][j-(M+1)];
        }
    }
    // 왼쪽 아래
    cur_sq.clear();
    for(int i=M+1;i<N;++i){
        vector<int> tmp;
        for(int j=0;j<M;++j){
            tmp.push_back(board[i][j]);
        }
        cur_sq.push_back(tmp);
    }
    turned_sq.clear();
    turned_sq=turn(cur_sq);
    for(int i=M+1;i<N;++i){
        for(int j=0;j<M;++j){
            board[i][j]=turned_sq[i-(M+1)][j];
        }
    }
    // 오른쪽 아래
    cur_sq.clear();
    for(int i=M+1;i<N;++i){
        vector<int> tmp;
        for(int j=M+1;j<N;++j){
            tmp.push_back(board[i][j]);
        }
        cur_sq.push_back(tmp);
    }
    turned_sq.clear();
    turned_sq=turn(cur_sq);
    for(int i=M+1;i<N;++i){
        for(int j=M+1;j<N;++j){
            board[i][j]=turned_sq[i-(M+1)][j-(M+1)];
        }
    }
    // for(int i=0;i<N;++i){
    //     for(int j=0;j<N;++j){
    //         cout<<board[i][j]<<" ";
    //     }cout<<endl;
    // }
    int cur_group_cnt=grouping();
    ans+=calc(cur_group_cnt);
    // cout<<ans;
    // sum 계산
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    for(int i=0;i<3;++i){
        solve();
    }
    cout<<ans;
    return 0;
}