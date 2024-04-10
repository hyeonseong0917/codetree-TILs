#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int N;
const int MAX=20+1;
int board[MAX][MAX];
int new_board[MAX][MAX];
bool isRange(int y,int x){
    return (y>=0 &&x>=0 && y<N && x<N);
}
bool visited[MAX][MAX];
void bfs(int cy, int cx, int cur_num){
    // int dy[3];
    // int dx[3];
    // for(int i=0;i<N;++i){
    //     for(int j=0;j<N;++j){
    //         visited[i][j]=0;
    //     }
    // }
    queue<pair<int,int>> q;
    // vector<int> dy(3,0);
    // vector<int> dx(3,0);
    if(cur_num==2){
        // dy={0,1,-1};
        // dx={-1,0,0};
        q.push({cy,cx-1});
        new_board[cy][cx-1]=2;
    }else if(cur_num==3){
        // dy={0,-1,0};
        // dx={1,0,-1};
        q.push({cy-1,cx});
        new_board[cy-1][cx]=3;
        
    }else if(cur_num==4){
        // dy={0,1,-1};
        // dx={-1,0,0};
        q.push({cy+1,cx});
        new_board[cy+1][cx]=4;
    }else if(cur_num==5){
        // dy={-1,0,1};
        // dx={0,1,0};
        q.push({cy,cx+1});
        new_board[cy][cx+1]=5;
    }
    int dy[4]={-1,0,1,0};
    int dx[4]={0,1,0,-1};
    while(!q.empty()){
        int y=q.front().first;
        int x=q.front().second;
        q.pop();
        for(int i=0;i<4;++i){
            int ny=y+dy[i];
            int nx=x+dx[i];
            if(!isRange(ny,nx)) continue;
            if(new_board[ny][nx]!=0) continue;
            new_board[ny][nx]=cur_num;
            q.push({ny,nx});
        }
    }
}
void solve(){
    cin>>N;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
        }
    }
    int ans=122232421;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            for(int k=1;k<=N;++k){
                for(int p=1;p<=N;++p){
                    if(isRange(i-k,j+k) && isRange(i-k-p,j+k-p) && isRange(i-p,j-p)){
                        for(int y=0;y<N;++y){
                            for(int x=0;x<N;++x){
                                new_board[y][x]=0;
                            }
                        }
                        int y=i;
                        int x=j;
                        while(1){
                            if(y==i-k && x==j+k) break;
                            new_board[y][x]=1;
                            y-=1;
                            x+=1;
                        }
                        y=i-k;
                        x=j+k;
                        while(1){
                            if(y==i-k-p && x==j+k-p) break;
                            new_board[y][x]=1;
                            y-=1;
                            x-=1;
                        }
                        y=i-k-p;
                        x=j+k-p;
                        while(1){
                            if(y==i-p && x==j-p) break;
                            new_board[y][x]=1;
                            y+=1;
                            x-=1;
                        }
                        y=i-p;
                        x=j-p;
                        while(1){
                            if(y==i && x==j) break;
                            new_board[y][x]=1;
                            y+=1;
                            x+=1;
                        }
                        // if(i==4 && j==1 && k==3){
                        //     for(int a=0;a<N;++a){
                        //         for(int b=0;b<N;++b){
                        //             cout<<new_board[a][b];
                        //         }cout<<endl;
                        //     }
                        //     return;
                        // }
                        for(int y=i+1;y<N;++y){
                            new_board[y][j]=5;
                        }
                        for(int x=j+k+1;x<N;++x){
                            new_board[i-k][x]=3;
                        }
                        for(int y=i-k-p-1;y>=0;--y){
                            new_board[y][j+k-p]=2;
                        }
                        for(int x=j-p-1;x>=0;--x){
                            new_board[i-p][x]=4;
                        }
                        
                        bfs(i-k-p,j+k-p,2);
                        bfs(i-k,j+k,3);
                        bfs(i-p,j-p,4);
                        bfs(i,j,5);
                        // if(i==6 && j==4 && k==2 && p==2){
                        //     for(int a=0;a<N;++a){
                        //         for(int b=0;b<N;++b){
                        //             cout<<new_board[a][b];
                        //         }cout<<endl;
                        //     }
                        //     return;
                        // }
                        for(int y=0;y<N;++y){
                            for(int x=0;x<N;++x){
                                if(new_board[y][x]==0){
                                    new_board[y][x]=1;
                                }
                            }
                        }

                        vector<int> sum(5,0);
                        for(int y=0;y<N;++y){
                            for(int x=0;x<N;++x){
                                int cur_num=board[y][x];
                                int host_num=new_board[y][x];
                                sum[host_num-1]+=cur_num;
                            }
                        }
                        sort(sum.begin(),sum.end());
                        ans=min(ans,sum[4]-sum[0]);
                        if(ans==15){
                            cout<<i<<" "<<j<<" "<<p<<" "<<k<<endl;
                            for(int a=0;a<N;++a){
                                for(int b=0;b<N;++b){
                                    cout<<new_board[a][b];
                                }cout<<endl;
                            }    
                            return;    
                        }
                        // if(ans==30){
                        //     for(int a=0;a<N;++a){
                        //         for(int b=0;b<N;++b){
                        //             cout<<new_board[a][b];
                        //         }cout<<endl;
                        //     }    
                        //     return;
                        // }

                        // if(i==5 && j==1 && k==3){
                        //     for(int a=0;a<N;++a){
                        //         for(int b=0;b<N;++b){
                        //             cout<<new_board[a][b];
                        //         }cout<<endl;
                        //     }
                        //     return;
                        // }
                    }
                }
            }
        }
    }
    cout<<ans;
}
int main() {
    // 여기에 코드를 작성해주세요.
    solve();
    return 0;
}