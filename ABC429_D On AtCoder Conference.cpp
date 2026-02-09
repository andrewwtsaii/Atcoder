#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
constraints on M really long
idea: we can use N somehow by keeping everyone sorted
Maybe we use binary search as well with total of N logN time?

we need to print the sum of all numbers between 1 and M. Answer doesn't change for any number between A_i and A_i+1. We just
have to be careful of cases inclusive and exclusive. Cases exclusive of boundarys we can multiply by difference between
A_i+1 and A_i

instead of binary search use PSA? some how use circular PSA to quickly calculate sums? Won't work not fast enough?
PSA + binary search???
too complex probably?

sliding window?

implementation help: mod idea for circular things. distance from a to b on a circle (a - b + M)%M
idea: use sliding window looping through people (N) and calculate for all other nodes with multiplication and subtraction

to get previous point (l - 1 + points.size()) % points.size()

general circular distance/info formula: (a - b + size) % size
clockwise distance + counterclockwise distance = circumference
forward = size - backward

if backwards < 0 then its - backward. otherwise adding size won't do anything after modding

if the gap is 0 between current point and previous point htere is only one point

*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N, M, C;
    cin >> N >> M >> C;

    map<ll, ll> freq;
    set<ll> circle;
    for(ll i = 0; i < N; i++){
        ll num;
        cin >> num;
        freq[num]++;
        circle.insert(num);
    }

    ll ans = 0;
    auto lft = circle.begin(), rht = circle.begin();

    ll currSum = freq[*circle.begin()];
    //inputs
    for(auto u: circle){
        if(u != *circle.begin()){
            currSum -= freq[*lft];
            lft = next(lft);
        }

        while(currSum < C){
            rht = next(rht);
            if(rht == circle.end()){
                rht = circle.begin();
            }
            currSum += freq[*rht];
        }

        if(lft == circle.begin()){
            ll gap = (*lft - *prev(circle.end()) + M)%M;

            if(gap == 0){ //only one point
                gap = M;
            }
            ans += (currSum * gap);
        } else{
            ll gap = (*lft - *prev(lft) + M)%M;
            if(gap == 0){ //only one point
                gap = M;
            }
            ans += (currSum * gap);
        }

        /*if(lft == rht){
            rht = next(rht);
        }*/

    }

    cout << ans << endl;

}
