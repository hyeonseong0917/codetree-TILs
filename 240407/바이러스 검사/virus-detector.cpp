#include <iostream>
#include <vector>
using namespace std;
#define ll long long
int main() {
    // 여기에 코드를 작성해주세요.
    ll n;
    cin>>n;
    vector<ll> v;
    for(ll i=0;i<n;++i){
        ll a=0;
        cin>>a;
        v.push_back(a);
    }
    ll a,b;
    cin>>a>>b;
    ll cnt=0;
    for(ll i=0;i<n;++i){
        ++cnt;
        v[i]-=a;
        if(v[i]<=0) continue;
        if(v[i]%b==0){
            cnt+=v[i]/b;
        }else{
            cnt+=(v[i]+b)/b;
        }
    }
    cout<<cnt;
}