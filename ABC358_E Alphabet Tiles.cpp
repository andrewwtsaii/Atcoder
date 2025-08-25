#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
K and Ci really small. Solvable in O(K*Ci*26) time
brute force solution: For each i from 1 to K. find out every possibility of picking letters. For each combination find every rearrangement.

idea 1: maybe think of how many strings can letter x if used y times be a part of?

is this DP?
dp[a][b][c] = ways to use letter a, in a string of size b if used c times.
O(N^2) transition, no relationship between letters. need to prevent double counting.

dp[a][b][c] = strings of size a where letter b is in character c. need to prevent double counting

dp[a][b][c] = strings of size a where letter b is used first and to a maximum of c times.
maybe consider strings of size a inserted before/after strings of size a+1 to use dp to solve.
dp[a][b][c] = dp[a-1][b][c-1] + dp[a-1][b][c] for all other b

obs 1: if we have the answer for all strings of size a, we can determine all strings of size a + 1 easier.
O(K^2 * 26 * 26)

dp idea with above transitions don't work. Considers invalid strings.
example: if we consider strings of size a-1 where the first letter is not b. It may include b input[b] times making that string invalid.
it only considers the cap on one letter at a time.

DP is right idea*
note that if a appears ta times, b tb times, etc. The number of permutations is n!/ta!tb!...
------------------------------------------------------------------------------------------------
Editorial Solution: consider number of strings for every possible occurence of the letter z.
If a string of size s has t occurence of the letter z. the letter z has s choose t ways to be placed. the characters at the other positions
forms a string of size s-t without the letter z, such that ai occurs between 0 and Ci. This turns into a problem of only characters between a, and y.
this hints at DP. (subproblems)
dp[i][j] = # of valid strings of length j consisting of the first i letters of the alphabet such that ak occurs between 0 and Ck times for all 1 <= k <= i
dp[i][j] = dp[i-1][j-k] * j choose K for all valid k from 0 to min(c[i], j)
*combo problems often need the inverse factorial and factorial precomputation
tough problem -> combinatorics

*/

ll input[27];
ll facts[1001];
ll invFacts[1001];
ll dp[27][1001];

ll mod = 998244353;

ll power(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1){
            res = ((res * a) % mod);
        }
        a = ((a * a) % mod);
        b >>= 1;
    }
    return res;
}

void precompute(){
    facts[0] = invFacts[0] = 1;
    for(int i = 1; i < 1001; i++){
        facts[i] = ((facts[i-1] * i) % mod);
        invFacts[i] = power(facts[i], mod - 2);
    }

}
ll choose (ll n, ll k){
    if(n < 0 || k < 0 || k > n){
        return 0;
    }
    return (facts[n] * invFacts[k] % mod) * invFacts[n-k] % mod;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll K;
    cin >> K;

    for(ll i = 1; i <= 26; i++){
        cin >> input[i];
    }

    ll ans = 0;
    memset(dp, 0, sizeof(dp));

    precompute();

    dp[0][0] = 1; //although dp is valid strings, we set base case to 1. since our answer builds off of this. valid rearrangements of empty string is 1 (this isn't included in our answer anyways)

    for(ll i = 1; i <= 26; i++){
        for(ll j = 0; j <= 1000; j++){
            for(ll k = 0; k <= min(input[i], j); k++){
                dp[i][j] = (dp[i][j] + dp[i-1][j-k] * choose(j,k)) % mod;
                /*
                ***note the same as dp[i][j] += ((dp[i-1][j-k] * choose(j, k))%mod);
                you should mod again after dp[i][j] = dp[i][j] % mod;
                */
            }
        }
    }

    for(ll j = 1; j <= K; j++){
        ans += (dp[26][j] % mod);
    }

    cout << (ans % mod) << endl;


}
