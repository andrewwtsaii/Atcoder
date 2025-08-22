#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
obs 1: O(N^2) won't work too much memory and too slow
brute force method: loop through all possible combinations and check if it's valid
obs 2: maybe we can binary search the answer? or use binary search <- unlikely, hard to check if answer x is possible

thought: is selecting the highest price meal always best? -> not always sometimes middle may let us get more expensive side etc

idea 1: sort M meals and N sides. <- don't even need to sort. For each M meal find the most expensive possible side that is valid (not in L pairs)
how to find most expensive side for each meal. idea: use map of set to store sides. Loop through each meal and erase sides linked with that meal
Sort L pairs.

idea 1 revision: for each M meal find most expensive possible side (not in L pair) and take total maximum as answer
to find most expensive possible side, have a map of sets, linking invalid sides with each meal.
sort sides
when looping through each meal find most expensive side by looping through v and checking if it exists in map. At most N pairs.
We only check pairs that have current meal as invalid with current side.
Low time complexity.
*/

ll arr1[200001];

vector<pair<ll, ll>> v;

map<ll, set<ll>> m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll meals, sides, L;
    cin >> meals >> sides >> L;

    for(ll i = 0; i < meals; i++){
        cin >> arr1[i];
    }

    for(ll i = 0; i < sides; i++){
        ll num;
        cin >> num;

        v.push_back({num, i});
    }

    sort(v.begin(), v.end());

    for(ll i = 0; i < L; i++){
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        m[a].insert(b);
    }

    ll ans = 0;
    for(ll i = 0; i < meals; i++){
        ll curr = v.size() - 1;
        while(m[i].find(v[curr].second) != m[i].end()){
            curr--;
        }

        ans = max(ans, v[curr].first + arr1[i]);
    }

    cout << ans << endl;

}
