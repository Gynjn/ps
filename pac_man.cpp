#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;
int n = 4;
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int m, t;
int pr, pc;
int monster[26][4][4][8];
int corpus[4][4][3];
int px[4] = {-1, 0, 1, 0};
int py[4] = {0, -1, 0, 1};

int tme = 1;

bool cango(int x, int y){
    if(x >= 4 || x < 0 || y >= 4 || y < 0) return false;
    return corpus[x][y][0] == 0 && corpus[x][y][1] == 0 && make_pair(pr, pc) != make_pair(x, y);
}

tuple<int, int, int> get_nxt_pos(int x, int y, int direc){
    for(int i = 0; i < 8; i++){
        int nd = (direc+ i+8) %8;
        int nx = x + dx[nd];
        int ny = y + dy[nd];
        if(cango(nx, ny)) return make_tuple(nx, ny, nd);
    }
    return make_tuple(x, y, direc);
}

void moveall(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 8; k++){
                tuple<int, int, int> nxt_pos = get_nxt_pos(i, j, k);
                int x, y, nxt_dir;
                tie(x, y, nxt_dir) = nxt_pos;
                monster[tme][x][y][nxt_dir] += monster[tme-1][i][j][k];
            }
        }
    }
}

int getnum(int d1, int d2, int d3){
    int dirs[3] = {d1, d2, d3};
    int x = pr, y = pc;
    int ans = 0;

    vector<pair<int, int> > visited;

    for(int i = 0; i < 3; i++){
        int nx = x + px[dirs[i]];
        int ny = y + py[dirs[i]];
        if(nx >= 4 || nx < 0 || ny >= 4 || ny < 0){
            return -1;
        }
        if(find(visited.begin(), visited.end(), make_pair(nx, ny)) == visited.end()){
            for(int j = 0; j < 8; j++){
                ans += monster[tme][nx][ny][j];
            }
            visited.push_back({nx, ny});
        }
        x = nx;
        y = ny;
    }
    return ans;
}

void kill(tuple<int, int, int> route){
    int dir1, dir2, dir3;
    tie(dir1, dir2, dir3) = route;

    int dirs[3] = {dir1, dir2, dir3};
    for(int i = 0; i < 3; i++){
        int nx = pr + px[dirs[i]];
        int ny = pc + py[dirs[i]];
        for(int j = 0; j < 8; j++){
            corpus[nx][ny][2] += monster[tme][nx][ny][j];
            monster[tme][nx][ny][j] = 0;
        }
        pr = nx;
        pc = ny;
    }
}

void pmove(){
    int mx = -1;
    tuple<int, int, int> proute;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                int tmp = getnum(i, j, k);
                if(tmp > mx){
                    mx = tmp;
                    proute = make_tuple(i, j, k);
                }
            }
        }
    }
    kill(proute);
}

void decy(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 2; k++){
                corpus[i][j][k] = corpus[i][j][k+1];
            }
            corpus[i][j][2] = 0;
        }
    }
}

void egg(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 8; k++){
                monster[tme][i][j][k] += monster[tme-1][i][j][k];
            }
        }
    }
}

void simul(){
    moveall();
    pmove();
    decy();
    egg();
}

int sol(){
    int tmp = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 8; k++){
                tmp += monster[t][i][j][k];
            }
        }
    }
    return tmp;
}

int main(){
    fastio;
    cin >> m >> t;
    cin >> pr >> pc; pr--; pc--;
    for(int i = 0; i < m; i++){
        int r, c, d;
        cin >> r >> c >> d;
        monster[0][r-1][c-1][d-1]++;
    }
    while(tme <= t){
        simul();
        tme++;
    }
    cout << sol();

}
