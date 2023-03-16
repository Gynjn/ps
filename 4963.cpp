#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
int n, m;
int bfs(vvi& v, vvi& visited){
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        if(visited[i][j] || !v[i][j]) continue;
        queue<pii> q;
        q.push({i,j});
        visited[i][j] = 1;
        ans++;
        while(q.size()){
            auto [a, b] = q.front(); q.pop();
            for(int d = 0; d < 8; d++){
                int dx = a + "00011222"[d] - '1';
                int dy = b + "01202012"[d] - '1';
                if (dx >= n || dx < 0 || dy >= m || dy < 0 ) continue;
                if (v[dx][dy] && !visited[dx][dy]) {
                    q.push({dx, dy});
                    visited[dx][dy] = 1;
                }
            }
        }
    }
    return ans;
}

int main(){
    fastio;
    while(cin >> m >> n && (n && m)){
        vvi v(50, vi(50));
        vvi visited(50, vi(50));
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> v[i][j];
        cout << bfs(v, visited) << '\n';
    }
}
