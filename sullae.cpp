#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cstdlib>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, h, k;
vector<int> v[100][100];
vector<int> tmp[100][100];
bool tree[100][100];
int sullaefor[100][100];
int sullaerev[100][100];
pair<int, int> sullaepos;
bool forwarding = true;
int ans = 0;

void sullae(){
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    int cur_x = n/2; int cur_y = n/2;
    int direc = 0; int step = 1;
    while(cur_x || cur_y){
        for(int i = 0; i < step; i++){
            sullaefor[cur_x][cur_y] = direc;
            cur_x += dx[direc]; cur_y += dy[direc];
            sullaerev[cur_x][cur_y] = (direc < 2) ? (direc+2) : (direc-2);

            if(!cur_x && !cur_y) break;
        }
        direc = (direc+1)%4;
        if(direc == 0 || direc == 2) step++;
    }
}

int runcheck(int x, int y){
    int sx, sy;
    tie(sx, sy) = sullaepos;
    return abs(sx-x) + abs(sy-y);
}

void rm(int x, int y, int direc){
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {-1, 1, 0, 0};

    int nx = x + dx[direc], ny = y + dy[direc];

    if(nx < 0 || nx >= n || ny < 0 || ny >= n){
        direc = (direc < 2) ? (1-direc) : (5-direc);
        nx = x + dx[direc]; ny = y + dy[direc];
    }
    if (sullaepos == make_pair(nx, ny)){
        tmp[x][y].push_back(direc);
    }
    else tmp[nx][ny].push_back(direc);

}

void runnermove(){
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        tmp[i][j].clear();
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(runcheck(i, j) <= 3){
                for(int l = 0; l < (int) v[i][j].size(); l++){
                    rm(i, j, v[i][j][l]);
                }
            }
            else{
                for(int l = 0; l < (int) v[i][j].size(); l++){
                    tmp[i][j].push_back(v[i][j][l]);
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            v[i][j] = tmp[i][j];
        }
    }
}

int get_sullae_direc(){
    int sx, sy;
    tie(sx, sy) = sullaepos;
    if(forwarding){
        return sullaefor[sx][sy];
    }
    else return sullaerev[sx][sy];
}

void direc_check(){
    if(sullaepos == make_pair(0,0) && forwarding){
        forwarding = false;
    }
    if(sullaepos == make_pair(n/2,n/2) && !forwarding){
        forwarding = true;
    }
}

void sullaemove(){
    int sx, sy;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    tie(sx, sy) = sullaepos;
    int direc = get_sullae_direc();
    sullaepos = make_pair(sx + dx[direc], sy + dy[direc]); 
    direc_check();
}

void score(int t){
    int sx, sy;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    tie(sx, sy) = sullaepos;
    int direc = get_sullae_direc();
    for(int i = 0; i < 3; i++){
        int nx = sx + i*dx[direc], ny = sy + i*dy[direc];
        if(nx < n && nx >= 0 && ny < n && ny >= 0 && tree[nx][ny] == 0){
            ans += t * (int) v[nx][ny].size();
            v[nx][ny].clear();
        }
    }

}

int main(){
    fastio;
    cin >> n >> m >> h >> k;
    while(m--){
        int x, y, d;
        cin >> x >> y >> d; x--; y--;
        v[x][y].push_back(d);
    }
    while(h--){
        int x, y;
        cin >> x >> y; x--; y--;
        tree[x][y] = true;
    }

    sullaepos = make_pair(n/2, n/2);
    sullae();
    for(int i = 1; i <= k; i++){
        runnermove();
        sullaemove();
        score(i);
    }
    cout << ans << '\n';
}
