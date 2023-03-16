#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
vvi v(100, vi(100));
vvi dist(100, vi(100));

void bfs(){
    queue<pii> q; q.push({0,0});
    dist[0][0] = 1;
    while(q.size()){
        auto [a, b] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int dx = a + "0112"[d] - '1';
            int dy = b + "1021"[d] - '1';
            if(dx >= n || dx < 0 || dy >= m || dy < 0) continue;
            if(!dist[dx][dy] && v[dx][dy]){
                q.push({dx, dy}); dist[dx][dy] = dist[a][b]+1;
            }
        }
    }
    cout << dist[n-1][m-1];
}

int main(){
    fastio;
    cin >> n >> m;
    string s[n];
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            v[i][j] = s[i][j]-'0';
        }
    }
    bfs();
}
