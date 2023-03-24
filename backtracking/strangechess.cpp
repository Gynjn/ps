#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>
#include <algorithm>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int chess[8][8];
int mydi[8][8];
int area = 1e9;
int visited[8][8];
vector<pair<int, int> > my;

bool possiblemove[6][4] = {
    {},
    {1, 0, 0, 0},
    {0, 1, 0, 1},
    {1, 1, 0, 0},
    {1, 1, 0, 1},
    {1, 1, 1, 1}
};

void mark(int x, int y){
    int num = chess[x][y];
    int direc = mydi[x][y];
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    for(int i = 0; i < 4; i++){
        if(!possiblemove[num][i]) continue;

        int sx = x;
        int sy = y;
        int md = (i+direc) % 4;
        while(true){
            visited[sx][sy] = 1;
            int nx = sx + dx[md];
            int ny = sy + dy[md];
            if (nx < n && nx >= 0 && ny < m && ny >= 0 && chess[nx][ny] != 6){
                sx = nx;
                sy = ny;
            }           
            else break; 
        }
    }
}

int get(){
    memset(visited, 0, sizeof visited);
    for(int i = 0; i < my.size(); i++){
        int x, y;
        tie(x, y) = my[i];
        mark(x, y);
    }

    int ans = 0;

    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        if(visited[i][j] == 0 && chess[i][j] != 6) ans++;
    }
    return ans;
}

void findmin(int cnt){
    if (cnt == my.size()){
        area = min(area, get());
        return;
    }
    int x, y;
    tie(x, y) = my[cnt];

    for(int i = 0; i < 4; i++){
        mydi[x][y] = i;
        findmin(cnt+1);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        cin >> chess[i][j];
        if(chess[i][j]>= 1 && chess[i][j] <= 5) my.push_back({i,j});
    }
    findmin(0);
    cout << area;
}
