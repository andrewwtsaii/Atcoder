#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int A, B, C;
    cin >> A >> B >> C;

    if(A == B && A == C){
        cout << "Yes" << endl;
    } else if(A == B + C || B == A + C || C == A + B){
        cout << "Yes" << endl;
    } else{
        cout << "No" << endl;
    }


}
