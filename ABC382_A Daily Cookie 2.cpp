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

    ll currI = N - 1;
    for(ll i = 0; i < D; i++){
        for(ll j = currI; j >= 0; j--){
            if(S[j] == '@'){
                S[j] = '.';
                break;
            }
        }
    }

    cout << S << endl;


}
