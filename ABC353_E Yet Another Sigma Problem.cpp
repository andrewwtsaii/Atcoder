#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
clear trie problem

idea 1: when inserting word walk down trie and add up all strings that have prefix of certain node
problem idea 1: how to prevent overcounting (ie word that starts with a and then ab, inserting word abc counts 2 for same word)
problem potential solution: maybe see how answer decreases as walking to trie to see how many prefixes split off?

reformed idea 1: insert a word and store number of words with walked path as prefix. For each node keep track of previous number of words.
ans += ((prev - curr) * (length of curr path - 1))
a, ab, abc, ac

obs 1: when inserting a string into trie we need to check sum of f(x, y) between current node (y) and all previously inserted strings (x)

full solve! -> quick interview time

*/
vector<string> input;

struct TrieNode{

    TrieNode* children[26];
    int preSum = 0;
    bool isEnd;
    TrieNode(){
        isEnd = false;
        preSum = 0;
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }
};

ll ans = 0;

void insert(TrieNode* root, string s){
    TrieNode* curr = root;
    ll prev = 0;
    for(int i = 0; i < s.size(); i++){
        if(i <= 1){
            prev = curr->preSum;
        } else{
            ll diff = prev - curr->preSum;
            ans += (diff * (i-1));
            prev = curr->preSum;
        }

        if(i > 0){
            curr->preSum++;
        }

        if(curr->children[s[i]-'a'] == nullptr){
            TrieNode* newNode = new TrieNode();
            curr->children[s[i]-'a'] = newNode;
        }
        curr = curr->children[s[i]-'a'];
    }

    ll diff = prev - curr->preSum;
    ans += (diff * (s.size() - 1));
    ans += (curr->preSum * s.size());
    curr->preSum++;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll strings;
    cin >> strings;

    TrieNode* root = new TrieNode();
    for(ll i = 0; i < strings; i++){
        string s;
        cin >> s;
        input.push_back(s);
        insert(root, s);
        //cout << ans << endl;
    }

    cout << ans << endl;

}
