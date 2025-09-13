#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
clear trie problem
idea: complementary counting?
build trie. find strings in Y that are children of new addition. if no strings in X children of new addition answer -= children
otherwise ans = prev ans

if inserting string in Y check if it has parent in X if it does ans = prev ans otherwise ans++

obs 1: if inserting word into X, and prefix found along the way in X, answer doesn't change
obs 2: if inserting word into Y, and prefix found along the way in X, answer doesn't change

idea: use complementary counting get number of strings in Y with prefix in X. subtract current total strings in Y.
if inserting word into X: insert word into trie.
    - if prefix found thats in X, answer already done.
    - if node found with children of Y increase answer by children of Y

if inserting word into Y: insert word into trie.
    -if prefix found along way thats in X, add 1 to answer

problem: last node messed up in implementation, cannot process anything with node since loop ends before iterating at node (simply creates the node)
problem: cannot store strings for every node, store numbers (index mapped to strings in vector storing input)
problem: inX and inEnd is not the same as a node being in X and the end. Node could be the end in F and not in the end but in X
*/

ll ans = 0;
ll totalY = 0;
set<int> validY;
vector<string> input;
struct TrieNode{
    TrieNode* children[26];
    set<int> YChildren; //fix: need way to maintain current valid strings
    bool flag = false;

    TrieNode(){
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }

};

void insert(TrieNode* root, int s, bool X){
    TrieNode* curr = root;
    for(int i = 0; i < input[s].size(); i++){
        if(X == true){

        } else{
            curr->YChildren.insert(s);
            if(curr->flag){
                validY.insert(s);
            }
        }
        if(curr->children[input[s][i]-'a'] == nullptr){
            TrieNode* newNode = new TrieNode();
            curr->children[input[s][i]-'a'] = newNode;
        }

        curr = curr->children[input[s][i]-'a'];
    }

    if(X == true){
        curr->flag = true;
        for(auto u: curr->YChildren){
            validY.insert(u);
        }
        curr->YChildren.clear();
    } else{
        curr->YChildren.insert(s);
        if(curr->flag){
            validY.insert(s);
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll queries;
    cin >> queries;

    TrieNode* root = new TrieNode();
    for(ll q = 0; q < queries; q++){
        int query;
        string s;
        cin >> query >> s;
        input.push_back(s);

        if(query == 1){
            insert(root, input.size() - 1, true);
        } else{
            insert(root, input.size() - 1, false);
            totalY++;
        }

        cout << totalY - validY.size() << endl;
    }

}
