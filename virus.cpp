#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, k;
int nutriadd[10][10];
int nutri[10][10];
vector<int> virus[10][10];
vector<int> nvirus[10][10];
int nnutri[10][10];

void simul(){
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        nvirus[i][j].clear();
        nnutri[i][j] = 0;
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        sort(virus[i][j].begin(), virus[i][j].end());
        for(int k = 0; k < virus[i][j].size(); k++){
            int age = virus[i][j][k];
            if (nutri[i][j] >= age){
                nutri[i][j] -= age;
                nvirus[i][j].push_back(age+1);
            }
            else nnutri[i][j] += age/2;
        }

        nnutri[i][j] += nutri[i][j];
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        for(int k = 0; k < nvirus[i][j].size(); k++){
            int age = nvirus[i][j][k];
            if(age%5 == 0){
                for(int d = 0; d < 8; d++){
                    int dx = i + "00122210"[d] - '1';
                    int dy = j + "12221000"[d] - '1';
                    if(dx >= 0 && dy >= 0 && dx < n && dy < n) nvirus[dx][dy].push_back(1);
                }
            }
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        nnutri[i][j] += nutriadd[i][j];
    }

    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        nutri[i][j] = nnutri[i][j];
        virus[i][j] = nvirus[i][j];
    }


}

int main() {
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> nutriadd[i][j];
    while(m--){
        int r, c, age;
        cin >> r >> c >> age; 
        r--;
        c--;
        virus[r][c].push_back(age);
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) nutri[i][j]=5;
    while(k--){
        simul();
    }
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) ans+=virus[i][j].size();
    cout << ans << '\n';
    return 0;
}
