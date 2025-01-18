#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll arr[400002];
/*
use array of size 2 * N
some kind of sliding window/2 pointer
subsequence made by deleting some # of elements from lft and right
*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N, sum;
    cin >> N >> sum;

    ll total = 0;
    bool possible = false;
    for(ll i = 0; i < N; i++){
        cin >> arr[i];
        total += arr[i];
    }

    for(ll i = N; i < 2 * N; i++){
        arr[i] = arr[i-N];
    }

    ll curr = (total * (sum/total));
    ll rem = sum - curr;

    ll temp = arr[0];

    //12
    //3 8 4
    ll lft = 0, rht = 0;
    if(rem == 0){
        possible = true;
    } else {
        while(rht < 2 * N){
            //cout << temp << " " << lft << " " << rht << " " << endl;
            if(temp == rem){
                possible = true;
                break;
            }
            if(temp < rem){
                rht++;
                temp += arr[rht];
            } else{
                temp -= arr[lft];
                lft++;
            }
        }
    }

    if(!possible){
        cout << "No" << endl;
    } else{
        cout << "Yes" << endl;
    }


}
