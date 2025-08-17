#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
quite clearly a data structure problem
idea 1: use map to keep track of occurence of each number, each operation subtract from
delete from map if freq = 0
how to get answer from this?

obs 1: cannot keep track of all numbers not in use, range too big
obs 2: problem can be reworded to first number x in data structure without x+1 in it.
obs 3: at most Q unique answers (maybe we can precomputer and store smallest Q numbers not in use?)
proof for obs 3: there are Q questions so max Q answers.
if we store Q + 1 smallest initial numbers not in set, we only need to update in O(1) time each operation. at most Q numbers removed from set so set will
never be empty

idea 2: use idea 1 + set to store MOST numbers not in use
print beginning element in set each query

Q = 5
2 0 2 2 1 1 2 5
not in use: 3 4 6 7 8
4 3
2 0 2 3 1 1 2 5
not in use: 4 6 7 8 <- keep track of frequency if it turns 0 insert into set
4 4
2 0 2 4 1 1 2 5
not in use: 3 6 7 8
... etc

** Full solve

---------------------------------------------------------------------------------------------------------------------------------------
Editorial idea: sequence of N numbers has a mex of at most N. There are N + 1 numbers from 0 to N but only N numbers, one is missing
*/

map<ll, ll> freq;

ll arr[200001];
set<ll> ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nums, queries;
    cin >> nums >> queries;

    for(ll i = 0; i < nums; i++){
        cin >> arr[i];
        freq[arr[i]]++;
    }

    ll curr = 0;
    while(ans.size() < queries + 1){
        if(freq[curr] == 0 || freq.find(curr) == freq.end()){
            ans.insert(curr);
        }
        curr++;
    }

    for(ll q = 0; q < queries; q++){
        ll a, b;
        cin >> a >> b;
        a--;

        freq[arr[a]]--;
        if(freq[arr[a]] == 0){
            freq.erase(arr[a]);
            ans.insert(arr[a]);
        }
        arr[a] = b;
        freq[arr[a]]++;
        ans.erase(arr[a]);


        auto it = ans.begin();
        cout << *it << endl;
    }


}
