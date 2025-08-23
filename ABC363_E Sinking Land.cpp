#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
brute force solution O(N^2 * Y)
obs 1: nothing sinks (answer remains same) at beginning until island on border sinks.
obs 2: solvable in O(n) time.
can we use a 2d difference array to subtract? O(1) time but how to query in O(1)?
probably not difference array -> too difficult to query
obs 3: query for numbers < sinking ships adjacent? we can keep track of this from input
obs 4: can this turn into graph theory? Once a ship sinks all connected nodes sink. Directed edges between nodes that are bigger to nodes that are smaller
another hint to obs 4 is the bounds on nodes <= 1000^2. Edges maxed at 4

how to use obs 4 to solve entire problem (after something sinks for the first time?)
how to quickly check all nodes <= i (current year) that are adjacent to sea or sunk node. Maybe use set, once something sinks add all adjacent nodes (not just directed edge nodes) to set?
O(N^2) time works under constraints

idea 1: Have a set of nodes. Originally add all nodes adjacent to sea. Loop through years i from 1 to Y. Each year check if the first element in set is <= Y.
If it is keep adding nodes in set to a queue until we reach a node > Y. BFS in queue deleting all nodes that are <= i. For each node sunk, add ALL adjacent nodes that are <= Y
O(max(N^2, Y)) time.

**obs 4 not completely accurate, turns out this is a more straightforward graph theory problem. We can just check if nodes should be sunk or not and add to visited

solution (idea 1 formalized): Represent 2D grid as graph. Have a set originally of border nodes. For each year check if a node is <= current year. If it is
loop through set adding each node into queue until > y. Then run bfs on these nodes adding to the queue if the adjacent node is <= current year. Otherwise add them
to the set. Continue for rest of years.
*/

int input[1001][1001];
bool sunk[1001][1001];

int output = 0;
set<pair<int, pair<int, int>>> s;
queue<pair<int, int>> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll rows, columns, Y;
    cin >> rows >> columns >> Y;

    for(ll r = 0; r < rows; r++){
        for(ll c = 0; c < columns; c++){
            cin >> input[r][c];
            if(r == 0 || c == 0 || r == rows - 1 || c == columns - 1){
                s.insert({input[r][c], {r, c}});
            }
        }
    }

    output = rows * columns;

    for(ll i = 1; i <= Y; i++){
        auto it = s.begin();
        while(it != s.end()){
            if((*it).first <= i){
                q.push({(*it).second.first, (*it).second.second});
                sunk[(*it).second.first][(*it).second.second] = true;
            } else{
                break;
            }
            it++;
        }

        s.erase(s.begin(), it);

       /* for(auto u: s){
            cout << "val: " << u.first << " " << "(" << u.second.first << ", " << u.second.second << " ), ";
        }
        cout << endl;*/

        while(!q.empty()){
            pair<int, int> p = q.front();
            q.pop();

            output--;

            //check 4 directions
            if(p.first > 0){
                if(input[p.first-1][p.second] <= i){
                    if(!sunk[p.first-1][p.second]){
                        sunk[p.first-1][p.second] = true;
                        q.push({p.first-1, p.second});
                    }
                } else{
                    s.insert({input[p.first-1][p.second], {p.first-1, p.second}});
                }
            }

            if(p.first < rows - 1){
                if(input[p.first+1][p.second] <= i){
                    if(!sunk[p.first+1][p.second]){
                        sunk[p.first+1][p.second] = true;
                        q.push({p.first+1, p.second});
                    }
                } else{
                    s.insert({input[p.first+1][p.second], {p.first+1, p.second}});
                }
            }

            if(p.second > 0){
                if(input[p.first][p.second-1] <= i){
                    if(!sunk[p.first][p.second-1]){
                        sunk[p.first][p.second-1] = true;
                        q.push({p.first, p.second-1});
                    }
                } else{
                    s.insert({input[p.first][p.second-1], {p.first, p.second-1}});
                }
            }

            if(p.second < columns - 1){
                if(input[p.first][p.second+1] <= i){
                    if(!sunk[p.first][p.second+1]){
                        sunk[p.first][p.second+1] = true;
                        q.push({p.first, p.second+1});
                    }
                } else{
                    s.insert({input[p.first][p.second+1], {p.first, p.second+1}});
                }
            }
        }

        cout << output << endl;
    }

}
