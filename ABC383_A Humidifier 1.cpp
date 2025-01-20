#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N;
    cin >> N;

    ll ans = 0;
    vector<pair<ll, ll>> v;
    for(ll i = 0; i < N; i++){
        ll a, b;
        cin >> a >> b;

        v.push_back({a, b});
    }

    sort(v.begin(), v.end());

    ll curr = 0;
    for(ll i = 1; i <= 100; i++){
        if(ans > 0){
            ans--;
        }
        if(curr < v.size() && v[curr].first == i){
            ans += v[curr].second;
            curr++;
        }

        if(curr == v.size()){
            break;
        }
    }

    cout << ans << endl;

}
