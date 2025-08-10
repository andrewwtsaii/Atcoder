#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//idea 1: binary seaching the answer -> not likely since hard to check if possible for x
//idea 2: greedy -> loop from left to right finding first number >= a[i] * 2 mark each as used, doesn't work counter case -> 2 8 9 16
//counter case product: how does taking first number >= a[i] * 2 produce a WA. Why wouldn't we want to take the second best case? (third etc)...
//can't prove taking a number greater than the first number >= a[i] * 2 won't work (i.e 2, 9 vs 2,8)
//bigger difference sometimes helps, we want a to be small so taking a big difference can help a be smaller in the future
//** main point: prove greedy properties before trying

//obs 1: a <= b/2 =>  b >= 2 * a
//obs 2: if arr[i] is a valid b for a, all elements after arr[i] are also valid.
//idea 3: loop through each element keeping track of valid b's (starting index) then choose best options
//how to implement idea 3?

/*
obs 3: each element is either an a or b (smaller or bigger)
obs 4: we want a as small as possible so first half a's second half b's
proof for obs 4: since we want a as small as possible if a number in the second half is a, then this can always be improved by decreasing it to a #
in the fist half
obs 5: if for some x, a number b is invalid, then it will be invalid for all a's after x
two pointers approach
***full solve simple solution

*/
ll arr[1000001];
ll ans = 0;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll cakes;
    cin >> cakes;

    for(ll i = 0; i < cakes; i++){
        cin >> arr[i];
    }

    ll lft = 0, rht = cakes/2;
    if(cakes%2 == 1){
        rht++;
    }
    ll finish = rht;
    while(lft < rht && rht < cakes){
        if(arr[rht] >= 2 * arr[lft]){
            ans++;
            lft++;
            rht++;
        } else{
            rht++;
        }
    }

    cout << ans << endl;
}
