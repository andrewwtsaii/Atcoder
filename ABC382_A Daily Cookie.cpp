#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N, D;
    cin >> N >> D;

    string S;
    cin >> S;

    ll cookies = 0;
    for(auto u: S){
        if(u == '@'){
            cookies++;
        }
    }

    for(ll i = 0; i < D; i++){
        cookies--;
    }

    cout << N - cookies << endl;


}
