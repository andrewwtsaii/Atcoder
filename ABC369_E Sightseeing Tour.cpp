#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
multiple queries -> is there an easy brute force solution?
consideration 1: Will shortest path from every node to node N help?
shortest path from every node to N using 1 specific road?
obs 1: each mandatory road connects two nodes -> if road connects a and b, shortest path from a to N using said road is dist(b, N) + road length
small N -> maybe computing shortest distance from every node to every node is needed. O(N^3) <- floyd warshal algorithm

idea 1: decompose answer into shortest distances from each node connected by a mandatory bridge (5 max). O(N^3 + 5Q)
consider node A and B connected by bridge, C and D connected by bridge both mandatory.
find shortest distance from B to C, distance from A to C using mandatory road is B to C + mandatory length, OR distance from B to C if it crosses
mandatory road.
continue until we extend to A to Z. Then take shortest path from node 1 to A and Z to N and sum all together
connect each node distance using closest distance (max 5 mandatory bridges)

idea 1 doesn't always work -> steps retraced sometimes not always optimal to take greedy shortest
idea 1 fix: try all combination orders of mandatory nodes (bridges) O(2^5 * 5! * 3000)
time complexity too bad

idea 2: visit bridge segments based off of max minimum distance to end first. This way we end on the closest to end (might need other comparisons as well)
idea 2 proof:if a segment is visited with a maximum distance to end visiting another segment first results going farther from the end point and then going back to the end point.
obs 2: only care about the distances from end points of mandatory bridges (i.e if a bridge spans 3 nodes only care about 2 endpoints). If we leave midway it will never be more optimal since we have to cross the bridge still anyways
if ending at midpoint is optimal shortest path from endpoint will go through it anyways

idea 3 (idea 2 simplified): seperate mandatory bridges into components. Visit components with the maximum minimum distance to end node first. Add up segments and distance to first segment + distance from last segment to end
for idea 3: end at closest node to end???

idea 2 + 3 don't work: not always optimal doesn't consider distance to end or distance from start/previous

idea 4: (combine idea 2 and 3) figure out optimal path based on distance to component and distance to end node
instead of max minimum distance, make each node val be minimum distance to end + distance from current node???
connected components of only required bridges makes previous ideas and obs shaky

obs 3: for cyclic connected components we want to end at the closest node to end. (this means starting at them?)

-----------------------------------------------------------------------
obs 4: it is optimal to visit a mandatory node through mandatory bridges, -> don't try and go to farthest node out of all nodes just farthest component since you can visit
farthest node in that component through mandatory bridges which will have to be crossed anyways
visit the closest node that is part of a mandatory connected component with the largest distance (max of all mandatory nodes) to end first then traverse mandatory bridge.
start at node 0
calculate distance to next required node, add mandatory bridge to answer and figure out current node.
finally add distance to end.
Implementation difficult -> connected components
--------------------------------------------------------------------------------------
editorial: Graph theory PLUS DP!
it turns out idea 1 variation is intended solution
rearranging the order of bridges K! ways, and the directions 2^K ways.
consider operations a second (different from time complexity!)
operations: 2^K * K!
time complexity O(Q*2^K*K! + N^3)
operations ~ 10^8

tricky implementation: generating all combinations
HUGE idea: use dp to speed up once order fixed + make implementation easier
dp[a][b] = min ans using a + 1 bridges starting on bth node of bridge a
instead of generating every two possible entries of a bridge use DP to keep track of the best way to enter each bridge as you loop through the # of bridges used
don't need to check EVERY combination, significantly reduces. Once optimal of subcase is found next case only checks cases using the optimal previous subcase
*/

ll nodes, edges, queries;

vector<pair<pair<ll, ll>, ll>> bridges;
ll dist[401][401];
ll dp[5][2];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    cin >> nodes >> edges;

    for(ll i = 0; i < nodes; i++){
        for(ll j = 0; j < nodes; j++){
            if(i == j){
                dist[i][j] = 0;
            } else{
                dist[i][j] = 100000000000000000;
            }
        }
    }

    for(ll i = 0; i < edges; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        bridges.push_back({{a, b}, c});
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    ll queries;
    cin >> queries;

    ll ans = 0;

    for(ll k = 0; k < nodes; k++){
        for(ll i = 0; i < nodes; i++){
            for(ll j = 0; j < nodes; j++){
                if(dist[i][k] != 100000000000000000 && dist[k][j] != 100000000000000000){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for(ll q = 0; q < queries; q++){
        ll required;
        cin >> required;

        ans = 100000000000000000;
        ll curr = 0;
        vector<ll> p; //permutations
        for(ll s = 0; s < required; s++){
            ll x;
            cin >> x;
            x--;
            p.push_back(x);
        }

        do{
            //reset DP every permutation
            for(ll i = 0; i < 5; i++){
                for(ll j = 0; j < 2; j++){
                    dp[i][j] = 100000000000000000;
                }
            }
            dp[0][0] = dist[0][bridges[p[0]].first.first] + bridges[p[0]].second;
            dp[0][1] = dist[0][bridges[p[0]].first.second] + bridges[p[0]].second;

            for(ll i = 1; i < required; i++){
                dp[i][0] = dp[i-1][0] + dist[bridges[p[i-1]].first.second][bridges[p[i]].first.first] + bridges[p[i]].second;
                dp[i][0] = min(dp[i][0], dp[i-1][1] + dist[bridges[p[i-1]].first.first][bridges[p[i]].first.first] + bridges[p[i]].second);

                dp[i][1] = dp[i-1][0] + dist[bridges[p[i-1]].first.second][bridges[p[i]].first.second] + bridges[p[i]].second;
                dp[i][1] = min(dp[i][1], dp[i-1][1] + dist[bridges[p[i-1]].first.first][bridges[p[i]].first.second] + bridges[p[i]].second);
            }

            ans = min(ans, dp[required-1][0] + dist[bridges[p[required-1]].first.second][nodes - 1]);
            ans = min(ans, dp[required-1][1] + dist[bridges[p[required-1]].first.first][nodes-1]);
        } while(next_permutation(p.begin(), p.end()));

        cout << ans << endl;

    }
}
