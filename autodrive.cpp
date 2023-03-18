#include <iostream>
#include <cstring>
#include <algorithm>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int x, y, d;
int board[50][50];
int visited[50][50];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int flag = 0;

bool cango(int x, int y){
    return (!board[x][y] && !visited[x][y]);
}

void step(){
    visited[x][y] = 1;
    for(int i = 0; i < 4; i++){
        int nd = (d+3)%4;
        int nx = x + dx[nd];
        int ny = y + dy[nd];    
        if(cango(nx, ny)){
            x = nx;
            y = ny;
            d = nd;
            return;
        }
        else d = nd;
    }

    int bx = x - dx[d];
    int by = y - dy[d];

    if(!board[bx][by]){
        x = bx; 
        y = by;
        return;
    }
    else {
        flag = 1;
        return;
    }
}


int main(){
    fastio;
    cin >> n >> m;
    cin >> x >> y >> d;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> board[i][j];
    while(true){
        step();
        if(flag) break;
    }
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) ans+=visited[i][j];
    cout << ans << '\n';
}
