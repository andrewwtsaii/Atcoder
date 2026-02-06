#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
definitely want to only update two cells each operation using L, and R somehow
not difference array

idea: update all ranges to turn into larger ranges with no overlap. Then use differences to calculate black cells.
Subtract total

READ PROBLEM, printed query by query
hard can't really accumulate anything, since summing is O(N) and we have so many queries
can't split up Left and right bounds

obs 1: answer only decreases
stack? prolly not

store a bunch of no overlap ranges?
use previous answer + new non overlap range?

binary search?

idea: split up left and right bounds and use binary search on either right or left bound
when checking smth?
need to link left and right bounds still
keep some data structure of relevant intervals only

***Clear cases write out all cases and see how to solve, binary search idea correct
we want to modify intervals as they appear quickly

Main idea: USE SET TO MAINTAIN INTERVALS IN A DATA STRUCTURE

We can assume all previous intervals are non overlapping since this process will create a better non overlapping interval
Case 1: li <= ri < L, NO AFFECt
Case 2: li <= L <= ri < R. remove range. New range at [li, R]
Case 3: L < li <= R <= ri. remove range. New range at [L, ri]
Case 4: L <= li <= ri <= R. remove range. new range at [L, R]
Case 5: li < L <= R < ri. don't add anything
Case 6: L <= R < li <= ri. No affect

//Trick use -1 for one of the pair values to cleverly binary search
//either finds first pair where li >= lft or where rht >= -1 (lft can be < li)
Problem new interval may intersect MULTIPLE intervals still. Need to loop through these.

HUGE IMPORTANT: WE TRACK WHITE CELLS NOT BLACK ONES. WHITE RANGES CAN ONLY SHRINK NOT MERGE!
Converse
ALL CASES MODIFY FOR CONVERSE
Case 1: li <= ri < L, NO AFFECt
Case 2: li <= L <= ri < R. remove range. New range at [li, L-1]
Case 3: L < li <= R <= ri. remove range. New range at [L, li-1]
Case 4: L <= li <= ri <= R. remove range. new range at [L, R]
Case 5: li < L <= R < ri. mew ranges at [li, L-1] and [R+1, ri]
Case 6: L <= R < li <= ri. No affect

Binary search on pairs: Checks first element, ONLY If firsst elements are equal compare second.
a > lft OR a == lft and r >= -1

HARD
*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N, Q;
    cin >> N >> Q;

    set<pair<int, int>> s;
    s.insert({1, N});

    ll ans = N;
    for(int i = 0; i < Q; i++){
        ll lft, rht;
        cin >> lft >> rht;
        auto it = s.lower_bound({lft, -1});

        //Handles case if there is a  range before it overlapping we only need to check one possibility
        if(it != s.begin()){
            --it;
            if(it->second < lft){  // Doesn't overlap, move forward
                ++it;
            }
        }
        vector<pair<ll, ll>> newS;
        while(it != s.end()){
            ll tempL = it->first;
            ll tempR = it->second;

            if(tempL > rht){ //cells already black
                break;
            }
            ans -= (min(tempR, rht) - max(tempL, lft) + 1);
            if(tempL < lft){
                newS.push_back({tempL, lft-1});
            }

            if(tempR > rht){
                newS.push_back({rht+1, tempR});
            }
            it = s.erase(it); //trick to erase and increment still
        }

        for(auto u: newS){
            s.insert(u);
        }


        cout << ans << endl;

    }

}
