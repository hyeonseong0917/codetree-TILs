#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
int N,M,K;
const int MAX=10+1;
int board[MAX][MAX];
int people_num[MAX][MAX];
pair<int,int> exit_pos;
vector<pair<int,int>> player;
int dy[4]={-1,1,0,0};
int dx[4]={0,0,-1,1};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
void Input(){
    cin>>N>>M>>K;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
        }
    }
    for(int i=0;i<M;++i){
        int y,x;
        cin>>y>>x;
        --y;
        --x;
        player.push_back({y,x});
        ++people_num[y][x];
    }
    int y,x;
    cin>>y>>x;
    --y;
    --x;
    exit_pos.first=y;
    exit_pos.second=x;
    board[y][x]=-1;
}
int get_dist(int y, int x, int yy, int xx){
    return (abs(y-yy)+abs(x-xx));
}
int ans=0;
vector<vector<int>> turn(vector<vector<int>> v){
    int vs=v.size();
    vector<vector<int>> turned_board;
    for(int i=0;i<vs;++i){
        vector<int> tmp;
        for(int j=0;j<vs;++j){
            tmp.push_back(v[vs-1-j][i]);
        }
        turned_board.push_back(tmp);
    }
    return turned_board;
}
void solve(){
    while(K-- && !player.empty()){
        // player이동
        int ey=exit_pos.first;
        int ex=exit_pos.second;
        for(int i=0;i<player.size();++i){
            int y=player[i].first;
            int x=player[i].second;
            
            int min_dist=get_dist(y,x,ey,ex);
            int ly=-1;
            int lx=-1;
            for(int j=0;j<4;++j){
                int ny=y+dy[j];
                int nx=x+dx[j];
                if(!isRange(ny,nx)) continue;
                if(board[ny][nx]>0) continue;
                if(min_dist>get_dist(ny,nx,ey,ex)){
                    min_dist=get_dist(ny,nx,ey,ex);
                    ly=ny;
                    lx=nx;
                }
            }
            if(ly!=-1){
                // cout<<ly<<" "<<lx<<endl;
                ans+=1;
                player[i].first=ly;
                player[i].second=lx;
                ++people_num[ly][lx];
                --people_num[y][x];
            }
        }
        // 탈출한 player 있는지?
        vector<pair<int,int>> tmp;
        for(int i=0;i<player.size();++i){
            int y=player[i].first;
            int x=player[i].second;
            if(y==ey && x==ex){
                --people_num[y][x];
                continue;
            }else{
                tmp.push_back({y,x});
            }
        }
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<people_num[i][j];
        //     }cout<<endl;
        // }
        int min_width=122232421;
        int min_y,min_x;
        player.clear();
        player=tmp;
        int r,c,cnt;
        // 미로 회전
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                for(int k=1;k<N;++k){
                    // i,j에서 k의 변의 길이를 가지는
                    if(!isRange(i+k, j+k)) continue;
                    bool exit_flag=0;
                    bool person_flag=0;
                    for(int p=i;p<=i+k;++p){
                        for(int q=j;q<=j+k;++q){
                            if(people_num[p][q]){
                                person_flag=1;
                            }
                            if(board[p][q]==-1){
                                exit_flag=1;
                            }
                        }
                    }
                    if(person_flag && exit_flag){
                        if(min_width>k){
                            min_width=k;
                            min_y=i;
                            min_x=j;
                        }
                    }
                }
            }
        }
        // if(K==7){
        //     cout<<min_width<<" "<<min_y<<" "<<min_x<<endl;    
        //     break;
        // }
        // cout<<min_width<<" "<<min_y<<" "<<min_x<<endl;
        // return;
        
        vector<vector<int>> tmp_board, tmp_people;
        // if(K==5){
        //     cout<<min_y<<" "<<min_x<<" "<<min_width<<"\n";
        //     break;
        // }
        for(int i=min_y;i<=min_y+min_width;++i){
            vector<int> tmp, ptmp;
            for(int j=min_x;j<=min_x+min_width;++j){
                tmp.push_back(board[i][j]);
                ptmp.push_back(people_num[i][j]);
            }
            tmp_board.push_back(tmp);
            tmp_people.push_back(ptmp);
        }
        
        vector<vector<int>> turned_board=turn(tmp_board);
        vector<vector<int>> turned_people=turn(tmp_people);
        for(int i=min_y;i<=min_y+min_width;++i){
            for(int j=min_x;j<=min_x+min_width;++j){
                board[i][j]=turned_board[i-min_y][j-min_x];
                if(board[i][j]==-1){
                    exit_pos.first=i;
                    exit_pos.second=j;
                }
                if(board[i][j]>0){
                    --board[i][j];
                }
            }
        }
        // if(K==5){
        //     cout<<ans<<"\n";
        //     break;
        // }
        // 
        vector<pair<int,int>> pre_pos, next_pos;
        // cout<<min_width<<endl;
        for(int i=min_y;i<=min_y+min_width;++i){
            for(int j=min_x;j<=min_x+min_width;++j){
                if(people_num[i][j]){
                    people_num[i][j]=0;
                    pre_pos.push_back({i,j});
                }
                if(turned_people[i-min_y][j-min_x]){
                    people_num[i][j]+=turned_people[i-min_y][j-min_x];
                    next_pos.push_back({i,j});
                }
                // if(K==6){
                //     cout<<i<<" "<<j<<endl;
                // }
            }
            
            // if(K==6){
            //     break;
            // }
        }
        // if(K==5){
        //     cout<<ans<<"\n";
        //     break;
        // }
        // if(K==6){
        //     cout<<ans;
        //     break;
        // }
        vector<pair<int,int>> tmp_player;
        for(int i=0;i<player.size();++i){
            int y=player[i].first;
            int x=player[i].second;
            bool flag=0;
            for(int j=0;j<pre_pos.size();++j){
                if(y==pre_pos[j].first && x==pre_pos[j].second){
                    flag=1;
                    continue;
                }
            }
            if(!flag){
                tmp_player.push_back({y,x});
            }
        }
        for(int i=0;i<next_pos.size();++i){
            tmp_player.push_back(next_pos[i]);
        }
        player.clear();
        player=tmp_player;
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<people_num[i][j];
        //     }cout<<endl;
        // }
        // cout<<endl;
        // for(int i=0;i<N;++i){
        //     for(int j=0;j<N;++j){
        //         cout<<board[i][j];
        //     }cout<<endl;
        // }break;
        // if(K==5){
        //     cout<<ans<<"\n";
        //     break;
        // }
    }
    cout<<ans<<"\n";
    cout<<exit_pos.first+1<<" "<<exit_pos.second+1;
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}