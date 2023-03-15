 /******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int f(int x, int mod){
    return (x%mod + mod) % mod;
}

void move(vvi& cl, int d, const int s){
    const int n = cl.size();
    d--;
    vvi temp(n, vi(n));
    int dx = "10001222"[d] - '1';
    int dy = "00122210"[d] - '1';
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        temp[f(i+s*dx,n)][f(j+s*dy,n)] = cl[i][j];
    }
    cl = temp;
}

void rain(vvi& v, vvi& cl, vvi& check){
    const int n = v.size();
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if (cl[i][j] == 1) {
            v[i][j]++;
            check[i][j] = 1;
        }
    }
}

void Set(vvi& cl){
    const int n = cl.size();
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cl[i][j] = 0;
}

void magic(vvi& v, vvi& cl, vvi& check){
    const int n = v.size();
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(check[i][j] == 1){
            for(int d = 0; d < 4; d++){
                int dx = "0022"[d] - '1';
                int dy = "0220"[d] - '1';
                int cnt = 0;
                if (i + dx < 0 || i + dx >= n || j + dy < 0 || j + dy >= n) continue;
                v[i][j] += !!v[i+dx][j+dy];
            }
        }
    }
}

void clmake(vvi& v, vvi& cl, vvi& clck){
    const int n = v.size();
    for(int i = 0; i < n; i++) for (int j = 0; j < n; j++){
        if(v[i][j] < 2 || clck[i][j]==1) continue;
        v[i][j] -= 2;
        cl[i][j] = 1;
    }
}

void sol(vvi& v, vvi& cl, int d, const int s){
    const int n = v.size();
    move(cl, d, s);
    vvi clck(n, vi(n));
    clck = cl;
    vvi check(n, vi(n));
    rain(v, cl, check);
    Set(cl);
    magic(v, cl, check);
    clmake(v, cl, clck);
}

int main(){
    fastio;
    int n, m; cin >> n >> m;
    vvi v(n, vi(n));
    vvi cl(n, vi(n));
    cl[n-1][0] = 1; cl[n-1][1] = 1; cl[n-2][0] = 1; cl[n-2][1] = 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> v[i][j];
    while(m--){
        int d, s; cin >> d >> s;
        sol(v, cl, d, s);
    }
    int answer = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        answer += v[i][j];
    }
    cout << answer << '\n';
    
}
