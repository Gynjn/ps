#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <climits>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n;
int arr[11];
int opnum[3];
int mx = INT_MIN;
int mn = INT_MAX;
vector<int> opuse;

bool ispos(){
    for(int i = 0; i < 3; i++){
        if(opnum[i]<0) return false;
    }
    return true;
}

int calc(){
    int tmp = arr[0];
    for(int i = 0; i < opuse.size(); i++){
        if(opuse[i] == 0){
            tmp += arr[i+1];
        }
        else if(opuse[i] == 1){
            tmp -= arr[i+1];
        }
        else {
            tmp *= arr[i+1];
        }
    }
    return tmp;
}

void fm(int cur){
    if(cur == n-1){
        if(ispos()){
            int val = calc();
            mx = max(mx, val);
            mn = min(mn, val);
        }
        return;
    }

    for(int i = 0; i < 3; i++){
        opuse.push_back(i);
        opnum[i]--;

        fm(cur + 1);
        opuse.pop_back();
        opnum[i]++;
    }
}

int main(){
    fastio;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < 3; i++){
        cin >> opnum[i];
    }
    fm(0);
    cout << mn << ' ' << mx << '\n';
    return 0;
}
