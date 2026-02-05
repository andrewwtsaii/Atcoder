#include <bits/stdc++.h>

using namespace std;

/*
area of clouds can overlap
2D psa?
dynamic so probably not PSA

only need to see if cell is covered by 0, 1 or more clouds

idea: 2D difference array to set all cells as covered by certain cloud
twist: make 2 2D difference arrays one to keep track of how many clouds cover a cell,
second to keep track of which cloud covers a cell (in single case otherwise this is ignored anyways)

editorial used, 2D difference array

easy way to remember
Add to top left and bottom right, subtract from bottom left top right.
Extend bottom left, bottom right, and top right corners by 1.
make all rows a[r][c] = a[r-1][c]
then make all columns
a[r][c] = a[r][c-1] or do columns and then rows, order doesn't matter

how summing works: we store cumlative row answers or columns,
then when switching to columns or rows to make it 2D, we add everything above which also includes everything above and to the left
plus everything to the left in the currennt row or everything above in the current column.

If needed initialize with differences,
for 2D, subtract left and above and add diagonal up and left (checking no out of range)
similar to PSA,
subtract left and top right, but this double counts the matrix represented by the diagonal cell.
*/

typedef long long ll;

ll emptyCells = 0;
int cloudNums[2000][2000];
int cloudVals[2000][2000];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    int N;
    cin >> N;

    ll ans[N+1];

    memset(cloudNums, false, sizeof(cloudNums));
    memset(cloudVals, false, sizeof(cloudVals));
    memset(ans, 0, sizeof(ans));
    for(int i = 1; i <= N; i++){
        int Uc, Dc, Lc, Rc;
        cin >> Uc >> Dc >> Lc >> Rc;
        Uc--;
        Dc--;
        Lc--;
        Rc--;

        cloudNums[Uc][Lc]++;
        cloudVals[Uc][Lc] += i;

        if(Dc + 1 < 2000){
            cloudNums[Dc+1][Lc]--;
            cloudVals[Dc+1][Lc] -= i;
        }

        if(Dc + 1 < 2000 && Rc + 1 < 2000){
            cloudNums[Dc+1][Rc+1]++;
            cloudVals[Dc+1][Rc+1] += i;
        }

        if(Rc + 1 < 2000){
            cloudNums[Uc][Rc+1]--;
            cloudVals[Uc][Rc+1] -= i;
        }

    }

    for(int r = 0; r < 2000; r++){
        for(int c = 1; c < 2000; c++){
            cloudNums[r][c] += cloudNums[r][c-1];
            cloudVals[r][c] += cloudVals[r][c-1];
        }
    }

    for(int r = 1; r < 2000; r++){
        for(int c = 0; c < 2000; c++){
            cloudNums[r][c] += cloudNums[r-1][c];
            cloudVals[r][c] += cloudVals[r-1][c];
        }
    }

    for(int r = 0; r < 2000; r++){
        for(int c = 0; c < 2000; c++){
            if(cloudNums[r][c] == 0){
                emptyCells++;
            } else if(cloudNums[r][c] == 1){
                ans[cloudVals[r][c]]++;
            }
        }
    }

    for(int i = 1; i <= N; i++){
        cout << emptyCells + ans[i] << endl;
    }



}
