#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
smart idea dp is infinity when difference in size strays by k
*/
ll dp[500001][41];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int K;
    cin >> K;

    string start, finish;
    cin >> start >> finish;


    int dist = abs((int)start.size() - (int)finish.size());
    if(dist > K){
        cout << "No" << endl;
    } else{
        memset(dp, 0x64, sizeof(dp));

        dp[0][K] = 0;
        for(ll a = 0; a <= start.size(); a++){
            for(ll b = 0; b <= (2 * K); b++){
                ll bb = a + (b - K);

                if(bb < 0 || bb > finish.size()){
                    continue;
                }

                if(a > 0 && b < (2 * K)){
                    dp[a][b] = min(dp[a][b], dp[a-1][b+1] + 1); //if we remove then b must change too to maintain size since b shifts with a
                }
                if(b > 0 && bb > 0){
                    dp[a][b] = min(dp[a][b], dp[a][b-1] + 1);
                }

                if(a > 0 && bb > 0){
                    int cost = 1;
                    if(start[a-1] == finish[bb-1]){
                        cost = 0;
                    }
                    dp[a][b] = min(dp[a][b], dp[a-1][b] + cost); //no need for b-1 auto shifts with a
                }
            }
        }


        ll bb = finish.size() - start.size();
        bb += K;

        if(dp[start.size()][bb] > K){
            cout << "No" << endl;
        } else{
            cout << "Yes" << endl;
        }
    }





}
