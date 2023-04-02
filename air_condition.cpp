#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <cstring>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, k;
int arr[20][20];
int tme = 0;
int cool[20][20];
int tmp[20][20];
int barrior[20][20][4];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
int visited[20][20];

bool inrange(int x, int y){
    return x >= 0 && x < n && y < n && y >= 0;
}

int direc(int x_diff, int y_diff){
    for(int i = 0; i < 4; i++){
        if(dx[i] == x_diff && dy[i] == y_diff) return i;
    }
}

void spread(int x, int y, int dir, int power){
    if(power == 0) return;

    visited[x][y] = true;
    cool[x][y] += power;

    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if(inrange(nx, ny) && !visited[nx][ny] && !barrior[x][y][dir]){
        spread(nx, ny, dir, power-1);
    }

    if(dx[dir] == 0){
        int nxs[2] = {x-1, x+1};
        for(int i = 0; i < 2; i++){
            int nx = nxs[i];
            int ny = y + dy[dir];
            if(inrange(nx, ny) && !visited[nx][ny] && !barrior[nx][y][dir] && !barrior[x][y][direc(nx-x, 0)]){
                spread(nx, ny, dir, power-1);
            }
        }
    }
    else{
        int nys[2] = {y-1, y+1};
        for(int i = 0; i < 2; i++){
            int nx = x + dx[dir];
            int ny = nys[i];
            if(inrange(nx, ny) && !visited[nx][ny] && !barrior[x][ny][dir] && !barrior[x][y][direc(0, ny-y)]){
                spread(nx, ny, dir, power-1);
            }
        }
    }
}

void air(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] > 1){
                int dir = (arr[i][j] <= 3) ? (3 - arr[i][j]) : (arr[i][j] - 2);

                int nx = i + dx[dir];
                int ny = j + dy[dir];
                memset(visited, 0, sizeof visited);
                spread(nx, ny, dir, 5);
            }
        }
    }
}

int get_mix(int x, int y){
    int tmp_cool = cool[x][y];
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(inrange(nx, ny) && !barrior[x][y][i]){
            if(cool[nx][ny] < cool[x][y]){
                tmp_cool -= (cool[x][y] - cool[nx][ny])/4;
            }
            else tmp_cool += (cool[nx][ny] - cool[x][y])/4;
        }
    }
    return tmp_cool;
}

void mix(){
    memset(tmp, 0, sizeof tmp);
    for(int i = 0; i< n; i++){
        for(int j = 0; j < n; j++){
            tmp[i][j] = get_mix(i, j);
        }
    }
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n; j++){
            cool[i][j] = tmp[i][j];
        }
    }
}

void side(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if((i == 0 || i == n-1 || j == 0 || j == n-1) && cool[i][j]) cool[i][j]--;
        }
    }
}


void simul(){
    air();   
    mix(); 
    side();
    tme++;
}

bool end(){
    if(tme > 100) return true;

    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(arr[i][j] == 1 && cool[i][j] < k) return false;
    }
    return true;
}

int main() {
    fastio;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        cin >> arr[i][j];
    }
    while(m--){
        int x, y, s;
        cin >> x >> y >> s; x--; y--;
        barrior[x][y][s] = true;
        int nx = x + dx[s];
        int ny = y + dy[s];

        if(nx >= 0 && nx < n && ny >= 0 && ny < n){
            barrior[nx][ny][3-s] = true;
        }
    }
    while(!end()){
        simul();        
    }

    if(tme <= 100) cout << tme << '\n';
    else cout << -1 << '\n';
    return 0;
}
