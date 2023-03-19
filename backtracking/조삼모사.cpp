#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <cmath>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n;
int evening[20];
int sc[20][20];
int mn = INT_MAX;

int calc(){
    int sun = 0;
    int night = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(evening[i] && evening[j]) night += sc[i][j];
            if(!evening[i] && !evening[j]) sun += sc[i][j];
        }
    }
    return abs(sun - night);
}

void findans(int cur, int st){
    if(cur == n/2){
        mn = min(mn, calc());
        return;
    }

    if(st >= n) return;

    findans(cur, st+1);
    
    evening[st] = 1;
    findans(cur + 1, st + 1);
    evening[st] = 0;
}

int main(){
    fastio;
    cin >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> sc[i][j];
    findans(0, 0);
    cout << mn << '\n';
}
