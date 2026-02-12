#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
we want to always visit smallest node (unless that node cannot reach the final node without revisiting a node)
size is not priority for lexicographically smallest.
Path is most significant number to least significant, if tie then size matters

going from reverse won't help since it starts with least significant going in reverse order

idea (greedy): Go through nodes from start check all neighbours starting from the smallest. If that node can reach the end
with only nonvisited nodes we are done.

a bit of help/peek (had idea already): weird idea with bfs and dfs kind of. Double traversal?

pretty straightforward problem

an optimization that may have to be made: instead of using BFS for the first graph traversal only one node
is needed to be stored at a time. So we can use a simple variable and while loop

instead of setting visitedTemp boolean variable to visited one by one, use memcpy (optimized library function for speed)

note: sets have high constant factors, vectors are find just sort
***PRIORITIZE TIME COMPLEXITY FOR LARGER N  , PRIORITIZE CONSTANT FACTORS IN OTHER CASES AND WHEN COMPLEXITY MAKES SENSE BUT YOU GET TLE
*****IN this problem set for adj TLEs but vector + sorting passes
note: overall time complexity is the same since we only sort once per test case and insertion is quick for vector, longer for set
set has higher constant factor******

HUGE OPTIMIZATION: if it fails to reach the end, all nodes it does reach are also unable to reach the end point so we can
mark them all as visited.

MAIN OPTIMIZATION IDEA: if a node in a connected component cannot reach a specific node, that entire connected component cannot reach that specific node.
*/

bool visitedTemp[1001];
bool visited[1001];

ll nodes, edges, X, Y;
vector<ll> adj[1001];

void dfs(ll s){

    if(visitedTemp[s]){
        return;
    }
    visitedTemp[s] = true;

    for(auto u: adj[s]){
        dfs(u);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll tests;
    cin >> tests;

    for(ll t =0; t < tests; t++){
        vector<ll> ans;
        memset(visitedTemp, false, sizeof(visitedTemp));
        memset(visited, false, sizeof(visited));
        for(int i = 0; i < 1001; i++){
            adj[i].clear();
        }

        cin >> nodes >> edges >> X >> Y;

        for(ll i = 0; i < edges; i++){
            ll a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        for(ll i = 1; i <= nodes; i++){
            sort(adj[i].begin(), adj[i].end());
        }

        ll currNode = X;
        visited[currNode] = true;
        ans.push_back(X);
        while(currNode != Y){
            for(auto u: adj[currNode]){
                if(visited[u]){
                    continue;
                }
                memcpy(visitedTemp, visited, sizeof(visited));
                dfs(u);
                visited[u] = true;
                if(visitedTemp[Y] == true){
                    currNode = u;
                    ans.push_back(u);
                    break;
                } else{
                    memcpy(visited, visitedTemp, sizeof(visited));
                }
            }
        }

        for(ll i = 0; i < ans.size(); i++){
            cout << ans[i] << " \n"[i == ans.size() - 1];
        }
    }



}
