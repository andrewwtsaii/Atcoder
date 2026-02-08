#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
simple problem
use some data structure to keep positions sorted, check left and right only

idea: insert data into some sorted structure modify answer only modifying 3 answers.
all numbers given to be distinct

case 1: adding at end: add a_i - a_i-1 to answer. Compare a_i-1 - a_i-2 to a_i - a_i-1 for second addition
case 2: adding at beginning: add a_i - ai+1 to answer. Compare a_i+1 - a_i+2 to a_i - a_i+1 for second addition
case 3: adding in middle: add min(a_i - a_i-1, a_i - a_i+1) to answer. compare (a_i - a_i-1, a_i-1 - a_i-2) and
(a_i - a_i+1, a_i+1 - a_i+2)

^^Some mistakes had to modify accordingly. KEY IDEA: Only 3 numbers answers modified per insertion. Use set
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
                    /*if(num - num1 < num1 - *prev(temp)){
                        ans -= (num1 - *prev(temp));
                        ans += (num - num1);
                    }*/
                    ans -= (num1 - *prev(temp));
                    ans += min(num - num1, num1 - *prev(temp));
                } else{
                    //ans += (num - num1);
                    ans -= num1;
                    ans += min(num - num1, num1);
                }

            } else{
                auto temp = next(it);
                if(next(temp) != s.end()){
                    //compare = *next(temp) - num2;
                    //compare = min(compare, num2 - num1);
                    /*if(num2 - num < *next(temp) - num2){
                        //ans -= (compare);
                        ans -= (*next(temp) - num2);
                        ans += (num2 - num);
                    } else if(num2 - num1 < *next(temp) - num2){
                        ans += (*next(temp) - num2);
                        ans -= (num2 - num1);
                    }*/
                    ans -= min(num2 - num1, *next(temp) - num2);
                    ans += min(num2 - num, *next(temp) - num2);
                } else{
                    ans -= (num2 - num1);
                    ans += (num2 - num);
                }

                temp = prev(it);
                if(temp != s.begin()){
                    //compare = num1 - *prev(temp);
                    //compare = min(compare, num2 - num1);
                    //cout << "X: " << num - num1 << " " << num1 - *prev(temp) << endl;
                    /*if(num - num1 < num1 - *prev(temp)){
                        ans -= (num1 - *prev(temp));
                        ans += (num - num1);
                    } else if(num2 - num1 < num1 - *prev(temp)){
                        ans += (num1 - *prev(temp));
                        ans -= (num2 - num1);
                    }*/
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
