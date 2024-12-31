#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    string s;
    cin >> s;

    ll output = 0;

    for(ll i = 0; i < s.size(); i++){
        if(s[i] == '0'){
            if(i == s.size() - 1){
                output++;
            } else{
                if(s[i + 1] == '0'){
                    output++;
                    i++;
                } else{
                    output++;
                }
            }
        } else{
            output++;
        }
    }

    cout << output << endl;
}
