#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
N <= 10^14
we need to get ALL NUMBERS <= N that are good integers
even just linear time too slow. Probably something like sqrt(N) or log(N)

consider multiples (sqrt(N)) idea or similar

alternate problem: for each X find the # of multiples <= N with a digit sum = X
O(sqrt(N)) time if we can get answer in O(1)
no double counting since digit sum must be exactly X

prime factorization?

obs 1: numbers 1, 10, 100, 1000, 10000 are all good numbers with prime X = 1. ans += digits of N.
maybe we only need to consider odd/even numbers or divisibility? every number is either odd or even

thought of DP somehow getting answer from x-1 digits, but how?
--------------------------------------------------------------
after seeing editorial:
digit dp -> iterating over digits construct a number through its digits
learned from: https://codeforces.com/blog/entry/53960
https://www.geeksforgeeks.org/dsa/digit-dp-introduction/

generally we want DP to have our answer conditions as state parameters somehow

obs: we want to store the sum of each digit, and the remainder % sum of digits, length of number, original sum, if our current number is > N
key to problem: fix digit sum to X, then solve problem along all X. (similar approach to ours but how to do this?)
solving for a fixed number in this dp is easier since what we mod by doesnt change when adding digits
dp[d][s][j][f] = amount of good integers <= N with d # of digits (current position from right), s as the sum, j = number % s, f = 0 if we are < N otehrwise 1
with n being new digit
dp[d+1][s+n][(10j+n)%X][0 if f = 1 and n is < digits[d+1]] += dp[d][s][j][f]
j leftover, now becomes 10*j leftover since shifted to left add new digit

*hardest transition to come up with -> j

- generally adding/removing %s doesn't change value for all s
max sum = 9 * 14, 14 digits max value of 9 each


** TOUGH PROBLEM - Weak

memset writes value to all bytes, ex memset(dp, 1, sizeof(dp)) gives value of 1 to all bits in dp
memset is kind of slow for a lot of bytes especially in a nested for loop like dp table tabulation loops
better idea: redeclare dp vector, only of size we need each time, dont need to create max size dp data structure each time

problem encountered: RE -> max digits is not 14. 10^14 has 15 digits!

*/

ll N;

ll dp[16][127][126][2];
vector<ll> digits;
ll ans = 0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    cin >> N;

    while(N > 0){
        digits.push_back(N%10);
        N/=10;
    }

    reverse(digits.begin(), digits.end());

    for(ll X = 1; X <= 126; X++){
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][1] = 1; //new DP used for every set answer
        for(ll d = 0; d < (ll)digits.size(); d++){
            for(ll s = 0; s <= X; s++){
                for(ll m = 0; m < X; m++){
                    for(ll n = 0; n <= 9; n++){
                        if(s + n > X){
                            break;
                        }
                        dp[d+1][s+n][((10 * m) + n)%X][0] += dp[d][s][m][0];
                        if(n < digits[d]){
                            dp[d+1][s+n][((10 * m) + n)%X][0] += dp[d][s][m][1];
                        }
                    }
                    ll n = digits[d];
                    if(s + n > X){
                        continue;
                    }
                    dp[d+1][s+n][((10 * m) + n) % X][1] += dp[d][s][m][1];
                }
            }
        }
        ans += dp[digits.size()][X][0][0] + dp[digits.size()][X][0][1];
    }

    cout << ans << endl;


}
