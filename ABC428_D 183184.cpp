#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
**** TRICKY ******
****CONCATENATION TO MATHEMATICAL EXPRESSION TRICK****
****OTHER TRICKS*****
D super large. Can't even loop through D
probably some mathematical property??

------------------------------------------Editorial
can think of concatenation as arithmetic
f(C, C+x) = C*(10^K) + (C+x) where K is the digits of C + x
if K is fixed, this is a linear function of X. Finding when it's a perfect square is counting
    perfect squares in an interval.

C+x must have k digits.
1 <= x <= D.

10^(k-1) <= C + x <= 10^k - 1

x has up to 10 digits.
C + x has up to 10 digits. (C <= (2 * 10^8))

since we have bounds on C + x we can find the number of squares between the bounds of C + x.
We can do this by finding the closest square roots outside the interval and using math to find the number
of perfect squares in the interval.

We want n^2 in [a, b]

a <= n^2 <= b
sqrt(a) <= n <= sqrt(b)
ceil(sqrt(a)) <= n <= floor(sqrt(b))

note: floor(sqrt(a)) could be out of the range of the interval.
n = floor(sqrt(a)) can result in it being < sqrt(a)

sqrts in interval is floor(sqrt(b)) - ceil(sqrt(a)) + 1

concatenated value = C*(10^K) + C + x
x is in [1, D]
C+1 <= C + x <= C+ D
10^(k-1) <= C + x <= 10^k - 1
intersect them

lower bound: max(C+1, 10^(k-1))
upper bound: min(C+D, 10^k - 1)

similar idea to why we ceil  sqrt(a) and floor sqrt(b)

we need a custom sqrt function to handle larger inputs
isqrt(x) = perfect squares in [1, x]
largest k where k^2 >= x
isqrt(x) = floor(sqrt(x))

perfect squares in [1, b] - perfect squares in [1, a-1] gives
perfect squares in [a, b]

note: can't use pow for larger inputs, returns double 'damage done before casting to ll'
---------------------------------------------------------

HARD INITIAL START.

MAIN IDEA: CONCATENATION CAN BE REPRESENTED AS ARITHMETIC
*/

ll isqrt(ll x) {
    ll r = (ll)sqrtl((long double)x);
    while (r * r > x) {
        r--;
    }
    while ((r+1) * (r+1) <= x) {
        r++;
    }
    return r;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();


    ll tests;
    cin >> tests;

    for(ll t = 0; t < tests; t++){
        ll C, D;
        cin >> C >> D;

        ll digits = 0;
        ll ans = 0;

        ll digitCheck = C + D;
        while(digitCheck > 0){
            digits++;
            digitCheck/=10;
        }

        ll p = 1;
        for(ll k = 1; k <= digits; k++){
            p *= 10;
            ll lo = max(C + 1, p/10);
            ll hi = min(C + D, p - 1);
            if(lo > hi){
                continue;
            }
            ll a = C * p + lo;
            ll b = C * p + hi;

            //isqrt = floor
            //isqrt(a-1) = ceil(isqrt(a)) - 1
            ans += (isqrt(b) - isqrt(a-1));
        }

        cout << ans << endl;
    }
}
