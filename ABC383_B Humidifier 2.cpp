#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll val[10][10];
int arr[10][10];

set<pair<ll, ll>> visited;
vector<pair<ll, ll>> starts;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll H, W, D;
    cin >> H >> W >> D;

    memset(val, 0, sizeof(val));

    for(ll r = 0; r < H; r++){
        for(ll col = 0; col < W; col++){
            char c;
            cin >> c;
            if(c == '#'){
                arr[r][col] = 1;
            } else{
                arr[r][col] = 0;
                starts.push_back({r, col});
            }
        }
    }

    ll output = 0;

    for(ll i = 0; i < starts.size(); i++){
        queue<pair<pair<ll, ll>, ll>> q;

        for(ll j = i + 1; j < starts.size(); j++){
            ll curr = 0;
            q.push({{starts[i].first, starts[i].second}, 0});
            q.push({{starts[j].first, starts[j].second}, 0});

            while(!q.empty()){
                pair<ll, ll> p = q.front().first;
                ll d = q.front().second;
                q.pop();

                ll r = p.first;
                ll c = p.second;

                if(d > D){
                    continue;
                }
                if(visited.find({r, c}) != visited.end()){
                    continue;
                }

                if(arr[r][c] == 0){
                    curr++;
                }
                visited.insert({r, c});

                if(r > 0 && visited.find({r-1, c}) == visited.end()){
                    q.push({{r-1, c}, d + 1});
                }
                if(r < H - 1 && visited.find({r+1, c}) == visited.end()){
                    q.push({{r + 1, c}, d+1});
                }

                if(c > 0 && visited.find({r, c-1}) == visited.end()){
                    q.push({{r, c-1}, d + 1});
                }

                if(c < W - 1 && visited.find({r, c+1}) == visited.end()){
                    q.push({{r, c+1}, d+1});
                }
            }

            visited.clear();
            output = max(output, curr);
        }
    }

    cout << output << endl;



}
