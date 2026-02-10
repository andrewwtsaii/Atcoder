#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
if a string is all 1's it is 'beautiful'

we want consecutive 0's and 1's
odd number of 0s is 'bad', even number of 0s is good

odd number of 0's as a block can turn into even
ex 111000101 -> 1000101 -> 100001 -> 1111
can compress string so that consecutive 1's turn into a single 1?


011011100101110111100010011010

i = 0,x = 0: impossible
i = 1, x = 1: adding a 1, still impossible
i = 2, x = 1: adding a 1, impossible
i = 3, x = 0: adding a 0, possible
^ correct thinking approahc? we need to check all substrings not just substrings starting at i = 0

^^ 1's dont affect answer?

sliding window? Probably not, we don't know when to advance left or right

----Editorial hint using below
HELPFUL: With string problems its helpful to look for an invariant, remains constant by any operation

00 reduces 0's by 2
01 redcues 1's by 1 -> deletes 1 0's same
10 redcues 1's by 1 -> deletes 1 0's same
11 reduces 1's by 1 -> deletes 1 0's same
----- Editorial hint ends

011011100101110111100010011010
we want the frequency of 1's to change to 1 and frequency of 0's to change to 0
01 freq[0] = 1 freq[1] = 1 impossible
011 freq[0] = 1 freq[1] = 2
we want to reduce 1's by 1 and 0's by 1
we must have a 00 conseuctively
011: impossible
0110: freq[0] = 2, freq[1] = 2
we want to reduce 1's by 1, and 0's by 2
01, 10 and 11 essentially do the same thing
01101: freq[0] = 2, freq[1] = 3
possible

adding 1 to end doesn't change answer: 11 -> 1 easily. 01-> can only turn into 0 or 0 turns into 1 giving 11->1
01101110
freq[0] = 3, freq[1] = 5

possibility: adding 0 to end swaps answer, adding 1 to end keeps answer the same.
idea: count number of swaps from 0 to 1 in input. For each number calculate swaps after that number?

need proof for: adding 0 swaps answer, adding 1 keeps answer same
string + 1. lets say it changes to string + 0 + 1 -> string + 0 doesn't change aynthing
lets say it changes to string + 1 + 1 -> string + 1 same as before

no affect
string + 0. Lets say it changes to string + 0 + 0 -> changes to string + 1. compressed string + 1. continues
lets say it changes to string + 1 + 0 -> string + 0. Stays the same
0111 -> 01110 -> 110 ->10

new thought: using hint we want to reduce 0's to 0. We need 00

001010100011
freq[0] = 6

idea: remove all 1's seperating 0's?
000000011
111011
impossible

00011000
000000
possible

--Editorial hint 2
parity stays the same -> invariant
So obvious from hint 1 idk how i missed it

------------
if 0s % 2 == 1: impossible
if 0s % 2 == 0: possible

need number of strings with parity of 0s == 0

if 0: even substrings ending at i = odd substrings ending at previous 0
if 1: even substrings ending at i = even substrings ending at i-1

idea: precompute 1's between 0s?

idea: use dp as in above. Based on 0 current or 1 current modify odd zeroes/even zeroes
increment ans by odd zeroes if 0 is current (now even) , increment ans by even zeroes if currently 1.

this solution uses space effective dp since we only need to store the previous odd and even answers
*/

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N;
    cin >> N;

    string T;
    cin >> T;

    ll ans = 0;
    ll evenZeroes = 0;
    ll oddZeroes = 0;
    ll evenTemp = 0;
    ll oddTemp = 0;
    //01101110
    //0001110001000000
    if(T[0] == '0'){
        oddZeroes++;
    } else{
        evenZeroes++;
        ans += evenZeroes;
    }

    for(ll i = 1; i < T.size(); i++){
        if(T[i] == '0'){
            ans += oddZeroes;
            ll temp = oddZeroes;
            oddZeroes = evenZeroes;
            evenZeroes = temp;
            oddZeroes++;
        } else{
            evenZeroes++;
            ans += evenZeroes;
        }
    }

    cout << ans << endl;

}
