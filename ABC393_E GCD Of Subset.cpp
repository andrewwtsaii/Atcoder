#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
binary search probably won't work. If N isn't GCD N-1 still can be and N + 1
obs 1: if a_i = 1, ans = 1
obs 2: if we only select numbers greater than a_i, GCD is maximized at a_i -> we want to select numbers divisible by a_i
obs 3: if we cannot only select numbers greater than a_i our number can be smaller than a_i thus we prioritize selecting larger numbers (divisible by a_i)

idea 1: sort sequence keeping track of numbers that are multiples of a_i

obs 4: if a number runs out of a_i we can select previous numbers that a_i is divisble by as we keep track of this.
obs 5: we may have to do this for numbers larger than a_i as well quickly somehow.
obs 6: if none of the above work we have to select numbers that are multiples of previous numbers that a_i is divisible by
obs 7: if none of the above work we will have to select numbers that make the GCD 1 and break

obs 8: instead of searching for multiples for each number, maybe use a map or vector or keep track of the number of a's divisible by X
obs 9: mostly we don't need to check actual multiples just the amount of multiples

--------------------------------------------------------------------------------------
Editorial: DP Problem
**Need to realize less obvious DP problems**

Note: A GCD of x is only possible if A_i is divisible by X, A has at least K elements divisible by X. The answer is the max among all X
Takes long time to compute above for all N. To speed up we precalculate values and use DP.
Let M = max(A). S_n = occurences of n in A. Let T_n = number of multiples of n in A.
Similar idea to what we had above with number of multiples kept track

The answer is simply the maximum d such that d divides n, and T_d >= K (similar to idea above)
how to get the maximum d and multiples quickly?

Multiples: Nested for loop: outer for loop uses d adding 1 each time, inner for loop starts at d and adds d each time
Maximum d: for each number as d check the number of X divisible by d <- original idea but turns out this is efficient enough

Turns out we just need to prevent from looping through answer for each i, calculate answer for each a_n using two for loops
Instead of using for loop to check every i how many multiples of a divisor exists, better to loop through possible GCD and store
answers for all multiples of gcd X.
Ex. 9, 12 need to loop through all divisors and cheeck multiples of divisor X. <- possibly could work but not official editorial solution

Editorial 3/4 needed
Seems like TLE, but doesn't -> harmonic series
----------------------------------------------------------------------------------------------------------
Solution used (intuitive):
Very close solution almost had it: Problem initially faced, some numbers in a sequence of numbers in A is not necessarily
a divisor of the largest number in A.
Important observation: All numbers in A are a multiple of GCD though.
We simply check the number of multiples of each A_i to see if it's less than K, and take maximum ans
NsqrtN time.

Might be too slow in which case we must use editorial solution which uses MlogM time.
Does not loop through every number for i, only loops through possible multiples/divisors.
outside loop d from 1 to M
    inner loop n from d to M adding d each time
time complexity: not M * (M/d) since d is changing.
Real time complexity: summation of M/d for all d from 1 to M
same as M summation of 1/d for all d from 1 to M. <- harmonic serioes
O(MlogM) time

think example: iterations M + (M/2) + (M/3)...
**NsqrtN solution doesn't work. TLE

*/

ll freq[1000001];
ll multiples[1000001];
ll ans[1000001];
ll input[1200001];

ll m = 0;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int nums, K;
    cin >> nums >> K;
    memset(freq, 0, sizeof(freq));

    for(ll i = 0; i < nums; i++){
        ll num;
        cin >> num;
        freq[num]++;
        m = max(m, num);
        input[i] = num;
    }

    for(ll i = 1; i <= m; i++){
        for(ll d = i; d <= m; d += i){
            multiples[i] += freq[d];
        }
    }

    for(ll i= 1; i <= m; i++){
        if(multiples[i] >= K){
            for(ll d = i; d <= m; d += i){
                ans[d] = max(ans[d], i);
            }
        }
    }

    for(ll i = 0; i < nums; i++){
        cout << ans[input[i]] << endl;
    }


}
