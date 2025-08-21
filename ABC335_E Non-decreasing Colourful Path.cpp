#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
first thoughts: similar problem to sightseeing tour? DP + graph theory
ans[adj[a]] may be related to ans[a]
ans[a] may be related to ans of nodes a is adjacent to.

obs 1: of a current path we only need to store most recent node to keep path non-decreasing, since only the largest number matters.
if a path stops being non-decreasing set it to -1.

greedy probably won't work. Always taking shortest may lead to shorter path, compared to a longer path with more distinct node numbers

idea 1: can we use priority queue or somehow use BFS where visiting nodes we already have in our Set counts as weight 0. (Need to account for non
decreasing order as well)
modified djikstras? Edge weights are difference between nodes? or 0 if node already exists

need max score not min score -> djikstras prolly does not work

idea 2: Maybe we can use DP, dp[i] = max score from node 1 to i
-> use BFS to visit nodes and update answer. If answer doesn't update to better one (either better answer or smaller number) don't add to queue
problem: how to make only simple paths?
need a 2D visited array somehow -> do we need one? Must be non increasing, keeping same won't increase answer (but eventually could). If we
increase number we must decrease to go back to non simple path, but how to prevent same path length taken?
some 2D array idea? how to keep in memory constraints?
idea 2B: no 2D array needed, if node # same just check if answer improved

queue only needs two numbers, node and path length. With node number we can see largest number (if it is no longer non decreasing it won't be in queue)
path must be non-decreasing makes problem easier for us, onyl need to keep track of last node (obs 1)

idea 2 Formalized:
important observations:
- Once we move to a higher number node, it is impossible to revisit the previous node without becoming non decreasing.
- We only need to keep track of the previous node in order to keep our path non decreasing
- If we keep an array dp of the best answers currently of our nodes, we solve by pushing pairs into the queue of the last node and current answer
- If an adjacent node has the same or smaller dp answer as current it's already visited by the current path or is not optimal to add to queue.
- dp[u]  is also the best answer at node u with path length arr[u] -> we don't need to check if dp[u] == curr ans because then it's 100% already visited
and the highest number is the same

important note: in modified BFS check if answer will improve, otherwise dont modify DP just add to queue. Use queue second value for this, since
you cannot use the optimal answer for node must be the answer of that specific path.

idea 2 TLE's. How to optimize -> probably something with visited array, same paths might be visited multiple times...
-If we are checking an adjacent node and the DP value is >= the calculated answer from current path we don't need to push to queue. It is guarnateed
the maximum number in sequence is the same since numbers are on nodes not edges.

might have to be optimized by using no BFS, currently we revisit nodes multiple times, we only want to visit once with optimal path.
something similar to djikstra or prioritizing certain edges.

optimizaiton possibility: change graph to directed, only have an edge to larger or equal node values.

idea priority queue by node numbers, smallest first.
it turns out the above works!
proof -> (by contradiction) if it is more optimal to visit a node that isn't the current smallest we would have to go to a larger node, and then back down.
if it would be more optimal to take a different route for later on, the node later on would have to be reached after for both paths since you must start
at a smaller number

HOWEVER -> if there is a tie (equal next nodes, maximize the second value prioritize we want maximum answer for first visit) -> custom sorter
modified djikstra* process answer based off of node values not edge weights
problem can be greatly simplified.

** When an idea comes up make sure to see contradiction case all the way through before scrapping
*/

int arr[200001];
int ans[200001];
bool visited[200001];

struct cmp{ //custom compare syntax -> different than sort which is a function, priority queue is a 'class template', struct cmp gives a type struct to pq. bool () would give a pointer to a function returning bool
    bool operator()(pair<int, int> a, pair<int, int> b){
        if(arr[a.first] == arr[b.first]){
            return a.second < b.second;
        }
        return arr[a.first] > arr[b.first];
    }

};

priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q;
vector<int> adj[200001];

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes, edges;
    cin >> nodes >> edges;

    for(ll i = 1; i <= nodes; i++){
        cin >> arr[i];
        ans[i] = -1;
    }

    for(ll i = 0; i < edges; i++){
        ll a, b;
        cin >> a >> b;
        if(arr[a] < arr[b]){
            adj[a].push_back(b);
        } else if(arr[a] > arr[b]){
            adj[b].push_back(a);
        } else if(arr[a] == arr[b]){
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    q.push({1, 1});
    ans[1] = 1;
    while(!q.empty()){
        pair<int, int> s = q.top();
        q.pop();

        //cout << s.first << " " << s.second << " D" << endl;
        if(visited[s.first]){
            continue;
        }
        visited[s.first] = true;
        //cout << s.first << " " << s.second << " E" << endl;

        for(auto u: adj[s.first]){
            if(arr[u] > arr[s.first] && ans[u] < s.second + 1){ //if ans[u] >= s.second + 1 not optimal to add to queue
                ans[u] = s.second + 1;
                q.push({u, s.second + 1});
            } else if(arr[u] == arr[s.first] && ans[u] < s.second){ //if ans[u] >= s.second not optimal to add to queue
                ans[u] = s.second;
                q.push({u, s.second});
            }
        }
    }
    if(ans[nodes] == -1){
        cout << 0 << endl;
    } else{
        cout << ans[nodes] << endl;
    }
}
