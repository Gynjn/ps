#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
pii cvs[30];
pii people[30];
int n, m;
int t = 0;
int dist[30][30];
int visited[30][30];
vvi v(30, vi(30));


void bfs(pii st){
    memset(dist, -1, sizeof dist);
    memset(visited, 0, sizeof visited);
    auto [pa, pb] = st;
    queue<pii> q; q.push(st); dist[pa][pb] = 0;
    visited[pa][pb] = 1;
    while(q.size()){
        auto [a, b] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int dx = a + "0112"[d] - '1';
            int dy = b + "1021"[d] - '1';
            if(dx >= n || dx < 0 || dy >= n || dy < 0) continue;
            if(v[dx][dy] != 1e9 && visited[dx][dy] == 0){
                dist[dx][dy] = dist[a][b] + 1;
                visited[dx][dy] = 1;
                q.push({dx, dy});
            }
        }
    } 
}


void step3(){
    if (t > m) return;
    bfs(cvs[t]);
    int mn = 1e9;
    int px = -1;
    int py = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(v[i][j] == 1 && dist[i][j] < mn && visited[i][j]){
                mn = dist[i][j];
                px = i;
                py = j;
            }
        }
    }
    people[t] = {px, py};
    v[px][py] = 1e9;
}

void step1(){
    for(int i = 1; i <= m; i++){
        auto [a, b] = people[i];
        if((a == -1 && b == -1) || people[i] == cvs[i]) continue;

        bfs(cvs[i]);
        auto [px, py] = people[i];

        int mn = 1e9;
        int mx = -1;
        int my = -1;
        for(int d = 0; d < 4; d++){
            int dx = px + "0112"[d] - '1';
            int dy = py + "1021"[d] - '1';
            if(dx >= n || dx < 0 || dy >= n || dy < 0) continue;
            if(v[dx][dy] != 1e9 && dist[dx][dy] < mn && visited[dx][dy]){
                mn = dist[dx][dy];
                mx = dx;
                my = dy;
            }
        }

        people[i] = {mx, my};
    }
}

void step2(){
    for(int i = 1; i <= m; i++){
        if(people[i] == cvs[i]){
            auto [px, py] = people[i];
            v[px][py] = 1e9;
        }
    }
}

bool End() {
    for(int i = 1; i <= m; i++) {
        if(people[i] != cvs[i])
            return false;
    }

    return true;
}

int main(){
    fastio;
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> v[i][j];
    for(int i = 1; i <= m; i++){
        int x, y; cin >> x >> y; x--; y--;
        cvs[i] = {x, y};
    }
    for(int i = 1; i <= m; i++){
        people[i] = {-1, -1};
    }
    while(true){
        t++;
        step1();
        step2();
        step3();
        if(End()) break;  
    }
    cout << t;
    return 0;
}
