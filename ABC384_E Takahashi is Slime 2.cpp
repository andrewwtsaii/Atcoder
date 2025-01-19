#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
modified bfs
pq
floating point error with precisions, solved with math (output + x-1)/x instead of float
*/

ll arr[501][501];
bool visited[501][501];
ll output = 0;
double check;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll rows, columns, x;
    cin >> rows >> columns >> x;

    memset(visited, false, sizeof(visited));

    ll startY, startX;
    cin >> startY >> startX;
    startY--;
    startX--;

    for(ll r = 0; r < rows; r++){
        for(ll c = 0; c < columns; c++){
            cin >> arr[r][c];
        }
    }

    output = arr[startY][startX];
    arr[startY][startX] = 0;

    priority_queue<pair<ll, pair<ll, ll>>> q;
    q.push({0, {startY, startX}});

    while(!q.empty()){
        pair<ll, ll> p = q.top().second;
        q.pop();

        //check = (double)(1/(double)x);
        //check *= output;

        //cout << output << " " << check << " " << p.first << " " << p.second << " " << arr[p.first][p.second] << " " << visited[p.first][p.second] << endl;

        if(arr[p.first][p.second] < (output + x-1)/x && !visited[p.first][p.second]){
            output += arr[p.first][p.second];

            if(p.first > 0){
                if(!visited[p.first-1][p.second]){
                    q.push({arr[p.first-1][p.second] * -1, {p.first-1, p.second}});
                }
            }

            if(p.first < rows - 1){
                if(!visited[p.first+1][p.second]){
                    q.push({arr[p.first+1][p.second] * -1, {p.first+1, p.second}});
                }
            }

            if(p.second > 0){
                if(!visited[p.first][p.second-1]){
                    q.push({arr[p.first][p.second-1] * -1, {p.first, p.second-1}});
                }
            }

            if(p.second < columns - 1){
                if(!visited[p.first][p.second+1]){
                    q.push({arr[p.first][p.second+1] * -1, {p.first, p.second+1}});
                }
            }

        } else if(!visited[startY][startX]){
            break;
        }


        visited[p.first][p.second] = true;
    }

    cout << output << endl;
}
