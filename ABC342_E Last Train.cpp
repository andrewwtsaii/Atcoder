#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
idea 1: Simple algorithm similar to DP. start at end instead of each starting node computing answer for all visited nodes.
for adjacent nodes to end take latest possible train. After that, find latest possible train to current node such that available train to end
store latest possible train for each node?
DP adjacent nodes use current node as answer. Directed graph. Reverse Edges?

obs 1: how to find closest train of adjacent node to latest time of current:
    - Check if c + l + (k-1)d > latest time
    - c + l + xd <= latest time
    - xd <= latest time - c - l
    - x <= (latest time - c - l)/d
    - ans = x * d + start Time

answer: f(s) latest time one can arrive at STATION S! in order to reach station N. (Not latest time to reach station N)
how to store information for each train? Multiple paths to same node
how to always optimize answer (prioritize certain paths). answer through current node might not be best option if adjacent node can go through different one
use ans[u] = max(ans[u], curr)? <- but need to revisit nodes

modified djikstras? priority queue sort nodes by something
sort nodes by highest answer? add to PQ, proessed instead of visited?

even if train arrives too early, we can wait until latest moment. if train arrives too late not possible
problem with multiple trains to and from same node <- how to store optimally? <- use class adjacent list uses class
*/

struct edge{
    ll startTime, difference, repeats, travelTime, node;

};
vector<edge> adj[200001];
ll ans[200001];

bool visited[200001];

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    for(int i = 0; i < 200001; i++){
        ans[i] = -1;
    }
    memset(visited, false, sizeof(visited));

    int stations, trains;
    cin >> stations >> trains;

    for(int i = 0; i < trains; i++){
        ll l, d, k, c, a, b;
        cin >> l >> d >> k >> c >> a >> b;

        struct edge tempEdge = {l, d, k, c, a};
        adj[b].push_back(tempEdge); //reverse edges;
    }

    priority_queue<pair<ll,ll>> q;
    q.push({1e18, stations});
    ans[stations] = 1e18;

    while(!q.empty()){
        ll s = q.top().second;
        ll f = q.top().first;
        q.pop();

        if(visited[s]){
            continue;
        }
        visited[s] = true;

        for(auto u: adj[s]){
            if(s == stations){
                ans[u.node] = max(ans[u.node], u.startTime + ((u.repeats - 1) * u.difference)); //use max since multiple edges may exit between 2 nodes
                q.push({ans[u.node], u.node});
            } else{
                ll x;
                if(u.travelTime + u.startTime > ans[s]){
                    continue;
                }
                x = ((ans[s] - u.travelTime - u.startTime)/u.difference);
                x = min(x, (ll)u.repeats - (ll)1);

                ll curr = ((x * u.difference) + u.startTime);
                if(curr <= ans[s] && curr >= u.startTime){
                    ans[u.node] = max(ans[u.node], curr);
                    q.push({ans[u.node], u.node});
                }
            }
        }
    }

    for(int i = 1; i < stations; i++){
        if(ans[i] == -1){
            cout << "Unreachable" << endl;
        } else{
            cout << ans[i] << endl;
        }
    }
}
