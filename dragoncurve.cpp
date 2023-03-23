#include <iostream>
#include <tuple>
#include <utility>
#include <cstring>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n;
bool arr[101][101];
bool tmp[101][101];
bool dotmp[101][101];

pair<int, int> update(int x, int y, int cx, int cy){
    return make_pair(y-cy+cx, cx-x+cy);
}

void step(int cx, int cy){
    for(int i = 0; i <= 100; i++){
        for(int j = 0; j <= 100; j++){
            dotmp[i][j] = false;
        }
    }
    for(int i = 0; i <= 100; i++){
        for(int j = 0; j <= 100; j++){
            if(tmp[i][j]){
                int nx, ny;
                tie(nx, ny) = update(i, j, cx, cy);
                dotmp[nx][ny] = true;
            }
        }
    }
    for(int i = 0; i <= 100; i++){
        for(int j = 0; j <= 100; j++){
            if(dotmp[i][j]) 
            {
                tmp[i][j] = true;                
            }
        }
    }
}

void curve(int x, int y, int d, int g){
    for(int i = 0; i <= 100; i++)
    {
        for(int j = 0; j <= 100; j++){
            tmp[i][j] = false;                    
        }
    }
    int dx[4] = {0, -1, 0, 1};
    int dy[4] = {1, 0, -1, 0};

    int sx = x;
    int sy = y;
    int ex = x + dx[d];
    int ey = y + dy[d];
    tmp[sx][sy] = true;
    tmp[ex][ey] = true;

    while(g--){
        step(ex, ey);
        tie(ex, ey) = update(sx, sy, ex, ey);
    }
    for(int i = 0; i <= 100; i++){
        for(int j = 0; j <= 100; j++){
            if(tmp[i][j])
            {
                arr[i][j] = true;                
            }
        }
    }

}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++){
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        curve(x, y, d, g);
    }
    int ans = 0;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            if(arr[i][j] && arr[i+1][j] && arr[i][j+1] && arr[i+1][j+1])
            {
                ans++;                
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
