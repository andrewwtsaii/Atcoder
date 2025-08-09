#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//Greedy sorting by b-a and then b doesn't work. Starting health and mana matters alot. Counter case: health: 3, mana: 1   3 8, 1 1, 1 1, 1 1, 1 1
//** full solve, fun/tricky
//N <= 3000 -> O(N^2) suffices
//obs 1: modified knapsack ish - items must be taken in order, two criteria health and mana
//obs 2 (important): if health known used for first i items, we can determine mana used very easily and efficiently
//obs 3: dp[i][a]: minimum mana needed if a health is used for first i monsters. dp[i][a] = min(dp[i-1][a] + mana[i], dp[i-1][a-health[i]])
//obs 4: if wanted dp can be made 1-D space, since we only need data of previous monster

ll dp[3001];
vector<pair<ll, ll>> v;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll monsters, health, mana;
    memset(dp, 0, sizeof(dp));

    cin >> monsters >> health >> mana;

    for(ll i = 0; i < monsters; i++){
        ll a, b;
        cin >> a >> b;
        v.push_back({a, b});
    }

    ll ans = 0;

    for(ll i = 1; i <= monsters; i++){
        for(ll j = health; j >= 0; j--){
            if(j >= v[i-1].first){
                dp[j] = min(dp[j] + v[i-1].second, dp[j-v[i-1].first]);
            } else{
                dp[j] = dp[j] + v[i-1].second;
            }
            if(dp[j] <= mana){
                ans = i;
            }
        }
    }

    cout << ans << endl;

}
