#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
int N,M,H,K;
const int MAX=99+1;
int board[MAX][MAX];
bool is_tree[MAX][MAX];
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
vector<pair<int,pair<int,int>>> thief;
pair<int,pair<int,int>> police;
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<N);
}
int get_dist(int y, int x, int yy, int xx){
    return (abs(y-yy)+abs(x-xx));
}
void Input(){
    cin>>N>>M>>H>>K;
    for(int i=0;i<M;++i){
        int x,y,d;
        int dir;
        cin>>x>>y>>d;
        --x;
        --y;
        if(d==1){
            dir=1;
        }else{
            dir=2;
        }
        thief.push_back({dir,{x,y}});
    }
    for(int j=0;j<N;++j){
        for(int k=0;k<N;++k){
            is_tree[j][k]=0;
        }
    }
    police.first=0;
    police.second.first=N/2;
    police.second.second=N/2;
    for(int i=0;i<H;++i){
        int x,y;
        cin>>x>>y;
        --x;
        --y;
        is_tree[x][y]=1;
    }
}
void solve(){
    int ans=0;
    int t=1;
    bool is_reverse_track=0;
    int cur_step=1;
    int step_cnt=0;
    int tmp_step=0;
    while(1){
        // thief 이동
        for(int i=0;i<thief.size();++i){
            int dir=thief[i].first;
            int y=thief[i].second.first;
            int x=thief[i].second.second;
            int py=police.second.first;
            int px=police.second.second;
            int cur_dist=get_dist(y,x,py,px);
            if(cur_dist<=3){
                int ny=y+dy[dir];
                int nx=x+dx[dir];
                if(!isRange(ny,nx)){
                    dir=(dir+2)%4;
                }
                ny=y+dy[dir];
                nx=x+dx[dir];
                if(py==ny && px==nx){
                    thief[i].first=dir; 
                }else{
                    thief[i].first=dir;
                    thief[i].second.first=ny;
                    thief[i].second.second=nx;
                }
            }
        }
        // police 이동
        if(!is_reverse_track){
            int dir=police.first;
            int y=police.second.first;
            int x=police.second.second;
            // cout<<y<<" "<<x<<endl;
            ++tmp_step;
            y+=dy[dir];
            x+=dx[dir];
            if(tmp_step==cur_step){
                ++step_cnt;
                tmp_step=0;
                dir=(dir+1)%4;
            }
            if(y==0 && x==0){
                // cout<<"he";
                is_reverse_track=1;
                tmp_step=1;
                cur_step=N;
                step_cnt=1;
                dir=2;
            }
            police.second.first=y;
            police.second.second=x;
            police.first=dir;
            if(step_cnt==2){
                step_cnt=0;
                ++cur_step;
            }
        }else{
            int dir=police.first;
            int y=police.second.first;
            int x=police.second.second;
            y+=dy[dir];
            x+=dx[dir];
            ++tmp_step;
            if(tmp_step==cur_step){
                ++step_cnt;
                tmp_step=0;
                dir=(dir+3)%4;
            }
            // cout<<y<<" "<<x<<endl;
            if(y==N/2 && x==N/2){
                cur_step=1;
                tmp_step=0;
                step_cnt=0;
                is_reverse_track=0;
                dir=0;
            }
            police.second.first=y;
            police.second.second=x;
            police.first=dir;
            if(step_cnt==2){
                step_cnt=0;
                --cur_step;
            }
        }
        //police 이동
        int dir=police.first;
        int y=police.second.first;
        int x=police.second.second;
        // y,x에 도둑 있는지
        vector<pair<int,pair<int,int>>> tmp; //잡히지 않은 도둑들 관리
        vector<int> del_idx;
        int get_thief=0;
        for(int i=0;i<thief.size();++i){
            int ty=thief[i].second.first;
            int tx=thief[i].second.second;
            if(ty==y && tx==x){
                if(!is_tree[ty][tx])
                {
                    ++get_thief;
                    del_idx.push_back(i);
                }
            }
        }
        for(int i=0;i<2;++i){
            y+=dy[dir];
            x+=dx[dir];
            for(int i=0;i<thief.size();++i){
                int ty=thief[i].second.first;
                int tx=thief[i].second.second;
                if(ty==y && tx==x && !is_tree[ty][tx]){
                    ++get_thief;
                    del_idx.push_back(i);
                }
            }    
        }
        for(int i=0;i<thief.size();++i){
            bool flag=0;
            for(int j=0;j<del_idx.size();++j){
                if(del_idx[j]==i){
                    flag=1;
                    break;
                }
            }
            if(!flag){
                tmp.push_back(thief[i]);
            }
        }
        thief.clear();
        thief=tmp;
        ans+=(t*get_thief);
        if(t==K){
            break;
        }
        ++t;
    }
    cout<<ans;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}