#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int ans=-1;
const int MAX=12+1;
int N,K;
int board[MAX][MAX]; //흰 칸 0, 빨간 칸 1, 파란 칸 2
int m[MAX][MAX]; // 밑 칸
vector<pair<pair<int,int>,pair<int,int>>> v[10+1];
int dy[4]={0,0,-1,1};
int dx[4]={1,-1,0,0};
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
void Input(){
    cin>>N>>K;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
            m[i][j]=0;
        }
    }
    for(int i=1;i<=K;++i){
        int x,y,d;
        cin>>x>>y>>d;
        --x;
        --y;
        --d;
        v[i].push_back({{x,y},{d,i}});
        m[x][y]=i;
    }
}
int turn_dir(int dir){
    if(dir==0){
        return 1;
    }else if(dir==1){
        return 0;
    }else if(dir==2){
        return 3;
    }else{
        return 2;
    }
    return -1;
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    int t=1;
    bool flag=0;
    while(t<=1000){
        for(int i=1;i<=K;++i){
            //i번째 말 이동
            int y=v[i][0].first.first;
            int x=v[i][0].first.second;
            int dir=v[i][0].second.first;
            int ny=y+dy[dir];
            int nx=x+dx[dir];
            if(!isRange(ny,nx) || board[ny][nx]==2){
                dir=turn_dir(dir);
                ny=y+dy[dir];
                nx=x+dx[dir];
                v[i][0].second.first=dir;
                if(!isRange(ny,nx) || board[ny][nx]==2){
                    continue;
                }
            }
            // (ny,nx)로 이동할 것임

            // 1-1.(y,x)에 있던 정보 지우기
            if(m[y][x]==i){
                m[y][x]=0;
            }
            // 1-2. i아래에 있던 말 번호들에 대해 i이후 삭제하기
            vector<pair<pair<int,int>,pair<int,int>>> tmp;
            for(int j=1;j<=K;++j){
                if(i==j) continue;
                tmp.clear();
                for(int k=0;k<v[j].size();++k){
                    if(v[j][k].second.second==i){
                        break;
                    }else{
                        tmp.push_back(v[j][k]);
                    }
                }
                v[j].clear();
                v[j]=tmp;
            }
            // 2-1.이동하려는 곳에 말이 없다면
            if(!m[ny][nx]){
                
                if(board[ny][nx]==0){
                    // 흰칸
                    m[ny][nx]=i;
                    for(int j=0;j<v[i].size();++j){
                        int cur_num=v[i][j].second.second;
                        for(int k=0;k<v[cur_num].size();++k){
                            v[cur_num][k].first.first=ny;
                            v[cur_num][k].first.second=nx;
                        }
                    }
                }else{
                    // 빨칸
                    for(int j=0;j<v[i].size();++j){
                        int cur_num=v[i][j].second.second;
                        for(int k=0;k<v[cur_num].size();++k){
                            v[cur_num][k].first.first=ny;
                            v[cur_num][k].first.second=nx;
                        }
                    }
                    tmp.clear();
                    tmp=v[i];
                    v[i].clear();
                    for(int j=0;j<tmp.size();++j){
                        int cur_num=tmp[j].second.second;
                        v[cur_num].clear();
                    }
                    reverse(tmp.begin(),tmp.end());
                    for(int j=0;j<tmp.size();++j){
                        int cur_num=tmp[j].second.second;
                        for(int k=j;k<tmp.size();++k){
                            v[cur_num].push_back(tmp[k]);
                        }
                    }
                    m[ny][nx]=tmp[0].second.second;
                }
            }else{
                // 2-2. 이동하려는 곳에 말이 있다면
                if(board[ny][nx]==0){
                    for(int j=0;j<v[i].size();++j){
                        int cur_num=v[i][j].second.second;
                        for(int k=0;k<v[cur_num].size();++k){
                            v[cur_num][k].first.first=ny;
                            v[cur_num][k].first.second=nx;
                        }
                    }
                    int bottom_num=m[ny][nx];
                    int vs=v[bottom_num].size();
                    for(int j=0;j<vs;++j){
                        int cur_num=v[bottom_num][j].second.second;
                        for(int p=0;p<v[i].size();++p){
                            v[cur_num].push_back(v[i][p]);
                        }
                    }
                }else{
                    // 빨칸
                    for(int j=0;j<v[i].size();++j){
                        int cur_num=v[i][j].second.second;
                        for(int k=0;k<v[cur_num].size();++k){
                            v[cur_num][k].first.first=ny;
                            v[cur_num][k].first.second=nx;
                        }
                    }
                    tmp.clear();
                    tmp=v[i];
                    v[i].clear();
                    for(int j=0;j<tmp.size();++j){
                        int cur_num=tmp[j].second.second;
                        v[cur_num].clear();
                    }
                    reverse(tmp.begin(),tmp.end());
                    for(int j=0;j<tmp.size();++j){
                        int cur_num=tmp[j].second.second;
                        for(int k=j;k<tmp.size();++k){
                            v[cur_num].push_back(tmp[k]);
                        }
                    }
                    int last_num=tmp[0].second.second;
                    int bottom_num=m[ny][nx];
                    int vs=v[bottom_num].size();
                    for(int j=0;j<vs;++j){
                        int cur_num=v[bottom_num][j].second.second;
                        for(int p=0;p<v[last_num].size();++p){
                            v[cur_num].push_back(v[last_num][p]);
                        }
                    }
                }
            }
            for(int j=1;j<=K;++j){
                if(v[j].size()>=4){
                    flag=1;
                    break;
                }
            }
            // cout<<t<<endl;
            // cout<<i<<"번째 말 이동"<<endl;
            // for(int j=0;j<v[i].size();++j){
            //     cout<<v[i][j].first.first<<" "<<v[i][j].first.second<<endl;
            // }cout<<endl;
        }
        if(flag){
            break;
        }
        // if(t==3){
        //     break;
        // }
        ++t;
    }
    ans=t;
    cout<<ans;
    return 0;
}