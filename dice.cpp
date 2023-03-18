#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <tuple>

#define fastio cin.tie(0)->sync_with_stdio(0)

using namespace std;

int n, m;
int x, y, k;
int board[20][20];
int mov[1000];
int dice[7];
int u = 1, f = 2, r = 3;

pair<int, int> posupdate(int x, int y, int md){
    int dx = x + "1102"[md] - '1';
    int dy = y + "2011"[md] - '1';
    if(dx < 0 || dx >= n || dy < 0 || dy >= m) return make_pair(-1, -1);
    return make_pair(dx, dy);
}

void play(int md){
    pair<int, int> pos = posupdate(x, y, md);

    if (pos == make_pair(-1, -1)) return;

    tie(x, y) = pos;

    if(md == 0) tie(u, f, r) = make_tuple(7-r, f, u);
    else if(md == 1) tie(u, f, r) = make_tuple(r, f, 7-u);
    else if(md == 2) tie(u, f, r) = make_tuple(f, 7 - u, r);
    else tie(u, f, r) = make_tuple(7 - f, u, r);

    int bot = 7-u;
    if(board[x][y] == 0){
        board[x][y] = dice[bot];
    }
    else {
        dice[bot] = board[x][y];
        board[x][y] = 0;
    }
    cout << dice[u] << '\n';
}

int main(){
    fastio;
    cin >> n >> m >> x >> y >> k;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> board[i][j];
    for(int i = 0; i < k; i++) {
        cin >> mov[i];
        mov[i]--;
    }

    for(int i = 0; i < k; i++) play(mov[i]);
}
