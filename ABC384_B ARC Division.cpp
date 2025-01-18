#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N, R;
    cin >> N >> R;

    ll rating = R;
    for(ll i = 0; i < N; i++){
        ll D, A;
        cin >> D >> A;
        if(D == 1){
            if(rating >= 1600 && rating <= 2799){
                rating += A;
            }
        } else{
            if(rating >= 1200 && rating <= 2399){
                rating += A;
            }
        }
    }

    cout << rating << endl;

}
