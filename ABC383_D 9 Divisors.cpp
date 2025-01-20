#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
write everything out
divisors = product of the (exponents of prime factors + 1)
8 + 1 = 9
(2 + 1)(2 + 1) = 9
implementation: use vector of list of primes and for loop to add them using N as max!
*/

vector<ll> primes;

bool isPrime(ll N){
    for(ll i = 2; i * i <= N; i++){
        if(N%i == 0 && i != N){
            return false;
        }
    }

    return true;
}

ll output = 0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll N;
    cin >> N;

    ll curr = 2;

    for(ll i = 2; i <= 2100000; i++){
        if(isPrime(i)){
            primes.push_back(i);
        }
    }

    for(auto i: primes){
        if(i >= 2100000){
            break;
        }
        if(i * i * i * i * i * i * i * i > N){
            break;
        } else{
            output++;
        }
    }

    ll p2 = primes[primes.size() - 1];

    for(ll i = 0; i < primes.size(); i++){
        ll p1 = primes[i];

        if(p1 * p1 * p1 * p1 > N){
            break;
        }

        for(ll j = i + 1; j < primes.size(); j++){
            ll p2 = primes[j];
            if(p1 * p1 * p2 * p2 <= N){
                output++;
            } else{
                break;
            }
        }
    }

    cout << output << endl;

}
