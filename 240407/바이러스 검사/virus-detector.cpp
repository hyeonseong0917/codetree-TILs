#include <iostream>
#include <vector>
using namespace std;
int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;
    vector<int> v;
    for(int i=0;i<n;++i){
        int a=0;
        cin>>a;
        v.push_back(a);
    }
    int a,b;
    cin>>a>>b;
    int cnt=0;
    for(int i=0;i<n;++i){
        ++cnt;
        v[i]-=a;
        if(v[i]<=0) continue;
        if(v[i]%b==0){
            cnt+=v[i]/b;
        }else{
            cnt+=(v[i]+b/b);
        }
    }
    cout<<cnt;
}