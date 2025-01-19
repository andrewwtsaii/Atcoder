#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll arr[200001];

ll N, K, ans = 0;

/*
common recursion trick for generating all possibilities
redundant operations, function called N choose i, where i is all nums from 1 to k times
complementary counting when N choose i is big.
XOR property, XOR everything and XOR result with N - k remaining elements
an element XORed with itself cancels out
*/

ll total = 0;
void getAns(ll curr, ll index, ll choose /* amount of nums left to pick*/){
    if(choose == 0){
        ans = max(ans, curr);
        return;
    }

    if(index == N){
        return;
    }

    getAns(curr, index + 1, choose);

    getAns(curr ^ arr[index], index + 1, choose-1);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    cin >> N >> K;

    for(ll i = 0; i < N; i++){
        cin >> arr[i];
    }


    if(K <= N - K){
        getAns(0, 0, K);
    } else{
        for(ll i = 0; i < N; i++){
            total ^= arr[i];
        }
        getAns(total, 0, N - K);
    }

    cout << ans << endl;


}
