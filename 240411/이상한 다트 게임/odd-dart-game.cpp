#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N,M,Q;
const int MAX=50+1;
vector<int> v[MAX];
bool visited[MAX][MAX];
vector<pair<pair<int,int>,int>> turn;
vector<pair<int,int>> pos;
void Input(){
    cin>>N>>M>>Q;
    for(int i=1;i<=N;++i){
        for(int j=0;j<M;++j){
            int a=0;
            cin>>a;
            v[i].push_back(a);
        }
    }
    for(int i=0;i<Q;++i){
        int a,b,c;
        cin>>a>>b>>c;
        turn.push_back({{a,b},c});
    }
}
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
bool isRange(int y, int x){
    return (y>=1 && x>=0 && y<=N && x<M);
}
void dfs(int y, int x, int cur_num){
    // cout<<y<<" "<<x<<endl;
    for(int i=0;i<4;++i){
        int ny=y+dy[i];
        int nx=x+dx[i];
        if(nx==-1){
            nx=M-1;
        }
        if(!isRange(ny,nx)) continue;
        if(v[ny][nx]!=cur_num) continue;
        if(visited[ny][nx]) continue;
        visited[ny][nx]=1;
        pos.push_back({ny,nx});
        dfs(ny,nx,cur_num);
    }
    
}
void solve(){
    for(int i=0;i<Q;++i){
        int x=turn[i].first.first;
        int d=turn[i].first.second;
        int k=turn[i].second;
        // 회전
        vector<int> tmp;
        for(int j=1;j<=N;++j){
            tmp.clear();
            if(j%x==0){
                // j번째 원판 회전
                k%=M;
                if(d==0){
                    //시계
                    for(int p=0;p<M;++p){
                        tmp.push_back(v[j][(M-k+p+M)%M]);
                    }
                    v[j].clear();
                    v[j]=tmp;
                }else{
                    //반시계
                    for(int p=0;p<M;++p){
                        tmp.push_back(v[j][(k+p+M)%M]);
                    }
                    v[j].clear();
                    v[j]=tmp;
                }
            }
        }
        // for(int j=1;j<=N;++j){
        //     cout<<j<<"번째"<<endl;
        //     for(int p=0;p<M;++p){
        //         cout<<v[j][p]<<" ";
        //     }cout<<endl;
        // }
        //
        for(int j=1;j<=N;++j){
            for(int p=0;p<M;++p){
                visited[j][p]=0;
            }
        }
        bool flag=0;
        for(int j=1;j<=N;++j){
            for(int p=0;p<M;++p){
                if(!visited[j][p] && v[j][p]){
                    pos.clear();
                    pos.push_back({j,p});
                    visited[j][p]=1;
                    // cout<<j<<" "<<p<<endl;
                    dfs(j,p,v[j][p]);
                    if(pos.size()>1){
                        for(int t=0;t<pos.size();++t){
                            int y=pos[t].first;
                            int x=pos[t].second;
                            v[y][x]=0;
                            flag=1;
                        }
                    }
                }
            }
        }
        // return;
        if(!flag){
            int mean_num=0;
            int sum=0;
            int cnt=0;
            for(int j=1;j<=N;++j){
                for(int p=0;p<M;++p){
                    if(v[j][p]){
                        sum+=v[j][p];
                        ++cnt;
                    }
                }
            }
            if(cnt>0){
                mean_num=sum/cnt;
                for(int j=1;j<=N;++j){
                    for(int p=0;p<M;++p){
                        if(v[j][p]==0) continue;
                        if(v[j][p]>mean_num){
                            --v[j][p];
                        }else if(v[j][p]<mean_num){
                            ++v[j][p];
                        }
                    }
                }
            }
            
        }
    }
    // for(int j=1;j<=N;++j){
    //     cout<<j<<endl;
    //     for(int k=0;k<v[j].size();++k){
    //         cout<<v[j][k]<<" ";
    //     }cout<<endl;
    // }
    int ans=0;
    for(int j=1;j<=N;++j){
        for(int k=0;k<v[j].size();++k){
            ans+=v[j][k];
        }
    }
    cout<<ans;
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}