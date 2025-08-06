#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
//considering leftmost grape helps us elminate the possibility of other grapes to the left as well as apples and oranges to the right!
//mathematical combo trick: counting ways of arranging fruits to the left of leftmost grape is # of ways to insert oranges (stars and bars, each insertion point can hold multiple oranges)
//Main helpful idea: Considering left most grape with i bananas to the left and iterating over i. Then counting possibilities to right and left for each i and taking the product and summing over all i
//mathematical important trick: With only two indistinguishable items its the total choose amount of one item (A+B)Choose B or (A+B) choose A. Ex AAABB is 5 Choose 2 or 5 Choose 3
//to efficiently implement chose precomputation is needed (inverse factorial and factorial) - fermat little theorem needed
// any + - and * operations can be modded by M, and won't affect the final answer if the final answer is mod M
//precompute explanation: factorial taken % M, invFact = fact[i] modM = facts[i]^(M-2)modM for prime M according to fermat little theorem
//factorial inverse: basically the equivalent of division (^-1) of a factorial
ll facts[4000001];
ll invFacts[4000001];
ll M = 998244353;

ll power(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}
void precompute(){
    facts[0] = invFacts[0] = 1;
    for(int i = 1; i < 4000001; i++){
        facts[i] = facts[i-1] * i % M;
        invFacts[i] = power(facts[i], M - 2); //invFacts[i] stores invFacts[i] mod M
    }
}

ll choose(ll n, ll k){
    if(k < 0|| k > n)return 0;
    return (facts[n] * invFacts[k] % M) * invFacts[n-k] % M;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    precompute();

    ll apples, oranges, bananas, grapes;

    cin >> apples >> oranges >> bananas >> grapes;

    ll ans = 0;
    ll curr = 0;
    ll lft = 0, rht = 0;
    for(int i = 0; i <= bananas; i++){
        curr = 0, lft = 0, rht = 0;
        lft = choose(apples + oranges + i, oranges); //oranges is bars, apples + oranges + i is stars
        rht = choose(grapes - 1 + bananas - i, grapes - 1); //only 2 distinguishable items
        curr = (lft * rht)%M;
        ans += (curr);
    }


    cout << ans % M << endl;
}
