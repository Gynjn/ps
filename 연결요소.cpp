#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int visited[1001];
vector<int> adj[1001];

void bfs(int st){
    queue<int> q; q.push(st); visited[st] = 1;
    while(q.size()){
        auto cur = q.front(); q.pop();
        for(auto& nxt : adj[cur]){
            if(visited[nxt]) continue;
            q.push(nxt), visited[nxt] = 1;
        }
    }
}

int main(){
    fastio;
    int n,m; cin >> n >> m;
    int ans = 0;
    while(m--){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i = 1; i <= n; i++){
        if(visited[i]) continue;
        bfs(i); ans++;
    }
    cout << ans;
}
