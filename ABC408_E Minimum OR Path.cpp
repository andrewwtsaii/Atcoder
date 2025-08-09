#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//obs 1: bit value higher than sum of all bits to left
//obs 2: djikstra modification doesn't work on sample case 2 (try ideas on all sample cases)
//obs 3: any number OR K results in a number <= K if the number has a different set bit
//brute force idea: test if it is possible only using weights that give an | <= K for all possible K. (subsets of 30 bits)
//** key idea to optimize brute force: if X is valid then X | 2^K is also valid (ie, adding the Kth bit is also valid)
//idea: set X = 2^30 - 1 (max ans), try and turn off the K-th bit starting from the biggest (x-2^k valid check) if it is new ans is x - 2^k and keep going
//this results in only 30 bfs checks (we prioritize turning off higher bits first and loop down)
//** main point: not all subsets need to be checked, smarter to loop down turning off highest bits first
//greedy
//*bitwise operation precedence is low use brackets especially in if statements
//a & ~b keeps set bits in a and ~b -> keeps set bits in a and non set bits in b (~ flips bits) <- NOT operator

vector<pair<ll, ll>> adj[200001];
bool visited[200001];

ll ans = pow(2, 30) - 1;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes, edges;
    cin >> nodes >> edges;

    for(ll i = 0; i < edges; i++){
        ll a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    for(ll k = 29; k >= 0; k--){
        memset(visited, false, sizeof(visited));
        queue<pair<int, int>> q;
        q.push({1, 0});
        visited[1] = true;
        while(!q.empty()){
            pair<ll, ll> n = q.front();
            q.pop();

            //0 0 1 0 0 1
            //1 0 1 0 0 1
            for(auto u: adj[n.first]){
                if(visited[u.first]){
                    continue;
                }
                ll check = ans - pow(2, k);
                if((u.second & ~check) != 0){ //if set bit in W not in ans - 2^k
                    continue;
                }
                visited[u.first] = true;
                q.push(u);
            }
        }

        if(visited[nodes]){
            ans -= (pow(2, k));
        }
    }


    cout << ans << endl;

}
