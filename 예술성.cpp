#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

int n;
int groupnum;
vvi visited(29, vi(29));
vvi group(29, vi(29));
int ng[29*29+1];

void rotate(vvi& v){
    const int n = v.size();
    vvi tmp(n, vi(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            tmp[i][j] = v[j][n-1-i];
        }
    }
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            tmp[i][j] = v[n/2-1-j][i];
        }
    }
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            tmp[i][j+n/2+1] = v[n/2-1-j][i+n/2+1];
        }
    }
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            tmp[i+n/2+1][j] = v[n-1-j][i];
        }
    }
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            tmp[i+n/2+1][j+n/2+1] = v[n-1-j][i+n/2+1];
        }
    }
    v = tmp;
}

void makegroup(vvi& v){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            visited[i][j] = 0;
            group[i][j] = 0;
        }
    }
    memset(ng, 0, sizeof ng);
    groupnum = 1;
    for(int i = 0; i<n; i++) for(int j = 0; j < n; j++){
        if(visited[i][j]) continue;
        queue<pii> q; q.push({i,j}); visited[i][j] = 1; group[i][j] = groupnum;
        while(q.size()){
            auto [x, y] = q.front(); q.pop();
            for(int d = 0; d < 4; d++){
                int dx = x + "0112"[d] - '1';
                int dy = y + "1021"[d] - '1';
                if(dx >= n || dx < 0 || dy >= n || dy < 0) continue;
                if(!visited[dx][dy] && v[x][y] == v[dx][dy]) {
                    q.push({dx,dy});
                    visited[dx][dy] = 1;
                    group[dx][dy] = groupnum;
                }
            }
        }
        groupnum++;
    }
    groupnum-=1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ng[group[i][j]]++;
        }
    }
}

int getscore(vvi& v){
    int score=0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int d = 0; d < 4; d++){
                int dx = i + "0112"[d] - '1';
                int dy = j + "1021"[d] - '1';
                if(dx >= n || dx < 0 || dy >= n || dy < 0) continue;
                if(v[i][j] != v[dx][dy]){
                    int a = ng[group[i][j]];
                    int b = ng[group[dx][dy]];
                    int av = v[i][j];
                    int bv = v[dx][dy];
                    score += (a+b)*av*bv;
                }
            }
        }
    }
    return score/2;
}

int sol(vvi& v){
    makegroup(v);
    return getscore(v);
}

int main(){
    fastio;
    cin >> n;
    vvi v(n, vi(n));
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> v[i][j];
    ans += sol(v);
    for(int i = 0; i < 3; i++){
        rotate(v);
        ans += sol(v);
    }
    cout << ans;
}
