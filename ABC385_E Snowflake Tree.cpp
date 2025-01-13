#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
snowflake trees all have radius of 2
find all XY nodes possible of each node
take total notes substract
for every node find best XY adj
*/

//pair<ll, ll> xy[300001];
vector<ll> adj[300001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes;
    cin >> nodes;

    for(ll i = 0; i < nodes - 1; i++){
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ll output = 1000000000000000;
    for(ll i = 1; i <= nodes; i++){
        ll y = -1;
        ll x = adj[i].size();
        priority_queue<ll> pq;

        for(auto u: adj[i]){
            pq.push((adj[u].size()-1) * (-1));
        }

        y = pq.top() * (-1);

        output = min(output, nodes - (x + (x * y) + 1));

        while(!pq.empty()){
            pq.pop();

            y = pq.top() * (-1);
            x--;

            output = min(output, nodes - (x + (x * y) + 1));
        }

        //cout << i << " " << output << endl;

    }

    cout << output << endl;


}
