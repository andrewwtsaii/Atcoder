#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
obs 1: we can find out the optimal paths through simple traversal if we get the MST.
idea 1: after precomputing answers between all nodes, the problem can be solved by finding the minimum answer between all nodes to node Bi.
Whichever node is the minimum is matched from Ai to Bi.
idea 1 is probably too slow need to find answer faster.
obs 2: reduced to tree problem
obs 3: not solvable in O(N^2) cannot even loop N times for each N node.

idea 2: multi source modified djisktras. Pair up smallest answers closest nodes. Path weigth is = highest encountered path weight so far, just don't visit previous nodes -> tree
just matches nodes prioritizing smallest answer pairs first.
doesn't really work, can revisit nodes -> MST complex probably not correct

obs 4: if f(x, y) <= f(x, z) -> f(y, z) = f(x, z)
obs 5: if f(x, y) <= f(y, z) -> f(x, z) = f(y, z)
obs 6: f(x, y) defines a path from x to y with all weights <= w
obs 7: (from 4, 5) if we compare start nodes distance with each other maybe we can check the distances from each starting node to each ending in O(1)

---------------------------------------------------------
editorial:
pre-read: greedy start with no edge graph
sort weights in ascending order (close to idea of always taking smallest edges first)
treating weights in ascending order simplifies problem for us

treating weights in ascending order, if node z connects to a graph with x and y. f(x, z) and f(y, z) == edge between z and connected graph.
every time we connect nodes match A and B by adding  new B to currently available A's. Otherwise store B's for later?
since it is in increasing order it is always optimal to add available B's in current connected component to A as edges will only get bigger later.

solution: **use disjoint set and map to keep track of starts and finishes in each connected component

helpful tip: when thinking about greedy/sorting, does sorting make the answer simpler. In this case sorting edges made it so adding a node to a component
always made it optimal to connect all A's and B's in those components (ONLY BECAUSE EDGES ARE SORTED IN ASCENDING ORDER)
tip 2: always think possible solutions even if they involve more complex data structures/algos
*/

vector<pair<ll, pair<ll, ll>>> edgeV;
map<ll, ll> start;
map<ll, ll> finish;

ll r[200001];
ll disjointSet[200001];
ll ans = 0;

ll findSet(ll d){
    if(d != disjointSet[d]){
        disjointSet[d] = findSet(disjointSet[d]);
    }
    return disjointSet[d];
}

void combine(ll x, ll y, ll weight){
    x = findSet(x);
    y = findSet(y);

    if(r[x] > r[y]){
        disjointSet[y] = x;
        start[x] += start[y];
        finish[x] += finish[y];

        ans += (min(start[x], finish[x])) * weight;
        ll temp = min(start[x], finish[x]);
        start[x] -= temp;
        finish[x] -= temp;
    } else{
        disjointSet[x] = y;
        start[y] += start[x];
        finish[y] += finish[x];
        if(r[x] == r[y]){
            r[y]++;
        }
        ans += (min(start[y], finish[y])) * weight;
        ll temp = min(start[y], finish[y]);
        start[y] -= temp;
        finish[y] -= temp;

    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes, edges, K;
    cin >> nodes >> edges >> K;

    for(ll i = 0; i < edges; i++){
        ll a, b, w;
        cin >> a >> b >> w;
        edgeV.push_back({w, {a, b}});
    }

    for(ll i = 0; i < K; i++){
        ll num;
        cin >> num;
        start[num]++;
    }

    for(ll i = 0; i < K; i++){
        ll num;
        cin >> num;
        finish[num]++;
    }

    for(ll i = 1; i <= nodes; i++){
        disjointSet[i] = i;
        r[i] = 0;
    }

    sort(edgeV.begin(), edgeV.end());

    for(ll i = 0; i < edges; i++){
        ll a = edgeV[i].second.first;
        ll b = edgeV[i].second.second;

        if(findSet(a) == findSet(b)){
            continue;
        } else{
            combine(a, b, edgeV[i].first);
        }
    }

    cout << ans << endl;




}
