#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
int N,M,K;
map<pair<int,int>,vector<pair<int,pair<int,int>>>> v;
int dy[4]={-1,1,0,0};
int dx[4]={0,1,0,-1};
int ans=0;
bool isRange(int y, int x){
    return (y>=0 && x>=0 && y<N && x<M);
}
void Input(){
    cin>>N>>M>>K;
    for(int i=0;i<K;++i){
        int x,y,s,d,b;
        cin>>x>>y>>s>>d>>b;
        --x;
        --y;
        --d;
        v[{x,y}].push_back({b,{s,d}});
    }
}
int turn_dir(int cur_dir){
    if(cur_dir==0){
        return 1;
    }else if(cur_dir==1){
        return 0;
    }else if(cur_dir==2){
        return 3;
    }else if(cur_dir==3){
        return 2;
    }
    return -1;
}
void solve(){
    map<pair<int,int>,vector<pair<int,pair<int,int>>>> tmp;
    for(int i=0;i<M;++i){
        tmp.clear();
        // 가장 처음 곰팡이 삭제
        for(int j=0;j<N;++j){
            if(!v[{j,i}].empty()){
                ans+=v[{j,i}][0].first;
                v[{j,i}].clear();
                break;
            }
        }
        // 곰팡이 이동
        for(int j=0;j<N;++j){
            for(int k=0;k<M;++k){
                if(!v[{j,k}].empty()){
                    pair<int,pair<int,int>> virus=v[{j,k}][0];
                    int step=virus.second.first;
                    int origin_step=step;
                    int dir=virus.second.second;
                    int cur_size=virus.first;
                    int y=j;
                    int x=k;
                    int need_step=0;
                    // if(j==0 && k==2){
                    //     cout<<i<<"번째"<<"dir"<<dir<<endl;
                    // }
                    if(dir==0 || dir==3){
                        if(dir==0){
                            need_step=y;
                        }else{
                            need_step=x;
                        }
                    }
                    if(dir==1 || dir==2){
                        if(dir==1){
                            need_step=N+N-1-y;
                        }else{
                            need_step=M+M-1-x;
                        }
                    }
                    if(step>=need_step){
                        step-=need_step;
                        if(dir==0){
                            dir=1;
                        }else if(dir==3){
                            dir=2;
                        }
                        if(dir==1){
                            int q=step/(N-1);
                            int mod=step%(N-1);
                            if(q%2==0){
                                y=mod;
                            }else{
                                y=N-1-mod;
                                dir=turn_dir(dir);
                            }
                        }else if(dir==2){
                            int q=step/(M-1);
                            int mod=step%(M-1);
                            if(q%2==0){
                                x=mod;
                            }else{
                                x=M-1-mod;
                                dir=turn_dir(dir);
                            }
                        }
                        
                    }else if(step<need_step){
                        if(dir==0 || dir==3){
                            if(dir==0){
                                y-=step;
                            }else{
                                x-=step;
                            }
                        }else if(dir==1 || dir==2){
                            if(dir==1){
                                int cur_step=N-1-y;
                                if(step>=cur_step){
                                    dir=turn_dir(dir);
                                    step-=cur_step;
                                    y=N-1-step;
                                }else if(step<cur_step){
                                    y+=step;
                                }
                            }else if(dir==2){
                                int cur_step=M-1-x;
                                if(step>=cur_step){
                                    dir=turn_dir(dir);
                                    step-=cur_step;
                                    x=M-1-step;
                                }else if(step<cur_step){
                                    x+=step;
                                }
                            }
                        }    
                    }
                    if(!tmp[{y,x}].empty()){
                        if(tmp[{y,x}][0].first<cur_size){
                            tmp[{y,x}][0]={cur_size,{origin_step,dir}};    
                        }
                    }else{
                        tmp[{y,x}].push_back({cur_size,{origin_step,dir}});
                    }
                }
            }
        }
        v.clear();
        v=tmp;
        // cout<<i<<"번째"<<endl;
        // for(int j=0;j<N;++j){
        //     for(int k=0;k<M;++k){
        //         if(!v[{j,k}].empty()){
        //             cout<<j<<" "<<k<<" "<<v[{j,k}][0].first<<"\n";
        //         }
        //     }
        // }
    }
    cout<<ans;
}

int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    solve();
    return 0;
}