#include <iostream>
#include <queue>
#include <tuple>
#include <cmath>
#include <cstring>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

char arr[4][8];
int k;
int n, d;
int direc[4];

void move(int chair, int direction){
    if(direction == 1){
        char tmp = arr[chair][7];
        for(int i = 7; i >= 1; i--){
            arr[chair][i] = arr[chair][i-1];
        }
        arr[chair][0] = tmp; 
    }
    if(direction == -1){
        char tmp = arr[chair][0];
        for(int i = 0; i <= 6; i++){
            arr[chair][i] = arr[chair][i+1];
        }
        arr[chair][7] = tmp;
    }
}

int flip(int d){
    if (d == 1) return -1;
    else if (d== -1) return 1;
}

void moveall(){
    memset(direc, 0, sizeof direc);
    direc[n] = d;

    // left side
    for(int i = n; i > 0; i--){
        if(arr[i][6] != arr[i-1][2]){
            direc[i-1] = flip(direc[i]);
        }
        else break;
    }

    // right side
    for(int i = n; i < 3; i++){
        if(arr[i][2] != arr[i+1][6]){
            direc[i+1] = flip(direc[i]);
        }
        else break;
    }
    for(int i = 0; i < 4; i++){
        if(direc[i] != 0){
            move(i, direc[i]);
        }
    }


}
int ans = 0;
int main(){
    fastio;
    for(int i = 0; i < 4; i++) for(int j = 0; j < 8; j++) cin >> arr[i][j];
    cin >> k;
    while(k--){
        cin >> n >> d; n--;
        moveall();
    }
    for(int i = 0; i < 4; i++){
        if(arr[i][0] == '1') ans +=pow(2, i);
    }
    cout << ans << '\n';
}
