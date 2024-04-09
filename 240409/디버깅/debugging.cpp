#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N,M,H;
int board[300+1][10+1];
void Input(){
    cin>>N>>M>>H;
    for(int i=0;i<N;++i){
        int a,b;
        cin>>a>>b;
        --a;
        --b;
        board[a][b]=1;
        board[a][b+1]=1;
    }
    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            cout<<board[i][j];
        }cout<<"\n";
    }
}
int main() {
    // 여기에 코드를 작성해주세요.
    Input();
    return 0;
}