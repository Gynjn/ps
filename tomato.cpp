#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;


vvi v(1000, vi(1000));
queue<pii> q;

void check(){
    int ans = 0;
    for(int i = 0; i< n; i++){
        for(int j = 0; j < m; j++){
            if (v[i][j]==0) {cout << -1; return;}
            else ans = max(ans, v[i][j]-1); 
        }
    }
    cout << ans;
}

void bfs(){
    while(q.size()){
        auto [a, b] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int dx = a + "0112"[d] - '1';
            int dy = b + "1021"[d] - '1';
            if (dx >= n || dx < 0 || dy >= m || dy < 0) continue;
            if(v[dx][dy] == 0) {
                q.push({dx, dy});
                v[dx][dy] = v[a][b] + 1; 
            }
        }
    }
}

int main(){
    fastio;
    cin >> m >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        cin >> v[i][j];
        if (v[i][j] == 1){
            q.push({i, j});
        }
    }
    bfs();
    check();
    
}
