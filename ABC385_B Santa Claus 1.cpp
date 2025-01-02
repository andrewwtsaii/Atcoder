#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll H, W, X, Y;
int grid[101][101];

set<pair<ll, ll>> visited;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    cin >> H >> W >> Y >> X;

    X--;
    Y--;
    for(ll r = 0; r < H; r++){
        string input;
        cin >> input;
        for(ll c = 0; c < W; c++){
            if(input[c] == '#'){
                grid[r][c] = 1;
            } else if(input[c] == '.'){
                grid[r][c] = 0;
            } else{
                grid[r][c] = 2;
            }
        }
    }

    string t;
    int houses = 0;
    cin >> t;

    if(grid[Y][X] == 2){
        houses++;
        visited.insert({Y, X});
    }
    for(ll i = 0; i < t.size(); i++){
        if(t[i] == 'U'){
            if(grid[Y-1][X] != 1){
                Y--;
            }
            if(grid[Y][X] == 2){
                if(visited.find({Y, X}) == visited.end()){
                    visited.insert({Y, X});
                    houses++;
                }
            }
        }
        if(t[i] == 'D'){
            if(grid[Y+1][X] != 1){
                Y++;
            }
            if(grid[Y][X] == 2){
                if(visited.find({Y, X}) == visited.end()){
                    visited.insert({Y, X});
                    houses++;
                }
            }
        }
        if(t[i] == 'L'){
            if(grid[Y][X-1] != 1){
                X--;
            }
            if(grid[Y][X] == 2){
                if(visited.find({Y, X}) == visited.end()){
                    visited.insert({Y, X});
                    houses++;
                }
            }
        }

        if(t[i] == 'R'){
            if(grid[Y][X+1] != 1){
                X++;
            }
            if(grid[Y][X] == 2){
                if(visited.find({Y, X}) == visited.end()){
                    visited.insert({Y, X});
                    houses++;
                }
            }
        }
    }

    Y++;
    X++;
    cout << Y << " " << X << " " << houses << endl;

}
