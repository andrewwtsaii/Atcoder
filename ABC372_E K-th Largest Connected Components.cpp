#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
clear disjoint set problem
idea 1: use extra sorted set to keep track of current k-th largest (works similar to rank)
note k <= 10 should satisfy time

probably TLE's with no optimizations, need to clear sets of non parents
to clear sets we need to make sure we don't combine two people already in same ds (goes for any disjoint set for efficiency)
fixed problem
*/

ll r[200001];
ll ds[200001];
set<ll> s[200001];
ll findSet(ll d){
    if(d != ds[d]){
        d = findSet(ds[d]);
    }
    return ds[d];
}

void combine(ll x, ll y){
    x = findSet(x);
    y = findSet(y);

    if(x == y){
        return;
    }

    if(r[x] < r[y]){
        for(auto u: s[findSet(x)]){
            //cout << x << " " << y << " " << u << " A " << endl;
            s[findSet(y)].insert(u);//can optimize space keep max size 10-20
        }
        s[findSet(x)].clear();
        //cannot clear unless sure it wont affect answer ex. if nodes are already in same ds
        ds[x] = ds[y];
    } else{
        for(auto u: s[findSet(y)]){
            s[findSet(x)].insert(u);
            //cout << x << " " << y << " " << u << " B " << endl;
        }
        s[findSet(y)].clear();
        ds[y] = ds[x];
        if(r[x] == r[y]){
            r[x]++;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll nodes, queries;
    cin >> nodes >> queries;

    for(int i = 0; i <= nodes; i++){
        r[i] = 0;
        ds[i] = i;
        s[i].insert(i * -1);
    }

    for(ll i = 0; i < queries; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        if(a == 1){
            combine(b, c);
        } else{
            int i = 0;
            for(auto u: s[findSet(b)]){
                //cout << u << endl;
                i++;
                if(i == c){
                    cout << (u * (-1)) << endl;
                    break;
                }
            }
            if(i != c){
                cout << -1 << endl;
            }
        }
    }
}
