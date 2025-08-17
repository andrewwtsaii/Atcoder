#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
obs 1: if a chord is between a and b. It intersects any chords with an endpoint between a and b and one outside a and b
obs 2: only need to print if an intersectino exists not how many
obs 3: make a < b for easier implementation
reworded problem: how to find segments with overlap but not complete overlap
obs 4: if a segment is completely absorbed in another we cannot just delete it as it may partially overlap with a different segment still
idea 1: loop in order of increasing a. Then keep track of all previous b's. Find b1 > a and < b2. Find smallest b1 > a. Binary search.
to keep time complexity low use set for binary search (given that all a's and b's are distinct from each other)

1 6
2 5
3 4

** full solve!
*/
vector<pair<ll, ll>> v;
set<ll> ss;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll n;
    cin >> n;

    for(ll i = 0; i < n; i++){
        ll a, b;
        cin >> a >> b;
        if(b < a){
            swap(a, b);
        }
        v.push_back({a, b});
    }

    sort(v.begin(), v.end());

    bool ans = false;
    ss.insert(v[0].second);
    for(ll i = 1; i < v.size(); i++){
        auto it = ss.upper_bound(v[i].first);
        if(it != ss.end()){
            if(*it < v[i].second){
                ans = true;
                break;
            }
        }
        ss.insert(v[i].second);
    }

    if(ans == false){
        cout << "No" << endl;
    } else{
        cout << "Yes" << endl;
    }

}
