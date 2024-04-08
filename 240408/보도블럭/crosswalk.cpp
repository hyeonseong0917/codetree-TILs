#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int N,L;
const int MAX=100+1;
int board[MAX][MAX];
int ans=0;
void Input(){
    cin>>N>>L;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cin>>board[i][j];
        }
    }
}
vector<int> tmp;
bool is_pass(vector<int> road){
    vector<bool> check(N,0);
    int idx=1;
    int cur_step=road[0];
    bool flag=0;
    while(!flag){
        if(idx==N){
            break;
        }
        if(cur_step==road[idx]){
            ++idx;
            continue;
        }else{
            if(abs(cur_step-road[idx])>1){
                flag=1;
                break;
            }else{
                if(cur_step<road[idx]){
                    if(idx-L>=0){
                        for(int j=idx-L;j<idx;++j){
                            if(road[j]!=road[idx-L] || check[j]){
                                flag=1;
                                break;
                            }
                            check[j]=1;
                        }
                        if(!flag){
                            cur_step=road[idx];
                            ++idx;
                        }
                    }else{
                        flag=1;
                        break;
                    }
                }else if(cur_step>road[idx]){
                    if(idx+L<=N){
                        for(int j=idx;j<idx+L;++j){
                            if(road[j]!=road[idx] || check[j]){
                                flag=1;
                                break;
                            }
                            check[j]=1;
                        }
                        if(!flag){
                            cur_step=road[idx];
                            idx+=L;
                        }
                    }else{
                        flag=1;
                        break;
                    }
                }
            }
        }
    }
    return flag;
}
void solve(){
    // 모든 행
    for(int i=0;i<N;++i){
        tmp.clear();
        for(int j=0;j<N;++j){
            tmp.push_back(board[i][j]);
        }
        if(!is_pass(tmp)){
            // for(int j=0;j<N;++j){
            //     cout<<tmp[j]<<" ";
            // }cout<<"\n";
            ++ans;
        }
        tmp.clear();
        for(int j=0;j<N;++j){
            tmp.push_back(board[j][i]);
        }
        if(!is_pass(tmp)){
            // for(int j=0;j<N;++j){
            //     cout<<tmp[j]<<" ";
            // }cout<<"\n";
            ++ans;
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