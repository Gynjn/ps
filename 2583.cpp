#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <tuple>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, k;
int board[100][100];
int visited[100][100];
vector<int> ekq;

int dfs(int x, int y){
    int tmp = 1;
    visited[x][y] = 1;
    for(int d = 0; d < 4; d++){
		const int nx = x + "1012"[d] - '1';
		const int ny = y + "2101"[d] - '1';
		if(nx >= n || nx < 0 || ny >= m || ny < 0) continue;
		if(!visited[nx][ny] && !board[nx][ny]) tmp += dfs(nx, ny);
    }
    return tmp;
}

int main(){
    fastio;
    cin >> m >> n >>k;
    while(k--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for(int i = x1; i < x2; i++) for(int j = y1; j < y2; j++) board[i][j] = 1;
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        if (visited[i][j] || board[i][j]) continue;
        ekq.push_back(dfs(i, j)); 
    }
    sort(ekq.begin(), ekq.end());
    cout << ekq.size() << '\n';
    for(int i : ekq) cout << i << ' '; 
}
