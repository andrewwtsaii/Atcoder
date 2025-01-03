#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
need to count houses in a specific range at specific X/Y coord
X/Y up to 10^9, idea: use map
binary search to get numbers in range
erasing houses from set does not take a long time since at most M houses removed! very close solve
set syntax problem
*/

map<ll, set<ll>> mx;
map<ll, set<ll>> my;
ll output = 0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll houses, movements, X, Y;
    cin >> houses >> movements >> X >> Y;

    for(ll i = 0; i < houses; i++){
        ll ix, iy;
        cin >> ix >> iy;

        mx[ix].insert(iy);
        my[iy].insert(ix);
    }


    for(ll i = 0; i < movements; i++){
        char D;
        ll c;
        cin >> D >> c;
        if(D == 'L'){
            //binary search on curr Y coord
            auto it = my[Y].lower_bound(X-c);
            while(it != my[Y].end() && *it <= X){
                output++;
                mx[*it].erase(Y);
                it = my[Y].erase(it);
            }

            X -= c;
        }
        if(D == 'R'){
            auto it = my[Y].lower_bound(X);
            while(it != my[Y].end() && *it <= X + c){
                output++;
                mx[*it].erase(Y);
                it = my[Y].erase(it);
            }

            X += c;
        }
        if(D == 'U'){
            auto it = mx[X].lower_bound(Y);
            while(it != mx[X].end() && *it <= Y + c){
                output++;
                my[*it].erase(X);
                it = mx[X].erase(it);
            }
            Y += c;
        }
        if(D == 'D'){
            auto it = mx[X].lower_bound(Y - c);
            while(it != mx[X].end() && *it <= Y){
                output++;
                my[*it].erase(X);
                it = mx[X].erase(it);
            }
            Y -= c;
        }
    }

    cout << X << " " << Y << " " << output << endl;
}
