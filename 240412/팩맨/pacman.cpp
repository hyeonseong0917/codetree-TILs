#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
int N,M,T;
const int MAX=4+1;
int dy[8]={-1,-1,0,1,1,1,0,-1};
int dx[8]={0,-1,-1,-1,0,1,1,1};
int py[4]={-1,0,1,0};
int px[4]={0,-1,0,1};
pair<int,int> pack_pos;
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<4 && x<4);
}
vector<pair<int,pair<int,int>>> m;
int smell[MAX][MAX];
map<pair<int,int>,vector<int>> egg;
int board[MAX][MAX];
int tmp_board[MAX][MAX];
void Input(){
    N=4;
    cin>>M>>T;
    int a,b;
    cin>>a>>b;
    --a;
    --b;
    pack_pos.first=a;
    pack_pos.second=b;
    for(int j=0;j<N;++j){
        for(int k=0;k<N;++k){
            smell[j][k]=0;
            board[j][k]=0;
        }
    }
    for(int i=0;i<M;++i){
        int r,c,d;
        cin>>r>>c>>d;
        --r;
        --c;
        --d;
        m.push_back({d,{r,c}});
        ++board[r][c];
    }
    
}
void solve(){
    while(T--){
        // 알까기
        for(int i=0;i<m.size();++i){
            int y=m[i].second.first;
            int x=m[i].second.second;
            int dir=m[i].first;
            // cout<<y<<" "<<x<<endl;
            egg[{y,x}].push_back(dir);
        }
        
        // 몬스터 이동
        for(int i=0;i<m.size();++i){
            int y=m[i].second.first;
            int x=m[i].second.second;
            int dir=m[i].first;
            int ny=y;
            int nx=x;
            bool flag=0;
            int new_dir=-1;
            for(int j=0;j<8;++j){
                ny=y+dy[(dir+j)%8];
                nx=x+dx[(dir+j)%8];
                if(!isRange(ny,nx)) continue;
                if(smell[ny][nx]) continue;
                if(ny==pack_pos.first && nx==pack_pos.second) continue;
                flag=1;
                new_dir=(dir+j)%8;
                break;
            }
            if(!flag) continue;
            //ny,nx로 이동할 것임
            --board[y][x];
            ++board[ny][nx];
            m[i].second.first=ny;
            m[i].second.second=nx;
            m[i].first=new_dir;
            // if(T==0){
            //     cout<<m.size()<<endl;
            //     cout<<"pos "<<ny<<" "<<nx<<" "<<new_dir<<endl;
            // }
        }
        
        // smell 갱신
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(smell[i][j]){
                    ++smell[i][j];
                }
            }
        }
        // 팩맨 이동
        vector<int> move_dir;
        int max_cnt=-1;
        int y=pack_pos.first;
        int x=pack_pos.second;
        vector<pair<int,int>> tmp_pos;
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                for(int k=0;k<4;++k){
                    // i,j,k방향으로 이동
                    int ny=y+py[i];
                    int nx=x+px[i];

                    int nny=ny+py[j];
                    int nnx=nx+px[j];

                    int nnny=nny+py[k];
                    int nnnx=nnx+px[k];

                    if(!isRange(ny,nx)) continue;
                    if(!isRange(nny,nnx)) continue;
                    if(!isRange(nnny,nnnx)) continue;
                    for(int p=0;p<4;++p){
                        for(int q=0;q<4;++q){
                            tmp_board[p][q]=board[p][q];
                        }
                    }
                    int cur_cnt=0;
                    cur_cnt+=board[ny][nx];
                    board[ny][nx]=0;
                    cur_cnt+=board[nny][nnx];
                    board[nny][nnx]=0;
                    cur_cnt+=board[nnny][nnnx];
                    board[nnny][nnnx]=0;
                    for(int p=0;p<4;++p){
                        for(int q=0;q<4;++q){
                            board[p][q]=tmp_board[p][q];
                        }
                    }
                    // cout<<m.size()<<" "<<cur_cnt<<endl;
                    // for(int p=0;p<m.size();++p){
                    //     int my=m[p].second.first;
                    //     int mx=m[p].second.second;
                    //     if(my==ny && mx==nx){
                    //         ++cur_cnt;
                    //     }else if(my==nny && mx==nnx){
                    //         ++cur_cnt;
                    //     }else if(my==nnny && mx==nnnx){
                    //         ++cur_cnt;
                    //     }
                    // }
                    if(cur_cnt>max_cnt){
                        max_cnt=cur_cnt;
                        move_dir.clear();
                        move_dir.push_back(i);
                        move_dir.push_back(j);
                        move_dir.push_back(k);
                    }
                }
            }
        }
        // for(int i=0;i<3;++i){
        //     cout<<move_dir[i]<<" ";
        // }
        // break;
        // cout<<max_cnt<<endl;
        // if(T==0){
        //     cout<<"max"<<max_cnt<<endl;
        // }
        // cout<<move_dir[0]<<" "<<move_dir[1]<<endl;
        // break;
        
        for(int i=0;i<3;++i){
            y+=py[move_dir[i]];
            x+=px[move_dir[i]];
            
            if(board[y][x]){
                smell[y][x]=1;
            }
            board[y][x]=0;
        }
        pack_pos.first=y;
        pack_pos.second=x;
        vector<pair<int,pair<int,int>>> tmp;
        for(int i=0;i<m.size();++i){
            int my=m[i].second.first;
            int mx=m[i].second.second;
            if(board[my][mx]){
               tmp.push_back(m[i]);
            }
        }
        m.clear();
        m=tmp;
        // 시체 소멸
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                if(smell[i][j]==3){
                    smell[i][j]=0;
                }
            }
        }
        
        // 몬스터 부화
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                // cout<<i<<" "<<j<<endl;
                if(!egg[{i,j}].empty()){
                    for(int k=0;k<egg[{i,j}].size();++k){
                        int cur_dir=egg[{i,j}][k];
                        m.push_back({cur_dir,{i,j}});
                        ++board[i][j];
                    }
                    egg[{i,j}].clear();
                }
            }
        }
        
        // for(int i=0;i<m.size();++i){
        //     cout<<m[i].first<<" "<<m[i].second.first<<" "<<m[i].second.second<<endl;
        // }cout<<endl;
        // cout<<m.size()<<endl;
        // break;
    }
    int ms=m.size();
    cout<<ms;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}