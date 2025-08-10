#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//naive approach: loop through each size, for each size get substring and take sum (doesn't work for larger numbers)
//idea: think of each digit seperately (similar idea comes from sum of all subarrays problem)
//size of string up to 2 * 10^5 (digits)
//maybe: sum up each digit seperately O(N) time aim <- hard to know how many times/which elements end up at each digit
//^^ need to determine how many times a number appears in specific position
//drawing out every substring reveals pattern in digits. i-th digit appears i times in every digit it appears in. Each digit appears in N - i + 1 digits.
//implementation: loop through each digit, incrementing stores sum of each digit
//efficiency improvement/realization: each digit misses one number (multiplied by x) less than previous
/*
example: 379
1: 9(3) + 7(2) + 3 = 27 + 14 + 3 = 44
2: 7(2) + 3 = 17
3: 3
3rd digit misses 7(2), 2nd digit misses 9(3)
*/
//problem answer too big for integer/ll
//store ans as string? digit sums can be stored as ll
//implementation idea*****: use modulus to deal with digits, simple and elegant implementation
//***basically full solve, needed help implementation of trivial problem (modulus implementation) <- was sleepy
ll arr[200001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int s;
    cin >> s;

    string input;
    cin >> input;

    ll prev = 0;
    for(ll i = s; i >= 1; i--){
        ll curr = (input[s - i] - '0');
        curr *= (s - i + 1);
        curr += prev;
        arr[i] = curr;
        prev = curr;
    }

    ll carry = 0;
    for (ll i = 1; i <= s; i++) {
        arr[i] += carry;
        carry = arr[i] / 10;
        arr[i] %= 10;
    }

    if(carry != 0){
        cout << carry;
    }


    for(ll i = s; i >= 1; i--){
        cout << arr[i];
        if(i == 1) cout << endl;
    }


}
