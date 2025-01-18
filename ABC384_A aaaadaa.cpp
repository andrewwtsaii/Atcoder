#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll length;
    char a, b;
    cin >> length >> a >> b;

    string s;
    cin >> s;

    for(ll i = 0; i < length; i++){
        if(s[i] != a){
            s[i] = b;
        }
    }

    cout << s << endl;

}
