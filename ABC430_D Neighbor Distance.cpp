#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
simple problem
use some data structure to keep positions sorted, check left and right only

idea: insert data into some sorted structure modify answer only modifying 3 answers.
all numbers given to be distinct

Cannot add at beginning since 0 is in set
case 1: adding at end: remove old answer for a_i-1. Add min a_i - a_i-1 and a_i-1 - a_i-2 to answer.
Edge case: a_i-1 is the first number.   ans -= a_i-1;
                    ans += min(a_i - a_i-1, a_i-1);

case 2: adding in middle: subtract answer for a_i+1. Add min a_i+2 - a_i-1.
Remove answer for a_i-1. Add min a_i-1 - a_i-2. Handle edge cases where a_i+2 or a_i-2 is out of set range

KEY IDEA: Only 3 numbers answers modified per insertion. Use set
and iterator syntax to solve

subtract accordingly. note edge cases where the size initially is small.
*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N;
    cin >> N;

    set<ll> s;
    s.insert(0);

    ll ans = 0;
    for(ll i = 0; i < N; i++){
        ll num;
        cin >> num;

        s.insert(num);

        /*cout << "SET: ";
        for(auto u: s){
            cout << u << " ";
        }
        cout << endl;*/
        if(i == 0){
            ans = (num * 2);
        } else if(i == 1){
            auto it = s.begin();
            ll gap1 = *next(it) - *it;
            ll gap2 = *next(next(it)) - *next(it);
            ll minDiff = min(gap1, gap2);
            ll maxDiff = max(gap1, gap2);
            ans = 2 * minDiff + maxDiff;
        } else{
            auto it = s.lower_bound(num);

            ll num1 = -1;
            ll num = (*it);
            ll num2 = -1;

            if(it != s.begin()){
                num1 = (*prev(it));
            }
            if(next(it) != s.end()){
                num2 = (*next(it));
            }

            if(num1 != -1){
                if(num2 != -1){
                    ans += min(num - num1, num2 - num);
                } else{
                    ans += num - num1;
                }
            } else{
                if(num2 != -1){
                    ans += num2 - num;
                }
            }

            if(next(it) == s.end()){
                auto temp = prev(it);
                if(temp != s.begin()){
                    if(num - num1 < num1 - *prev(temp)){
                        ans -= (num1 - *prev(temp));
                        ans += (num - num1);
                    }
                } else{
                    ans -= num1;
                    ans += min(num - num1, num1);
                }

            } else{
                auto temp = next(it);
                if(next(temp) != s.end()){
                    ans -= min(num2 - num1, *next(temp) - num2);
                    ans += min(num2 - num, *next(temp) - num2);
                } else{
                    ans -= (num2 - num1);
                    ans += (num2 - num);
                }

                temp = prev(it);
                if(temp != s.begin()){
                    ans -= min(num2 - num1, num1 - *prev(temp));
                    ans += min(num - num1, num1 - *prev(temp));
                } else{
                    ans -= (num2 - num1);
                    ans += (num - num1);
                }

            }


        }
        cout << ans << endl;
    }



}
