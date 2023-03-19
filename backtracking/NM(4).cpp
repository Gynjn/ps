#include <iostream>
#include <algorithm>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int arr[10];
int visited[10];

void dfs(int dep, int st){
    if (dep == m){
        for(int i = 0; i < m; i++) cout << arr[i] << ' ';
        cout << '\n';
        return;
    }
    for(int i = st; i <= n; i++){
        arr[dep] = i;
        dfs(dep+1, i);
    }
}

int main(){
    fastio;
    cin >> n >> m;
    dfs(0, 1);
}
