#include <iostream>
#include <algorithm>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m;
int arr[10];
int visited[10];

void DFS(int dep){
    if(dep == m){
        for(int i = 0; i < dep; i++) cout << arr[i] << ' ';
        cout << '\n';
        return;
    }
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            visited[i] = 1; arr[dep] = i;
            DFS(dep+1);
            visited[i] = 0;
        }
    }
}

int main(){
    fastio;
    cin >> n >> m;
    DFS(0);
}
