#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll arr[1001][1001];
set<pair<ll, ll>> visited;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll rows, columns, D;
    cin >> rows >> columns >> D;

    queue<pair<pair<ll, ll>, ll>> q;
    for(ll r = 0; r < rows; r++){
        for(ll c = 0; c < columns; c++){
            char ch;
            cin >> ch;

            if(ch == 'H'){
                arr[r][c] = 2;
                q.push({{r, c}, 0});
            } else if(ch == '#'){
                arr[r][c] = 1;
            } else{
                arr[r][c] = 0;
            }
        }
    }

    ll output = 0;
    while(!q.empty()){
        pair<ll, ll> p = q.front().first;
        ll dist = q.front().second;
        ll r = p.first;
        ll c = p.second;

        q.pop();

        if(dist > D || visited.find({r, c}) != visited.end()){
            continue;
        }

        visited.insert({r, c});
        output++;
        //cout << r << " " << c << endl;

        if(r > 0 && arr[r-1][c] != 1){
            q.push({{r-1, c}, dist + 1});
        }

        if(r < rows - 1 && arr[r+1][c] != 1){
            q.push({{r+1, c}, dist + 1});
        }

        if(c > 0 && arr[r][c-1] != 1){
            q.push({{r, c-1}, dist + 1});
        }

        if(c < columns - 1 && arr[r][c+1] != 1){
            q.push({{r, c+1}, dist + 1});
        }
    }

    cout << output << endl;

}
