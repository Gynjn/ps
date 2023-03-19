#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n;
int x, y;
pair<int, int> tme[15];
int pay[15];
int max_profit;
vector<int> selected;

bool ispossible(){
    for(int i = 0; i < (int) selected.size()-1; i++){
        if(tme[selected[i]].second >= tme[selected[i+1]].first) return false;
    }
    for(int i = 0; i < selected.size(); i++){
        if (tme[selected[i]].second > n) return false; 
    }
    return true;
}

int Get_profit(){
    int tmp = 0;
    for(int i = 0; i < selected.size(); i++){
        tmp += pay[selected[i]];
    }
    return tmp;
}

void DFS(int cur_idx){
    if(cur_idx == n){
        if(ispossible()){
            max_profit = max(max_profit, Get_profit());
        }
        return;
    }

    DFS(cur_idx + 1);
    selected.push_back(cur_idx);
    DFS(cur_idx + 1);
    selected.pop_back();
}

int main() {
    fastio;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> x >> y;
        tie(tme[i-1].first, tme[i-1].second) = make_pair(i, i + x -1);
        pay[i-1] = y;
    }
    DFS(0);
    cout << max_profit;

    return 0;
}
