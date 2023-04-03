#include <iostream>
#include <tuple>
#define fastio cin.tie(0)->sync_with_stdio(0)
#define BLANK make_tuple(-1, -1, -1)
using namespace std;

int n, m, k;
int ans = 0;
tuple<int, int, int> arr[100][100];
tuple<int, int, int> tmp[100][100];

void hunt(int col){
    for(int row = 0; row < n; row++){
        if(arr[row][col] != BLANK){
            int sz;
            tie(sz, ignore, ignore) = arr[row][col];
            ans += sz;
            arr[row][col] = BLANK;
            break;
        }
    }
}

tuple<int, int, int> get_next(int x, int y, int speed, int dir){
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while(speed--){
        int nx, ny;
        nx = x + dx[dir], ny = y + dy[dir];

        if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
            x = nx, y = ny;
        }
        else {
            dir = (dir%2 == 0) ? (dir+1) : (dir-1);
            x = x + dx[dir], y = y + dy[dir];
        }
    }
    return make_tuple(x, y, dir);
}

void move(int x, int y){
    int sz, speed, dir;
    tie(sz, speed, dir) = arr[x][y];
    int nx, ny, nd;
    tie(nx, ny, nd) = get_next(x, y, speed, dir);

    tuple<int, int, int> nw = make_tuple(sz, speed, nd);

    if(nw > tmp[nx][ny]){
        tmp[nx][ny] = nw;
    }
}

void moveall(){
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) tmp[i][j] = BLANK;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        if(arr[i][j] != BLANK){
            move(i, j);
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        arr[i][j] = tmp[i][j];
    }
}

void simul(int col){
    hunt(col);
    moveall();
}

int main() {
    fastio;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) arr[i][j] = BLANK;
    for(int i = 0; i < k; i++){
        int x, y, s, d, b;
        cin >> x >> y >> s >> d >> b; x--; y--; d--;
        if(d >= 2){
            s %= (2*m - 2);
        }
        else {
            s %= (2*n -2);
        }
        arr[x][y] = make_tuple(b, s, d);
    }

    for(int i = 0; i < m; i++){
        simul(i);
    }
    cout << ans;
    return 0;
}
