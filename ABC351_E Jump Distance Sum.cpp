#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
consider simplified problem of just rabbits in a line. For each distance between a[i] and a[i+1] looping from 1 to n, multiply by n - i

obs 1: dist from b to c can be calculated using dist from a to c and dist from a to b
obs 2: if x + y is odd, it is impossible to each a point where x + y = even
proof -> we must move 1 step in BOTH x and y, this keeps parity the same
obs 3: renumbering points doesn't change answer

idea 1: loop from points 1 to n after sorting from left to right (down to up). Calculate distance from a[i] to a[i+1] and add to dist[i]. Add this distance to an array dist[i] to all points
with a y greater than equal to a[i+1] and subtract to all points with a y less than a[i+1]. Final answer is the sum of every dist[i] <- needs to be looked over and improved, not sure if works
after testing cases idea 1 probably doesn't work or needs to be modified similar idea can work. right time complexity

consider when adding to every array element a[i] to a[i+1] might have to multiply by points visited same parity.
dist[a -> c} not easily determinable from dist[a->b] and dist[b->c]. try thinking of new appraoch now?

obs 4: storing ans[i] to be the distance from all points i-1 to i, can help us solve in O(n) time, if we fill array in O(N) time and calculate sum of array at end
instead of looping through all pairs, we can still consider looping from left to right and updating array in O(1) time somehow maybe? -> hinted at through time complextiy?

obs 5: distance is the max(abs(x1-x2), abs(y1-y2))
proof x1-D = x2   y1-D = y2   D = y1-y2   D = x1-x2 whichever bigger

can we sort points somehow to make obs4 and obs5 help us with a solution?
---------------------------------------------------------------------------------------------------
Solution: we want to reduce problem so sum of all manhattan distances between points O(NlogN).
The idea for this reduced problem is to treat the x and y coordinates seperately and use a running sum. res = res + (xi)*i - (x0 + x1 + ... xi-1).
We cannot treat x and y seperately for original problem because we need to sort and then we can't take maximum easily.
Similar idea to original problem, with using sorting and calculated distances between adjacent points for all points and using math to solve in O(NlogN). Need to seperate into
x and y though.
How to convert this to a manhattan distance problem?

transform (x, y) -> (x+y, x-y).
proof
case 1: x1 + y1 > x2 + y2 and x1-y1 > x2-y2
manhattan distance: x1 + y1 - x2 - y2 + x1 - y1 - x2 - y2 = 2(x1 - x2)
proof |x1-x2| > |y1-y2| -> case1 condition 1: (x1-x2) + (y1-y2) > 0 case1 condition 2: (x1-x2)-(y1-y2) > 0
(x1-x2) > -(y1-y2) and (x1-x2) > (y1-y2)   -> (x1-x2) > |y1-y2| --> x1-x2 > 0

case 2: x1 + y1 > x2 + y2 and x1 - y1 < x2 - y2
manhattan distance: x1 + y1 - x2 - y2 + x2 - y2 - x1 + y1 = 2(y1 - y2)

case 3: x1 + y1 < x2 + y2 and x1 - y1 > x2 - y2
manhattan distance: x2 + y2 - x1 - y1 + x1 - y1 - x2 + y2 = 2(y2 - y1)

case 4: x1 + y1 < x2 + y2 and x1 - y1 < x2 - y2
manhattan distance: x2 + y2 - x1 - y1 + x2 - y2 - x1 + y1 = 2(x2 - x1)

Therefore, 2 * regular answer = manhattan distance

Easier proof:
note that whichever is larger in x1 -x2 or y1 -y2 will dominate (same sign) in the manhattan distance giving us 2 x (our answer) always! formally shown in case 1
let a = x1-x2, let b = y1 -y2. After transforming: Manhattan distance = abs(x1+y1-x2-y2) + abs(x1-y1-x2+y2) = abs(x1-x2+y1-y2) + abs(x1-x2+y2-y1) = abs(a+b) + abs(b-a) = 2max(a, b)  <- Left side if b > a multiply by negative one since absolute value

Hint at solution: only diagonal moves, rotating plane 45 degrees may help.
All points reachable with distance <= 1 for manhattan forms square, for our earlier formula obs 5: Chebyshev distance it forms a diamond. hints at rotation
rotating point (x,y) 45 degrees and scaling by sqrt(2) gives (x+y, x-y)
rotating point (x,y) 45 degrees without scaling is ((x+y)/sqrt(2), (x-y)/sqrt(2))

****Note that normally this transformation gives (x+y, y-x), however both transformations work.****
proof -> negative doesn't matter in distances. Look at easier proof swapping b to y2-y1 doesn't change answer.

**make sure to treat parities seperately when transforming since different x + y parities aren't reachable in the original question

identity in problem: Chebyshev distance * 2 = manhattan distance of (x+y, x-y)
*/

ll ans = 0;

vector<ll> xs1;
vector<ll> ys1;
vector<ll> xs2;
vector<ll> ys2;

void computeAns(vector<ll> v){
    ll sum = 0;
    ll curr = 0;

    for(ll i = 1; i < v.size(); i++){
        ll dist = v[i] - v[i-1];
        curr += ((dist * i) + sum);
        sum += (dist * i);
    }

    ans += curr;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie();

    ll points;
    cin >> points;

    for(ll i = 0; i < points; i++){
        ll x, y;
        cin >> x >> y;
        if(((x+y) % 2) == 0){
            xs1.push_back(x + y);
            ys1.push_back(x-y);
        } else{
            xs2.push_back(x + y);
            ys2.push_back(x - y);
        }
    }

    sort(xs1.begin(), xs1.end());
    sort(ys1.begin(), ys1.end());
    sort(xs2.begin(), xs2.end());
    sort(ys2.begin(), ys2.end());

    computeAns(xs1);
    computeAns(ys1);
    computeAns(xs2);
    computeAns(ys2);

    ans /= 2;
    cout << ans << endl;
}
