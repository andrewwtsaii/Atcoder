#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int freq[14];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int A, B, C, D;
    memset(freq, 0, sizeof(freq));
    cin >> A >> B >> C >> D;
    freq[A]++;
    freq[B]++;
    freq[C]++;
    freq[D]++;

    bool one = false, two1 = false, two2 = false, three = false;
    for(ll i = 1; i <= 13; i++){
        if(freq[i] == 1){
            one = true;
        }
        if(freq[i] == 2){
            if(two1){
                two2 = true;
            }
            two1 = true;
        }
        if(freq[i] == 3){
            three = true;
        }
    }

    if(three && one || two1 && two2){
        cout << "Yes" << endl;
    } else{
        cout << "No" << endl;
    }


}
