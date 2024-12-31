#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int K;
    cin >> K;

    string s, t;
    cin >> s >> t;

    ll x = s.size();
    ll y = t.size();
    if(abs(x-y) > 1){
        cout << "No" << endl;
    } else{
        if(s.size() == t.size()){
            bool possible = true;
            bool first = false;
            for(ll i = 0; i < s.size(); i++){
                if(s[i] != t[i]){
                    if(first){
                        possible = false;
                        break;
                    } else{
                        first = true;
                    }
                }
            }
            if(possible){
                cout << "Yes" << endl;
            } else{
                cout << "No" << endl;
            }
        } else{
            //check insertion
            //ending
            bool append = true;
            bool deletion = true;
            bool first = false;
            for(ll i = 0; i < min(s.size(), t.size()); i++){
                if(first){
                    if(s.size() < t.size()){
                        if(s[i] != t[i + 1]){
                            deletion = false;
                            break;
                        }
                    } else{
                        if(t[i] != s[i + 1]){
                            deletion = false;
                            break;
                        }
                    }
                } else{
                    if(s[i] != t[i]){
                        first = true;
                    }
                }
            }
            first = false;

            for(ll i = 0; i < min(s.size(), t.size()); i++){
                if(s[i] == t[i]){

                } else{
                    append = false;
                }
            }
            if(!append){
                append = true;
                for(ll i = 1; i < max(s.size(), t.size()); i++){
                    if(s.size() < t.size()){
                        if(s[i-1] != t[i]){
                            append = false;
                            break;
                        }
                    } else{
                        if(t[i-1] != s[i]){
                            append = false;
                            break;
                        }
                    }
                }
            }
            if(deletion || append){
                cout << "Yes" << endl;
            } else{
                cout << "No" << endl;
            }
        }
    }

}
