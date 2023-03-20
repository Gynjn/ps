#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>
#include <cstring>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int arr[8][8];
int visited[8][8];
int mx;
vector<pair<int, int> > emtpycoord;
queue<pair<int, int> > firecoord;
vector<int> selected;

void area(){
    memset(visited, 0, sizeof visited);
    for(int i = 0; i < selected.size(); i++){
        int idx = selected[i];
        int cx = emtpycoord[idx].first;
        int cy = emtpycoord[idx].second;
        arr[cx][cy] = 1;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] == 2){
                firecoord.push({i, j});
                visited[i][j] = 1;
            }
        }
    }

    while(firecoord.size()){
        pair<int , int> cf = firecoord.front();
        int cx = cf.first;
        int cy = cf.second;
        firecoord.pop();

        for(int d = 0; d < 4; d++){
            int nx = cx + "1012"[d] -'1';
            int ny = cy + "0121"[d] -'1';
            if(nx >= n || nx < 0 || ny >= m || ny < 0) continue;
            if(!visited[nx][ny] && arr[nx][ny] == 0){
                visited[nx][ny] = 1; firecoord.push({nx, ny});
            }
        }
    }
    int empty_cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(!visited[i][j] && arr[i][j] == 0)
                empty_cnt++;
    mx = max(empty_cnt, mx);

    for(int i = 0; i < (int) selected.size(); i++) {
        int idx = selected[i];
        int cx = emtpycoord[idx].first;
        int cy = emtpycoord[idx].second;

        arr[cx][cy] = 0;
    }
}

void fm(int cur, int cnt){
    if(cnt == 3){
        area();
        return;
    }

    if(cur == emtpycoord.size()) return;

    fm(cur+1, cnt);

    selected.push_back(cur);
    fm(cur+1, cnt+1);
    selected.pop_back();
}



int main(){
    fastio;
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        cin >> arr[i][j];
        if(arr[i][j] == 0){
            emtpycoord.push_back({i,j});
        }
    }
    fm(0, 0);
    cout << mx << '\n';
}
