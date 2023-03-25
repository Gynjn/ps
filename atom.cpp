#include <iostream>
#include <tuple>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, c, k;
vector<tuple<int, int, int> > arr[50][50];
vector<tuple<int, int, int> > tmp[50][50];

void simul(){
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        tmp[i][j].clear();
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        while(arr[i][j].size()){
            int m, s, d;
            tie(m, s, d) = arr[i][j].back();
            arr[i][j].pop_back();
            int ni, nj;
            ni = (i + s*("00122210"[d] - '1')+n*s)%n;
            nj = (j + s*("12221000"[d] - '1')+n*s)%n;
            tmp[ni][nj].push_back({m,s,d});
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        arr[i][j].clear();
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if((int)tmp[i][j].size() == 1) arr[i][j].push_back(tmp[i][j].back());
        else if((int)tmp[i][j].size()>1){
            int ms = 0;
            int ss = 0;
            int ds[2] = {0, 0};
            int sz = tmp[i][j].size();
            while((int)tmp[i][j].size()){
                int m, s, d;
                tie(m,s,d) = tmp[i][j].back();
                tmp[i][j].pop_back();
                ms+=m;
                ss+=s;
                ds[d%2]++;
            }
            int sd;
            if(!ds[0] || !ds[1]) sd = 0;
            else sd = 1;
            if(ms/5 != 0){
                for(int l = sd; l < 8; l+=2){
                    arr[i][j].push_back(make_tuple(ms/5, ss/sz, l));                
                }
            }
        }
    }
}

int sol(){
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        int tp = 0;
        while((int)arr[i][j].size()){
            int m;
            tie(m,ignore,ignore) = arr[i][j].back();
            arr[i][j].pop_back();
            tp+=m;
        }
        ans += tp;
    }
    return ans;
}

int main() {
    fastio;
    cin >> n >> c >> k;
    while(c--){
        int x, y, m, s, d;
        cin >> x >> y >> m >> s >> d; 
        x--; 
        y--;
        arr[x][y].push_back(make_tuple(m, s, d));
    }
    while(k--){
        simul();
    }
    cout << sol() << '\n';
    return 0;
}
