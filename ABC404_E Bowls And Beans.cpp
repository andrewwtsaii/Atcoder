#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
graph theory? each bowl connects to max (N-1 bowls), each node has N-1 edges?
idea 1: N only up to 2000. Brute forceing adjacency list and using graph theory could work. (Shortest path to node 0)

*make sure to read problem carefully see what problem is asking for, see how idea can help answer problem

problem idea 1: doesn't account for situation where we move beans into a bowl with beans already in it and hten move them all for optimal solution
only accounts for independent solutions.

idea: dont reset visited or distances, if a node has already been visited before (check that a bean has made it from there to 0) so just continue?
how to increment answer?

consider reversing edges? we can prioritize nodes closest to bowl 0 easier

idea 2: create two adjaceny lists, one with reverse edges one normal.
    - calculate distance from bowl 0 to all bowls
    - start at the closest bowl and add distance to answer while traversing graph
    - continue with rest of the bowls when a node that already has been visited and used to go to node 0 is reached stop.

idea 2 might have to be optimized
modified idea 2 might work

note: idea 2 is always optimal since the closest visited node or node 0 will be in the queue first

obs and note: cycles are impossible we can only move to nodes with a smaller index
problem idea 2: how to check if node reaches node 0 optimally? ex. C = 1 1 2. Final bowl goes to C - 1 and C - 2. Then when
C - 1 in queue it sees C - 2 is visited how to know if it reaches node 0 optimally?

idae to fix: have second bool array called completed, set all nodes in visited to completed only after node has finished. We only
want to stop if we reach an already visited node (by a previous start node)

maybe compute difference between every node? (not enough time)
helpful: MAKE SURE TO PROVE ALL OBS BEFORE ASSUMING THEM

problem: just because node was visited does not mean it was taken (shouldn't be completed if it wasnt on optimal path for ndoe)

*WA -> AC fix --> sorted by i and then distances[i] instead of distances[i] and then i.

distances[i] might not even be necesssary. WHy?
sorting by distances[i] is never BETTER than i. If later bowl can move alot, processing i marks all the nodes that
it would have to take regardless.

sorting by i is better than distances[i] proof: beans can only move left. this fixes our problem as it doesn't matter if we mark all
visited nodes as completed, since the bean bowl is always the most to the right, we can just visit the bean bowl to the right and then
mark everything as completed

distances[i] can thus be removed
can be simplified further to just look for closest bean bowl starting, since if we go earlier we can also just go to a higher i bowl.
---------------------------------------------------------------------------
Intended solution:
Loop through beans from left to right
initially segment from moving beans can be in the range [x, x]
after k + 1 moves segment[l, r] (from k moves) becomes min(i from l to r (i-Ci), r)
repeat this until bowl 0 is reached.

can be optimized with seg tree
-------------------------------------------------------------
*/

vector<ll> adj[2001];

bool visited[2001];
bool completed[2001];

ll distances[2001];

vector<ll> C;
vector<ll> beans;
set<int> filledBowls;

ll ans = 0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N;
    cin >> N;

    memset(distances, 0, sizeof(distances));
    memset(completed, false, sizeof(completed));
    memset(visited, false, sizeof(visited));

    C.push_back(0);
    beans.push_back(0);
    for(ll i = 0; i < N - 1; i++){
        ll num;
        cin >> num;
        C.push_back(num);
    }

    for(ll i = 0; i < N - 1; i++){
        ll num;
        cin >> num;
        beans.push_back(num);
    }

    for(ll i = 1; i < N; i++){
        for(ll j = i - 1; j >= max((ll)0, i - C[i]); j--){
            adj[i].push_back(j);
        }
    }

    queue<int> q;

    for(ll i = 1; i < N; i++){
        if(beans[i] > 0){
            filledBowls.insert(i);
        }
    }

    for(auto start: filledBowls){
        queue<pair<int, int>> journey;
        journey.push({start, 0});
        visited[start] = true;

        while(!journey.empty()){
            pair<int, int> s = journey.front();
            journey.pop();
            if(completed[s.first]){
                break;
            }

            bool flag = false;
            for(auto u: adj[s.first]){
                if(completed[u]){
                    ans += (s.second + 1);
                    flag = true;
                    break;
                }
                if(visited[u]){
                    continue;
                }
                if(u == 0){
                    ans += (s.second + 1);
                    flag = true;
                    visited[u] = true;
                    break;
                }
                visited[u] = true;
                journey.push({u, s.second + 1});
            }
            if(flag){
                break;
            }
        }

        for(ll i = 0; i < N; i++){
            if(visited[i]){
                completed[i] = true;
            }
        }
    }

    cout << ans << endl;

}
