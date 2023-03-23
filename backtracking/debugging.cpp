#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <algorithm>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, h;
int arr[31][11];
int ans = INT_MAX;

vector<pair<int, int> > candidate;

bool possible(){
    for(int i = 1; i <= h; i++){
        for(int j = 2; j < n; j++){
            if(arr[i][j] && arr[i][j-1]) return false;
        }
    }

    int test[11];
    for(int i = 1; i <= n; i++){
        test[i] = i;
    }

    for(int i = 1; i <= h; i++){
        for(int j = 1; j < n; j++){
            if(arr[i][j]) swap(test[j], test[j+1]);
        }
    }
    for(int i = 1; i <= n; i++){
        if(test[i] != i) return false;
    }
    return true;
}

void findmin(int cur, int cnt){
    if(cnt >= ans) return;

    if(possible()) {
        ans = min(ans, cnt);
    }

    if(cnt == 3 || cur == (int) candidate.size()) return;

    findmin(cur+1, cnt);

    int a, b;
    tie(a, b) = candidate[cur];
    arr[a][b] = 1;
    findmin(cur+1, cnt+1);
    arr[a][b] = 0;
}

int main() {
    cin >> n >> m >> h;
    while(m--){
        int a, b;
        cin >> a >> b;
        arr[a][b] = 1;
    }
    for(int i = 1; i <= h; i++){
        for(int j = 1; j < n; j++){
            if(!arr[i][j]){
                candidate.push_back({i, j});
            }
        }
    }
    findmin(0, 0);
    if(ans == INT_MAX) {cout << ans << '\n'; return 0;}
    cout << ans << '\n';
    return 0;
}
