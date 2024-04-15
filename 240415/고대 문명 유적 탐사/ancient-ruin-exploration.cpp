#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<5 && x<5);
}
int board[5+1][5+1];
int tmp_board[5+1][5+1];
bool visited[5+1][5+1];
vector<pair<int,int>> tmp_pos;
vector<int> block;
void dfs(int y, int x, int cur_num){
    for(int i=0;i<tmp_pos.size();++i){
        int y=tmp_pos[i].first;
        int x=tmp_pos[i].second;
        for(int j=0;j<4;++j){
            int ny=y+dy[j];
            int nx=x+dx[j];
            if(!isRange(ny,nx)) continue;
            if(visited[ny][nx]) continue;
            if(board[ny][nx]!=cur_num) continue;
            tmp_pos.push_back({ny,nx});
            visited[ny][nx]=1;
            dfs(ny,nx,cur_num);
        }
    }
}
vector<vector<int>> turn(vector<vector<int>> tmp){
    vector<vector<int>> turned_vector;
    for(int i=0;i<3;++i){
        vector<int> tmp_vector;
        for(int j=2;j>=0;--j){
            tmp_vector.push_back(tmp[j][i]);
        }
        turned_vector.push_back(tmp_vector);
    }
    return turned_vector;
}
int N,M;
void Input(){
    cin>>N>>M;
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){
            cin>>board[i][j];
        }
    }
    for(int i=0;i<M;++i){
        int a=0;
        cin>>a;
        block.push_back(a);
    }
}
vector<int> ans;
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    int idx=0;
    while(N--){
        int score=0;
        int max_y, max_x, max_dir;
        int max_score=0;
        
        for(int k=0;k<5;++k){
            for(int p=0;p<5;++p){
                tmp_board[k][p]=board[k][p];
            }
        }
        for(int i=0;i<=2;++i){
            for(int j=0;j<=2;++j){
                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        board[k][p]=tmp_board[k][p];
                    }
                }
                vector<vector<int>> cur_sq;
                int cur_score=0;
                for(int k=i;k<i+3;++k){
                    vector<int> tmp_sq;
                    for(int p=j;p<j+3;++p){
                        tmp_sq.push_back(board[k][p]);
                    }
                    cur_sq.push_back(tmp_sq);
                }
                vector<vector<int>> fst_turn=turn(cur_sq);
                cur_score=0;
                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        visited[k][p]=0;
                        board[k][p]=tmp_board[k][p];
                    }
                }
                for(int k=i;k<i+3;++k){
                    for(int p=j;p<j+3;++p){
                        board[k][p]=fst_turn[k-i][p-j];
                    }
                }

                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        if(visited[k][p]) continue;
                        tmp_pos.clear();
                        visited[k][p]=1;
                        tmp_pos.push_back({k,p});
                        dfs(k,p,board[k][p]);
                        if(tmp_pos.size()>=3){
                            cur_score+=tmp_pos.size();
                        }
                    }
                }
                if(cur_score>max_score){
                    max_score=cur_score;
                    max_y=i;
                    max_x=j;
                    max_dir=1;
                }else if(cur_score==max_score){
                    if(max_dir>1){
                        max_score=cur_score;
                        max_y=i;
                        max_x=j;
                        max_dir=1;
                    }else if(max_dir==1){
                        if(max_x>j){
                            max_score=cur_score;
                            max_y=i;
                            max_x=j;
                            max_dir=1;
                        }else if(max_x==j){
                            if(max_y>i){
                                max_score=cur_score;
                                max_y=i;
                                max_x=j;
                                max_dir=1;
                            }
                            
                        }
                    }
                }


                
                vector<vector<int>> sed_turn=turn(fst_turn);
                cur_score=0;
                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        visited[k][p]=0;
                        board[k][p]=tmp_board[k][p];
                    }
                }
                for(int k=i;k<i+3;++k){
                    for(int p=j;p<j+3;++p){
                        board[k][p]=sed_turn[k-i][p-j];
                    }
                }

                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        if(visited[k][p]) continue;
                        tmp_pos.clear();
                        visited[k][p]=1;
                        tmp_pos.push_back({k,p});
                        dfs(k,p,board[k][p]);
                        if(tmp_pos.size()>=3){
                            cur_score+=tmp_pos.size();
                        }
                    }
                }
                
                if(cur_score>max_score){
                    max_score=cur_score;
                    max_y=i;
                    max_x=j;
                    max_dir=2;
                }else if(cur_score==max_score){
                    if(max_dir>2){
                        max_score=cur_score;
                        max_y=i;
                        max_x=j;
                        max_dir=2;
                    }else if(max_dir==2){
                        if(max_x>j){
                            max_score=cur_score;
                            max_y=i;
                            max_x=j;
                            max_dir=2;
                        }else if(max_x==j){
                            if(max_y>i){
                                max_score=cur_score;
                                max_y=i;
                                max_x=j;
                                max_dir=2;
                            }
                        }
                    }
                }

                vector<vector<int>> trd_turn=turn(sed_turn);
                cur_score=0;
                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        visited[k][p]=0;
                        board[k][p]=tmp_board[k][p];
                    }
                }
                
                
                for(int k=i;k<i+3;++k){
                    for(int p=j;p<j+3;++p){
                        board[k][p]=trd_turn[k-i][p-j];
                    }
                }

                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        if(visited[k][p]) continue;
                        tmp_pos.clear();
                        visited[k][p]=1;
                        tmp_pos.push_back({k,p});
                        dfs(k,p,board[k][p]);
                        if(tmp_pos.size()>=3){
                            cur_score+=tmp_pos.size();
                        }
                    }
                }
                if(cur_score>max_score){
                    max_score=cur_score;
                    max_y=i;
                    max_x=j;
                    max_dir=3;
                }else if(cur_score==max_score){
                    if(max_dir>3){
                        max_score=cur_score;
                        max_y=i;
                        max_x=j;
                        max_dir=3;
                    }else if(max_dir==3){
                        if(max_x>j){
                            max_score=cur_score;
                            max_y=i;
                            max_x=j;
                            max_dir=3;
                        }else if(max_x==j){
                            if(max_y>i){
                                max_score=cur_score;
                                max_y=i;
                                max_x=j;
                                max_dir=3;
                            }
                            
                        }
                    }
                }
                for(int k=0;k<5;++k){
                    for(int p=0;p<5;++p){
                        board[k][p]=tmp_board[k][p];
                    }
                }
            }
        }
        if(max_score==0) continue;
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                board[i][j]=tmp_board[i][j];
            }
        }
        vector<vector<int>> cur_sq;
        for(int i=max_y;i<max_y+3;++i){
            vector<int> tmp_sq;
            for(int j=max_x;j<max_x+3;++j){
                tmp_sq.push_back(board[i][j]);
            }
            cur_sq.push_back(tmp_sq);
        }
        for(int i=1;i<=max_dir;++i){
            cur_sq=turn(cur_sq);
        }
    
        for(int i=max_y;i<max_y+3;++i){
            for(int j=max_x;j<max_x+3;++j){
                board[i][j]=cur_sq[i-max_y][j-max_x];
            }
        }
        while(1){
            for(int i=0;i<5;++i){
                for(int j=0;j<5;++j){
                    visited[i][j]=0;
                }
            }
            vector<pair<int,int>> zero_pos;
            for(int i=0;i<5;++i){
                for(int j=0;j<5;++j){
                    if(visited[i][j]) continue;
                    tmp_pos.clear();
                    visited[i][j]=1;
                    tmp_pos.push_back({i,j});
                    dfs(i,j,board[i][j]);
                    if(tmp_pos.size()>=3){
                        for(int p=0;p<tmp_pos.size();++p){
                            zero_pos.push_back(tmp_pos[p]);
                        }
                    }
                }
            }
            if(zero_pos.empty()){
                break;
            }
            score+=zero_pos.size();
            
            for(int i=0;i<zero_pos.size();++i){
                int y=zero_pos[i].first;
                int x=zero_pos[i].second;
                board[y][x]=0;
            }
            for(int i=0;i<5;++i){
                for(int j=4;j>=0;--j){
                    if(board[j][i]==0){
                        board[j][i]=block[idx++];
                    }
                }
            }
            
        }
        ans.push_back(score);
    }
    for(int i=0;i<ans.size();++i){
        cout<<ans[i]<<" ";
    }
    return 0;
}