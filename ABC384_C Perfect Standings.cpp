#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<ll, string>> v;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;

    v.push_back({a, "A"});
    v.push_back({b, "B"});
    v.push_back({c, "C"});
    v.push_back({d, "D"});
    v.push_back({e, "E"});

    v.push_back({a + b, "AB"});
    v.push_back({a + c, "AC"});
    v.push_back({a + d, "AD"});
    v.push_back({a + e, "AE"});
    v.push_back({b + c, "BC"});
    v.push_back({b + d, "BD"});
    v.push_back({b + e, "BE"});
    v.push_back({c + d, "CD"});
    v.push_back({c + e, "CE"});
    v.push_back({d + e, "DE"});

    v.push_back({a + b + c, "ABC"});
    v.push_back({a + b + d, "ABD"});
    v.push_back({a + b + e, "ABE"});
    v.push_back({a + c + d, "ACD"});
    v.push_back({a + c + e, "ACE"});
    v.push_back({a + d + e, "ADE"});
    v.push_back({b + c + d, "BCD"});
    v.push_back({b + c + e, "BCE"});
    v.push_back({b + d + e, "BDE"});
    v.push_back({c + d + e, "CDE"});

    v.push_back({a + b + c + d, "ABCD"});
    v.push_back({a + b + c + e, "ABCE"});
    v.push_back({a + b + d + e, "ABDE"});
    v.push_back({a + c + d + e, "ACDE"});
    v.push_back({b + c + d + e, "BCDE"});

    v.push_back({a + b + c + d + e, "ABCDE"});

    for(auto &u: v){
        u.first *= -1;
    }

    sort(v.begin(), v.end());

    for(auto u: v){
        cout << u.second << endl;
    }
}
