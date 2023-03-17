#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
int dist[20][20];
int x, y; 
int shark;
int sharkmeal;
int flag;
int ex, ey;
int ans = 0;

void check(vvi& v){
    memset(dist, -1, sizeof dist);
    queue<pii> q; q.push({x, y}); dist[x][y] = 0;
    while(q.size()){
        auto [a, b] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int da = a + "0112"[d] - '1';
            int db = b + "1021"[d] - '1';
            if(da >= n || da < 0 || db >= n || db < 0) continue;
            if(dist[da][db] == -1 && shark >= v[da][db]){
                q.push({da, db});
                dist[da][db] = dist[a][b] + 1;
            }
        }
    }

}

void eat(vvi& v){
    int mn = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (dist[i][j] == -1 || dist[i][j] == 0) continue;
            if (v[i][j] >= shark || v[i][j] == 0) continue;
            int tmp = mn;
            mn = min(mn, dist[i][j]);
            if(tmp != mn){
                ex = i;
                ey = j;
            }
        }
    }
    if (mn == 1e9) {
        flag = 1;
        return;
    }
    v[x][y] = 0;
    x = ex; y = ey; ans+=mn; sharkmeal++;
    v[ex][ey] = 9;
    if(sharkmeal==shark){
        shark+=1;
        sharkmeal = 0;
    }
}



int main(){
    fastio;
    cin >> n;
    vvi v(n, vi(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        cin >> v[i][j];
        if (v[i][j] == 9){
            x = i;
            y = j;
        }
    }
    shark = 2;
    int i = 4;
    while(!flag){
        check(v);
        eat(v);   
    }
    cout << ans << ' ';
}
