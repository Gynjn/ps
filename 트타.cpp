#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int v[15][15];
int nutri[15][15];
int x, y;
int ans = 0;



void move(){
    int dx = "10001222"[x] - '1';
    int dy = "22100012"[x] - '1';
    int tmp[15][15];
    memset(tmp , 0, sizeof tmp);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(nutri[i][j] == 1){
            int xloc = (i + dx*y + n*y)%n;
            int yloc = (j + dy*y + n*y)%n;
            tmp[xloc][yloc] = 1;
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        nutri[i][j] = tmp[i][j];
    }
}

void grow(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(nutri[i][j] == 1) v[i][j]++;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(nutri[i][j] == 0) continue;
            for(int d = 0; d < 4; d++){
                int dx = i + "0022"[d] - '1';
                int dy = j + "2002"[d] - '1';
                if( dx >= n || dx < 0 || dy >= n || dy < 0) continue;
                if(v[dx][dy] > 0) v[i][j] += 1;
            }
        }
    }
}

void change(){
    int tmp[15][15];
    memset(tmp, 0, sizeof tmp);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(v[i][j] >= 2 && nutri[i][j] == 0){
            v[i][j]-=2;
            tmp[i][j] = 1;
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        nutri[i][j] = tmp[i][j];
    }
}

int sol(){
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) ans += v[i][j];
    return ans;
}

int main(){
    fastio;
    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> v[i][j];
    nutri[n-1][0] = 1; nutri[n-2][0] = 1; nutri[n-1][1] = 1; nutri[n-2][1] = 1;
    while(m--){
        cin >> x >> y; x--; ;
        move();
        grow();
        change();           
    }
    cout << sol() << '\n';
}
