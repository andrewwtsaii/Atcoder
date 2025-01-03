#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int arr[3001];

/*
most ideas ~O(N^3)
N <= 3000
Time complexity can be up to ~ O(N^2logN)
ABSOLUTE max = max occurences of an element
ABSOLUTE min = 1
key idea: O(N/K) time to loop through 1, K, 2K + 1, 3K+1. O(K) time to loop through each possible start value, total is O(N)
time complexity does work loop through N possible K's O(N^2) total time
guesstimate time complexities

*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int N;
    cin >> N;

    for(ll i = 0; i < N; i++){
        cin >> arr[i];
    }

    ll output = 1;
    for(int k = 1; k <= N; k++){
        for(int i = 0; i < N; i++){
            /*if(i + k >= N){
                break;
            }*/
            ll curr = 1;
            for(int j = i; j < N; j += k){
                if(j + k >= N){
                    break;
                } else if(arr[j] == arr[j + k]){
                    curr++;
                } else{
                    break;
                }
            }
            output = max(output, curr);
        }
    }


    cout << output << endl;
}
