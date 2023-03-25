#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int r, c, k;
int n = 3; 
int m = 3;
int arr[100][100];

int Row(int row){
    vector<pair<int, int> > v;
    for(int i = 1; i <= 100; i++){
        int freq = 0;
        for(int j = 0; j < m; j++){
            if(arr[row][j] == i) freq++;
        }
        if(freq)
            v.push_back({freq, i});
    }
    for(int i = 0; i < m; i++){
        arr[row][i] = 0;
    }

    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        int a, b;
        tie(a, b) = v[i];
        arr[row][i*2] = b;
        arr[row][i*2+1] = a;
    }

    return (int)v.size()*2;
}

int Col(int col){
    vector<pair<int, int> > v;
    for(int i = 1; i <= 100; i++){
        int freq = 0;
        for(int j = 0; j < n; j++){
            if(arr[j][col] == i) freq++;
        }
        if(freq)
            v.push_back({freq, i});
    }
    for(int i = 0; i < n; i++){
        arr[i][col] = 0;
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        int a, b;
        tie(a, b) = v[i];
        arr[2*i][col] = b;
        arr[2*i+1][col] = a;
    }
    return (int)v.size()*2;
}

void simul(){
    if(n >= m){
        int max_col = 0;
        for(int i = 0; i < n; i++){
            max_col = max(max_col, Row(i));
        }
        m = max_col;
    }
    else {
        int max_row = 0;
        for(int i = 0; i < m; i++){
            max_row = max(max_row, Col(i));
        }
        n = max_row;
    }
}

int main() {
    fastio;
    cin >> r >> c >> k; r--; c--;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> arr[i][j];
    int tme = -1;
    for(int i = 0; i <= 100; i++){
        if(arr[r][c] == k){
            tme = i;
            break;
        }
        simul();
    }
    cout << tme << '\n';
    return 0;
}
