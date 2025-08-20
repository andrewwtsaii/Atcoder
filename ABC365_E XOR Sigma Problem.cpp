#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
obs 1: Even just looping through all queries is N^2 and too slow
obs 2: for each number if we can find the number of queries with each set bit appearing odd # of times we can multiply the occurences
by the value of the set bit and add it to our answer. (Number of appearances is X + X + X... y times where y is the number of appearances).
we need to easily find/precompute the number of subarrays with each set bit appearing odd times.
obs 3: if a bit appears an odd number of times it will not be cancelled out in XOR, if it appears an even number of times it will be cancelled out
maybe loop through each bit somehow log(2,10^8)
idea 1: use suffix array suff[x][l] containing the number of subarrays ending at x with bit l appearing an odd number of times
loop from 1 to n and calculate how many subarrays with an odd occurence of bit l

suffix array doesn't help (idea 1)

obs 4: problem can be reworded too for each n from 1 to n, how many non size 1 arrays starting at n are there such that bit l
appears an odd number of times
obs 5: each number when removed either keeps a bit occurence the same or changes it from odd -> even or even -> odd if the bit is set

idea 2: for each number 1 to N precompute which bits appear an even amount of times and odd amount of times in a subarray
from a[0] to a[i]. Then loop through each number simulating a removal for each subarrays bit occurences. O(N^2logN)
needs to be improved still...

obs 6: maybe we can calculate number of times each bit appears after arr[i] in O(N) time.
calculate it for arr[0] first, and then loop through the rest of the numbers subtracting current (no subarrays of size 1) set bits.

does obs 6 help us solve the answer?
what information could help us solve the answer?

obs 7: maybe we can calculate the number of times an odd/even subarray appears with arr[i] as the start in O(NlogN) time?
obs 8: adding a number to the current subarrays we are checking at most changes the number of odd or even by 1.
idea 3: keep track of the number of even/odd subarrays of non size 0 starting at a[n]. Loop down from a[n] using
previously determined answers to calculate new one in O(nlogn)

to determine the answer for each a[i] b ased off of a[i+1] do the following:
first determine the # of even/odd subarrays starting at a[i] of at least size 3. (all of these are in answer for a[i+1])
swap even and odd if a[i] current bit is set, and keep it the same otherwise.
then add answer based on the subarray of size 2 starting at a[i]. if subarray a[i] and a[i+1] is odd, increase accordingly otherwise.


to calculate answer loop through # of odd occurences array and add 2^bit to answer
ex:   1   3    2
      001 011  010
odd:  010 001  000
even: 212 110  000

note using (ll)1 << j is more  reliable than pow(2, j). pow(2, j) returns a float and sometimes leads to precision errors or WA for larger j.
*/

ll arr[200001];
ll odd[200001][28];
ll even[200001][28];

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nums;
    cin >> nums;

    for(ll i = 0; i < nums; i++){
        cin >> arr[i];
    }

    memset(odd, 0, sizeof(odd));
    memset(even, 0, sizeof(even));
    for(ll i = nums - 2; i >= 0; i--){
        ll curr = 0;
        ll temp = arr[i];
        ll temp2 = arr[i + 1];
        while(curr < 28){
            if((temp & 1) == 1){
                odd[i][curr] = even[i+1][curr];
                even[i][curr] = odd[i+1][curr];
                if((temp2 & 1) == 1){
                    even[i][curr]++;
                } else{
                    odd[i][curr]++;
                }
            } else{
                odd[i][curr] = odd[i+1][curr];
                even[i][curr] = even[i+1][curr];
                if((temp2 & 1) == 1){
                    odd[i][curr]++;
                } else{
                    even[i][curr]++;
                }
            }

            curr++;
            temp >>= 1;
            temp2 >>= 1;
        }
    }

    /*for(ll i = 0; i < nums; i++){
        for(ll j = 0; j < 3; j++){
            cout << odd[i][j] << " \n"[j == 2];
        }
        for(ll j = 0; j < 3; j++){
            cout << even[i][j] << " \n"[j == 2];
        }
    }*/

    ll ans = 0;
    for(ll i = 0; i < nums; i++){
        for(ll j = 0; j < 28; j++){
            ans += (((ll)1 << j) * odd[i][j]);
        }
    }

    cout << ans << endl;
}
