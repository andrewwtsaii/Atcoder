#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
obs 1: if we start at the start and end node (using opposite directionon arrows for end node), we must use the same letters each "turn" eventually meeting to form a palindromic path
obs 2: the answer to every node to itself is 0

idea 1: somehow use obs 1 to run a two point souurce graph traversal for the answer
time complexity O(N^2 * N^2)?? N^2 for every query in matrix, N^2 for traversal? N^2 edges
optimization: DP? dp[a][b] = answer between node a and b, if another problem reduces to this memoization may help.
optimization 2: check if node a and b are reachable at all first.

problem with idea 1: Sometimes stuck in indefinite loop with no progress to join 2 nodes together made. How to prevent this and ensure
shortest path?

idea 2: for every node, start with the answer to direct nodes, and then farther and farther nodes and use DP + graph theory somehow
dp[a][b] = ans from node a to node b. <- also store letter used/string?

idea 2 might not work, string might have to change entirely subcases not valid to use to solve full case
for dp[a][b+1] (b is one edge farther), check all letters used for dp[a][b] and dp[b][b+1] if match, ans is dp[a][b] + 1, otherwise no answer?
idea 2 -> doesn't work/needs change. Example if 1->2 is S, and 2->3 is t, might seem impossible but if edge 3->3 s, it is possible
not always simple path affects transition as well. Palindromes change between cases and subcases.

-------------------------------------------------------------------------------------------------------------------------------------------
hint from editorial preview: think of looping through 26 letters somehow for answer?
obs 3 (in editorial): a palindrome is still a palindrome if removing the first & last character (already knew) -> how to apply to solution
how to make idea 1 work with two point source
problem: how to always make next step optimal in getting closer to end node and making palindrome
obs 4 (in editorial):a palindrome can be formed by concatenating a letter to the end and beginning of a palindrome

editorial sneak peek: form a new graph with N^2 vertices where each vertex is the pair (i, j)
for each original node we can go to any node in the graph with pair(n, j)

0 length palindromes are at (i, i), one length palindromes are at (i, j) if Ci,j != 1
palindrome will length + 2 when (
for answer take shortest path of modified graph

full solution: consider a new graph with verticies (i, j). Each edge represents the length of a palindrome. We want to get to vertex (a, b) where
a and b are our query values.
start at an imaginary start node with edge 0 to vertices (i, i), 1 to vertices (i, j) if an edge exists between i and j
create an edge between vertices (i, j) and (k, l) of length 2 (represents adding letter to front and back of palindrome) if
C[k][i] = C[j][l] and isn't non existent edge. This edge represents a palindrome from k to l. (First we need to go to node (i, j) representing
we got a palindrome, then (k, l) representing we extended the palindrome by length 2). Adding the other way would mean the palindrome length
increases as we get to nodes that are optimally closer.

run BFS to find shortest palindrome. Note: we add edges in order of increasing length in order to account for different lengths.
all 0 length first, then all 1 length. Process answers, then all 2 lengths since they are all same answer can be accurate using BFS.
Answer for each query is shortest path to (a, b) where a and b are our query nodes.

note: ll not needed for queue resulted in MLE
*/

ll ans[101][101];
char userIn[101][101];
bool visited[101][101];
queue<pair<int, int>> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes;
    cin >> nodes;

    for(ll i = 0; i < nodes; i++){
        for(ll j = 0; j < nodes; j++){
            ans[i][j] = 1000000000000000;
        }
    }
    memset(visited, false, sizeof(visited));

    for(ll i = 0; i < nodes; i++){
        for(ll j = 0; j < nodes; j++){
            cin >> userIn[i][j];
        }
    }

    for(ll i = 0; i < nodes; i++){
        for(ll j = 0; j < nodes; j++){
            if(i == j){
                ans[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    for(ll i = 0; i < nodes; i++){
        for(ll j = 0; j < nodes; j++){
            if(userIn[i][j] != '-'){
                ans[i][j] = min(ans[i][j], (ll)1);
                q.push({i, j});
            }
        }
    }

    while(!q.empty()){
        if(visited[q.front().first][q.front().second]){
            q.pop();
            continue;
        }
        visited[q.front().first][q.front().second] = true;
        for(int k = 0; k < nodes; k++){
            for(int x = 0; x < nodes; x++){
                if(userIn[k][q.front().first] != '-' && userIn[k][q.front().first] == userIn[q.front().second][x]){
                    q.push({k, x});
                    ans[k][x] = min(ans[k][x], ans[q.front().first][q.front().second] + 2);
                }
            }
        }
        q.pop();
    }

    for(ll i = 0; i < nodes; i++){
        for(ll j = 0; j < nodes; j++){
            if(ans[i][j] == 1000000000000000){
                ans[i][j] = -1;
            }
            cout << ans[i][j] << " \n"[j == nodes - 1];
        }
    }
}
