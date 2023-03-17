#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, k, c, px, py;
int ans = 0;
using vi = vector<int>;
using vvi = vector<vi>;
vvi poi(20, vi(20));

void grow(vvi& v){
    vvi tmp(n, vi(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(v[i][j] == 0 || v[i][j] == -1) continue;
        int cnt = 0;
        for(int d = 0; d < 4; d++){
            int dx = i + "0112"[d] - '1';
            int dy = j + "1021"[d] - '1';
            if(dx >= n || dx < 0 || dy >= n || dy < 0) continue;
            if(v[dx][dy] > 0) v[i][j]++;
            if(v[dx][dy] == 0 && poi[dx][dy] < 1) cnt++;
        }
        tmp[i][j] = cnt;
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(v[i][j] == -1){
            tmp[i][j] = -1;
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(tmp[i][j] == 0 && poi[i][j]==0 && v[i][j] == 0)
            for(int d = 0; d < 4; d++){
                int dx = i + "0112"[d] - '1';
                int dy = j + "1021"[d] - '1';
                if(dx >= n || dx < 0 || dy >= n || dy < 0) continue;
                if(poi[dx][dy] > 0) continue;
                if(tmp[dx][dy] > 0) v[i][j] += v[dx][dy]/tmp[dx][dy];
            }
    }
}

void select(vvi& v){
    int mx = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(v[i][j] <= 0) continue;
        int cnt = v[i][j];
        for(int d = 0; d < 4; d++){
            for(int l = 1; l <= k; l++){
                int dx = i + ("0022"[d] - '1')*l;
                int dy = j + ("0202"[d] - '1')*l;
                if(dx >= n || dx < 0 || dy >= n || dy < 0) break;
                if(v[dx][dy] <= 0) break;
                cnt += v[dx][dy];
            }
        }
        if (mx < cnt){
            mx = cnt;
            px = i;
            py = j;
        }
    }
    ans += mx;

    if(v[px][py] > 0){
        v[px][py] = 0;
        poi[px][py] = c+1;
        for(int d = 0; d < 4; d++){
            for(int l = 1; l <= k; l++){
                int dx = px + ("0022"[d] - '1')*l;
                int dy = py + ("0202"[d] - '1')*l;
                if(dx >= n || dx < 0 || dy >= n || dy < 0) break;
                if(v[dx][dy] < 0) break;
                if(v[dx][dy] == 0) {
                    poi[dx][dy] = c+1; break;
                }
                v[dx][dy] = 0;
                poi[dx][dy] = c+1;
            }
        }
    }
}

void tme(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (poi[i][j] > 0) poi[i][j]-=1;
        }
    }
}

int main(){
    fastio;
    cin >> n >> m >> k >> c;
    vvi v(n, vi(n));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> v[i][j];
    while(m--){
        grow(v);
        select(v);
        tme();        
    }


    cout << ans << '\n';
}
