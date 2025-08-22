#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
brute force solution: loop through all triples adding edges. Keep repeating until none need to be added.
idea 1: brute force improvement -> instead of looping through triples maybe we can loop through edge pairs -> guarantees 2 nodes are connected.

idea 1 continued: loop through nodes i from 1 to n. Check all adjacent nodes x to node i. Create edge between node i and x if not already one. Add this node
to the adjaceny list you are looping through (might need queue or something). O(N^3)? For each node we loop through N other nodes maximum.

still needs optimization

obs 1: we only need to print the number of times we use the operation. Maybe we can do some math with multiplication or something?
Obs 1 potential issue: dynamic edges, edges added affect answer

idea 2: loop through nodes from 1 to n. Find the # of adjacent nodes we aren't connected to for each node adjacent to i. Add to operation number, update adj list. Use map?

potential easy solution: Edges needed to make a complete graph??? (unlikely because it's directed maybe something similar??)
something to do with complete graph. Treat reverse edges as seperate graph? Answer is number of edges away from a complete graph in reverse and normal graph?
(something to do with cycles as well maybe not reverse graph?) (one graph small nodes to big, one big to small?)
do the same for all connected graphs

proof (in order to satisfy constraints we must make a complete graph): conditions for making second edge are that three nodes are part of same graph. it then connects all nodes
try simplified problem of undirected graph? -> check if its just making a complete graph
solution for simplified problem: edges away from making complete graphs from all connected graphs
proof: say we have 3 nodes a, b, and c that are connected. a must connect to all nodes b is connected to. a must connect to all nodes c is connected to. vice versa.
This then continues (changing a, b, and c for the newly connected nodes) until all nodes are connected.

idea 3: loop through nodes from 1 to n. Find all reachable nodes from node i. See how many new edges to make complete graph. <- not really complete graph just current node connects to all others
how to see how many NEW edges to make to complete graph of reachablle nodes from node i. -> having 2 edges between two nodes making it bidirectional makes problem harder

Might not work since adding new edges makes different nodes reachable from later processed nodes.
*Turns out the above isn't True, adding edges to make complete graph from current node won't affect connectivity later, directed edges, only increases connectivity of current node*

hint towards solution -> the operation is connecting a node to all reachable nodes. Initially it's connecting to a reachable node as you keep adding edges
it connects to farther and farther nodes until a complete graph is made.

idea 3 remastered: loop through nodes from 1 to n. Find all reachable nodes from node i. See how many edges needed to connect current node directly to all others nodes.
Adding these edges won't affect later connectivity -> should fit under time constraints.
proof for idea 3: An operation connects a node directly to nodes it can reach in two edges. Performing this operation reduces the distance to a
connected node to 1. It can then be directly connected to connected nodes again. Repeating this gives us our solution of finding how many edges are needed
to connect a current node directly to all connected nodes. This operation does not change the vertices reachable from current node i.

hint towards idea 3 -> the operation connects current node directly to farther connected node. This keeps going until connected to all possible nodes.
-----------------------------------------------------------------------------
Editorial proof: The simulation described above adds a directed edge from x to
y while there is a vertex y whose distance from a vertex
x is two. This operation does not change the vertices reachable from
x. Also, when the operation is no longer possible, there is no vertex whose distance from
x is two, so the edges going out from
x in the final state all go to the vertices reachable from
x in the original state.

*/

vector<ll> adj[2001];
bool visited[2001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes, edges;
    cin >> nodes >> edges;

    for(ll i = 0; i < edges; i++){
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    memset(visited, false, sizeof(visited));

    ll ans = 0;
    for(ll i = 1; i <= nodes; i++){
        memset(visited, false, sizeof(visited));

        ll curr = 1;
        visited[i] = true;
        queue<ll> q;
        q.push(i);

        while(!q.empty()){
            ll s = q.front();
            q.pop();

            for(auto u: adj[s]){
                //cout << s << " " << u << endl;

                if(visited[u]){
                    continue;
                }
                visited[u] = true;
                curr++;
                q.push(u);
            }
        }

        ans += (curr-adj[i].size() - 1);
    }

    cout << ans << endl;
}
