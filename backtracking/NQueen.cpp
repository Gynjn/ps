#include <iostream>
#include <algorithm>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n;
int board[14][14];
int ans = 0;

bool check(int x, int y){
    for(int d = 0; d < 3; d++){
        int dx = -1, dy = d-1;
        for(int i=1; ; i++){
            int nx = x + i*dx;
            int ny = y + i*dy;
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) break;
            if(board[nx][ny]) return 0;
        }
    }
    return 1;
}

void dfs(int x){
    if(x == n) {
        ans++;
        return;
    }
    for(int y = 0; y < n; y++){
        if(!check(x, y)) continue;
        board[x][y] = 1;
        dfs(x + 1);
        board[x][y] = 0;
    }
}

int main(){
    fastio;
    cin >> n;
    dfs(0);
    cout << ans;
}
