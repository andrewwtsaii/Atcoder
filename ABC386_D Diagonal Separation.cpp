#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
harder than original idea
ex
E E E E
E E E E
W E E E
E E B E

all cells above and left B must be black
all cells below and right W must be white
if intersection impossible
if cell is white all cells with col >= wc and row >= wr impossible

possible idea: go thorugh all coords from bottom right to top left
if white check out of black cells so far check if one exists with col greater, maybe not needed: and check if one exists with row greater
*/

vector<pair<pair<ll, ll>, char>> combine;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N, M;
    cin >> N >> M;

    for(ll i = 0; i < M; i++){
        ll a, b;
        char c;
        cin >> a >> b >> c;

        if(c == 'B'){
            combine.push_back({{a, b}, 'B'});
        } else{
            combine.push_back({{a, b}, 'W'});
        }
    }

    sort(combine.begin(), combine.end());
    reverse(combine.begin(), combine.end());
    bool possible = true;

    ll maxBlackC = -1;
    for(auto u: combine){
        if(u.second == 'B'){
            maxBlackC = max(maxBlackC, u.first.second);
        } else{
            if(maxBlackC >= u.first.second){
                possible = false;
                break;
            }
        }

    }

    if(possible){
        cout << "Yes" << endl;
    } else{
        cout << "No" << endl;
    }
}
