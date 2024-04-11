#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;
const int MAX=20+1;
int N,M,K;
int total_air_board[MAX][MAX];
int air_board[MAX][MAX];
int board[MAX][MAX];
int air_diff[MAX][MAX];
bool is_wall[MAX][MAX][2];
vector<pair<int,int>> office;
vector<pair<int,pair<int,int>>> air;
int dy[4]={-1,0,1,0};
int dx[4]={0,-1,0,1};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
void Input(){
    cin>>N>>M>>K;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
            if(!board[i][j]) continue;
            if(board[i][j]==1){
                office.push_back({i,j});
            }else{
                air.push_back({board[i][j],{i,j}});
            }
            total_air_board[i][j]=0;
            is_wall[i][j][0]=0;
            is_wall[i][j][1]=0;
            air_diff[i][j]=0;
        }
    }
    for(int i=0;i<K;++i){
        int x,y,s;
        cin>>x>>y>>s;
        is_wall[x-1][y-1][s]=1;
    }
}
void solve(){
    int t=1;
    while(t<=100){
        for(int i=0;i<air.size();++i){
            int cur_num=air[i].first;
            int cy=air[i].second.first;
            int cx=air[i].second.second;
            // y,x에서 시작
            for(int j=0;j<N;++j){
                for(int k=0;k<N;++k){
                    air_board[j][k]=0;
                }
            }
            queue<pair<int,pair<int,int>>> q;
            if(cur_num==2){
                q.push({5,{cy,cx-1}});
                air_board[cy][cx-1]=5;
                while(!q.empty()){
                    int y=q.front().second.first;
                    int x=q.front().second.second;
                    int cnt=q.front().first;
                    q.pop();
                    if(cnt==1) continue;
                    // 위로 45도 확인
                    int ny=y+dy[0];
                    int nx=x+dx[0];
                    int nny=ny+dy[1];
                    int nnx=nx+dx[1];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[y][x][0] && !is_wall[ny][nx][1]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                    // 바로 옆 확인
                    ny=y+dy[1];
                    nx=x+dx[1];
                    if(isRange(ny,nx) && !air_board[ny][nx] && !is_wall[y][x][1]){
                        air_board[ny][nx]=cnt-1;
                        q.push({cnt-1,{ny,nx}});
                    }
                    // 아래로 45도 확인
                    ny=y+dy[2];
                    nx=x+dx[2];
                    nny=ny+dy[1];
                    nnx=nx+dx[1];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[ny][nx][0] && !is_wall[ny][nx][1]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                }
            }else if(cur_num==3){
                q.push({5,{cy-1,cx}});
                air_board[cy-1][cx]=5;
                while(!q.empty()){
                    int y=q.front().second.first;
                    int x=q.front().second.second;
                    int cnt=q.front().first;
                    q.pop();
                    if(cnt==1) continue;
                    // 왼쪽 45도 확인
                    int ny=y+dy[1];
                    int nx=x+dx[1];
                    int nny=ny+dy[0];
                    int nnx=nx+dx[0];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[y][x][1] && !is_wall[ny][nx][0]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                    // 바로 위 확인
                    ny=y+dy[0];
                    nx=x+dx[0];
                    if(isRange(ny,nx) && !air_board[ny][nx] && !is_wall[y][x][0]){
                        air_board[ny][nx]=cnt-1;
                        q.push({cnt-1,{ny,nx}});
                    }
                    // 오른쪽으로 45도 확인
                    ny=y+dy[3];
                    nx=x+dx[3];
                    nny=ny+dy[0];
                    nnx=nx+dx[0];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[ny][nx][1] && !is_wall[ny][nx][0]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                }
            }else if(cur_num==4){
                q.push({5,{cy,cx+1}});
                air_board[cy][cx+1]=5;
                while(!q.empty()){
                    int y=q.front().second.first;
                    int x=q.front().second.second;
                    int cnt=q.front().first;
                    q.pop();
                    if(cnt==1) continue;
                    // 위로 45도 확인
                    int ny=y+dy[0];
                    int nx=x+dx[0];
                    int nny=ny+dy[3];
                    int nnx=nx+dx[3];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[y][x][0] && !is_wall[nny][nnx][1]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                    // 바로 옆 확인
                    ny=y+dy[3];
                    nx=x+dx[3];
                    if(isRange(ny,nx) && !air_board[ny][nx] && !is_wall[ny][nx][1]){
                        air_board[ny][nx]=cnt-1;
                        q.push({cnt-1,{ny,nx}});
                    }
                    // 아래로 45도 확인
                    ny=y+dy[2];
                    nx=x+dx[2];
                    nny=ny+dy[3];
                    nnx=nx+dx[3];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[ny][nx][0] && !is_wall[nny][nnx][1]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                }
            }else if(cur_num==5){
                q.push({5,{cy+1,cx}});
                air_board[cy+1][cx]=5;
                while(!q.empty()){
                    int y=q.front().second.first;
                    int x=q.front().second.second;
                    int cnt=q.front().first;
                    q.pop();
                    if(cnt==1) continue;
                    // 왼쪽아래로 45도 확인
                    int ny=y+dy[1];
                    int nx=x+dx[1];
                    int nny=ny+dy[2];
                    int nnx=nx+dx[2];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[y][x][1] && !is_wall[nny][nnx][0]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                    // 바로 아래 확인
                    ny=y+dy[2];
                    nx=x+dx[2];
                    if(isRange(ny,nx) && !air_board[ny][nx] && !is_wall[y][x][0]){
                        air_board[ny][nx]=cnt-1;
                        q.push({cnt-1,{ny,nx}});
                    }
                    // 오른쪽 아래로 45도 확인
                    ny=y+dy[3];
                    nx=x+dx[3];
                    nny=ny+dy[2];
                    nnx=nx+dx[2];
                    if(isRange(ny,nx) && isRange(nny,nnx)){
                        if(!is_wall[ny][nx][1] && !is_wall[nny][nnx][0]){
                            if(!air_board[nny][nnx]){
                                air_board[nny][nnx]=cnt-1;
                                q.push({cnt-1,{nny,nnx}});
                            }
                        }
                    }
                }
            }
            for(int j=0;j<N;++j){
                for(int k=0;k<N;++k){
                    total_air_board[j][k]+=air_board[j][k];
                }
            }
        }
        // for(int j=0;j<N;++j){
        //     for(int k=0;k<N;++k){
        //         cout<<total_air_board[j][k]<<" ";
        //     }cout<<endl;
        // }cout<<endl;
        // break;
        // 공기 섞기
        for(int j=0;j<N;++j){
            for(int k=0;k<N;++k){
                air_diff[j][k]=0;
            }
        }
        for(int j=0;j<N;++j){
            for(int k=0;k<N;++k){
                for(int p=0;p<4;++p){
                    int ny=j+dy[p];
                    int nx=k+dx[p];
                    if(!isRange(ny,nx)) continue;
                    if(p==1 && is_wall[j][k][1]) continue;
                    if(p==3 && is_wall[ny][nx][1]) continue;
                    if(p==0 && is_wall[j][k][0]) continue;
                    if(p==2 && is_wall[ny][nx][0]) continue;
                    int fst_num=total_air_board[j][k]; //기준
                    int sed_num=total_air_board[ny][nx];
                    if(fst_num<sed_num){
                        air_diff[j][k]+=((sed_num-fst_num)/4);
                        // air_diff[ny][nx]-=((sed_num-fst_num)/4);
                    }else{
                        // air_diff[ny][nx]+=(fst_num-sed_num)/4;
                        air_diff[j][k]-=(fst_num-sed_num)/4;
                    }
                }
            }
        }
        for(int j=0;j<N;++j){
            for(int k=0;k<N;++k){
                total_air_board[j][k]+=air_diff[j][k];
            }
        }
        // for(int j=0;j<N;++j){
        //     for(int k=0;k<N;++k){
        //         cout<<total_air_board[j][k]<<" ";
        //     }cout<<endl;
        // }
        // 외벽 -1
        int y=0, x=0;
        // -----
        while(1){
            if(x==N){
                --x;
                ++y;
                break;
            }
            if(total_air_board[y][x]>0){
                --total_air_board[y][x];
            }
            ++x;
        }
        // // ||||||
        while(1){
            if(y==N){
                --y;
                --x;
                break;
            }
            if(total_air_board[y][x]>0){
                --total_air_board[y][x];
            }
            ++y;
        }
        // // <-----
        while(1){
            if(x==-1){
                ++x;
                --y;
                break;
            }
            if(total_air_board[y][x]>0){
                --total_air_board[y][x];
            }
            --x;
        }
        // // ||||^
        while(1){
            if(y==0){
                break;
            }
            if(total_air_board[y][x]>0){
                --total_air_board[y][x];
            }
            --y;
        }
        // break;
        //verify
        bool flag=1;
        for(int j=0;j<office.size();++j){
            int y=office[j].first;
            int x=office[j].second;
            if(total_air_board[y][x]<K){
                flag=0;
                break;
            }
        }
        // for(int j=0;j<N;++j){
        //     for(int k=0;k<N;++k){
        //         cout<<total_air_board[j][k]<<" ";
        //     }cout<<endl;
        // }
        // break;
        if(flag){
            break;
        }
        ++t;
    }
    if(t>100){
        cout<<-1;
    }else{
        cout<<t;
    }
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}