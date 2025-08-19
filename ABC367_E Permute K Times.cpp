#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
obs 1: probably some type of pattern/cycle
obs 2: graph theory???? X remains constant, edge between current and X_ith node

idea 1: common graph theory idea. each number in sequence is a node, edge determined by X. Follow each path, determine cycle to reduce time complexity
implementation cancer? can we make it easier?
determine cycle offset and cycle length -> (K- cycle offset)%cycle length

obs 3: functional graph -> a cycle MUST eventaully exist
inefficient, must check for cycle everytime
nodes visited multiple times for answer is there a way to fix this???
can we get the answer for all nodes in a path upon visiting the first time?
O(N^2) time without optimization

optimization: after calculating cycle answers, get answer for all nodes visited in that path -> implementation how?
is there an easier way?
optimization still too slow.
If a large cycle exists with multiple paths incoming, we must traverse the large cycle over and over for each path incoming. Moreover optimization may give
WA in this case
also can TLE with paths incoming a larger path that enters a large cycle ETC

new approach needed
------------------------------------------
editorial
obs: we don't need to update every element each time, tracking the position of an element after K operations and taking the original array at that position gives the answer
proof -> tracking the path of a number after K operations can be reverse to seeing where an element will end up after K operations. (Graph theory)
after 1 operation an element follows X[i], after second it still follows X[i] but the new element at X[i] is at X[X[i]] and so forth
common trick: doubling (similar to binary lifting)
dp[i][k] = if you're at position i where do you end up in 2^k steps
each number can be decomposed into binary.
Then simply get dp[i][k] of each set bit to get final answer

**In general doubling can be used when we want to perform some operation K times, and find end positions**
Similar idea: ABC167 D – Teleporter
*/
ll nums, K;
ll X[200001];
ll arr[200001];

ll dp[200001][60];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    cin >> nums >> K;

   for(ll i = 0; i < nums; i++){
        cin >> X[i];
        X[i]--;
   }

   for(ll i = 0; i < nums; i++){
        cin >> arr[i];
   }

   memset(dp, 0, sizeof(dp));

   for(ll k = 0; k < 60; k++){
        for(ll i = 0; i < nums; i++){
            if(k == 0){
                dp[i][k] = X[i];
            } else{
                dp[i][k] = dp[dp[i][k-1]][k-1];
            }
        }
   }

   for(ll i = 0; i < nums; i++){
        ll curr = 0;
        ll temp = K;
        ll pos = i;

        while(temp > 0){
            if((temp & 1) == 0){

            } else{
                pos = dp[pos][curr];
            }
            curr++;
            temp >>= 1;
        }


        cout << arr[pos] << " \n"[i == nums - 1];
   }
}
