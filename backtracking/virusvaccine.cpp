#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <tuple>
#include <cstring>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int mn = INT_MAX;
int n, m;
int arr[50][50];
vector<pair<int, int> > hospital;
vector<int> selected;
int dist[50][50];
queue<pair<int, int> > q;

int solve(){
    memset(dist, -1, sizeof dist);
    for(int i = 0; i < selected.size(); i++){
        int idx = selected[i];
        int cx = hospital[idx].first;
        int cy = hospital[idx].second;
        q.push({cx, cy}); dist[cx][cy] = 0;
    }
    while(q.size()){
        int x, y;
        tie(x, y) = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int nx = x + "1012"[d] - '1';
            int ny = y + "0121"[d] - '1';
            if(nx >= n || nx < 0 || ny >= n || ny < 0) continue;
            if(arr[nx][ny]  != 1 && dist[nx][ny] == -1){
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    int tmp = 0;
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(arr[i][j] == 0){
                if(dist[i][j] != -1)
                    tmp = max(tmp, dist[i][j]);
                else tmp = INT_MAX;
            }
        }
    }
    return tmp;
}

void fm(int cur, int cnt){
    if(cnt == m){
        mn = min(mn, solve());
        return;
    }

    if(cur == hospital.size()) return;

    fm(cur+1, cnt);

    selected.push_back(cur);
    fm(cur+1, cnt+1);
    selected.pop_back();
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        cin >> arr[i][j];
        if(arr[i][j] == 2){
            hospital.push_back({i, j});
        }
    }
    fm(0, 0);
    if (mn == INT_MAX) {
        cout << -1;
        return 0;
    }
    cout << mn;

}
