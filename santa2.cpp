#include <iostream>
#include <vector>
#include <unordered_map>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int q;
int head[100001], tail[100001];
int sz[100001];
unordered_map<int, int> prv, nxt;

void Build(){
    int n, m;
    cin >> n >> m;
    vector<int> box[100000];
    for(int i = 1; i <=m; i++){
        int num;
        cin >> num;
        num--;
        box[num].push_back(i);
    }
    for(int i = 0; i < n; i++){
        if((int) box[i].size() == 0) continue;
        head[i] = box[i].front();
        tail[i] = box[i].back();
        sz[i] = (int) box[i].size();

        for(int j = 0; j < (int) box[i].size() - 1; j++){
            prv[box[i][j+1]] = box[i][j];
            nxt[box[i][j]] = box[i][j+1];
        }
    }
}

void Move(){
    int m_src, m_dst;
    cin >> m_src >> m_dst;
    m_src--;
    m_dst--;
    if(sz[m_src] == 0){
        cout << sz[m_dst] << '\n';
        return;
    }
    if(sz[m_dst] == 0){
        head[m_dst] = head[m_src];
        tail[m_dst] = tail[m_src];
    }
    else{
        prv[head[m_dst]] = tail[m_src];
        nxt[tail[m_src]] = head[m_dst];
        head[m_dst] = head[m_src];
    }

    head[m_src] = tail[m_src] = 0;
    sz[m_dst] += sz[m_src];
    sz[m_src] = 0;

    cout << sz[m_dst] << '\n';
}

int rmhead(int num){
    if(!sz[num]){
        return 0;
    }
    if(sz[num] == 1){
        int tmp = head[num];
        head[num] = tail[num] = 0;
        sz[num] = 0;
        return tmp;
    }

    int tmp = head[num];
    int nxt_head = nxt[tmp];
    nxt[tmp] = prv[nxt_head] = 0;
    sz[num]--;
    head[num] = nxt_head;
    return tmp;
}

void pushhead(int num, int tmp){
    if(tmp == 0) return;
    if(sz[num] == 0){
        head[num] = tail[num] = tmp;
        sz[num] = 1;
        return;
    }
    int oghead = head[num];
    prv[oghead] = tmp;
    nxt[tmp] = oghead;
    head[num] = tmp;
    sz[num]++;
}

void Change(){
    int m_src, m_dst;
    cin >> m_src >> m_dst;
    m_src--;
    m_dst--;
    int src_head = rmhead(m_src);
    int dst_head = rmhead(m_dst);
    pushhead(m_dst, src_head);
    pushhead(m_src, dst_head);
    cout << sz[m_dst] << '\n';

}

void Divide(){
    int m_src, m_dst;
    cin >> m_src >> m_dst;
    m_src--;
    m_dst--;
    int cnt = sz[m_src];
    vector<int> box;
    for(int i = 0; i < cnt/2; i++){
        box.push_back(rmhead(m_src));
    }
    for(int i = (int) box.size() - 1; i >= 0; i--){
        pushhead(m_dst, box[i]);
    }
    cout << sz[m_dst] << '\n';

}

void Present(){
    int pn;
    cin >> pn;
    int a = prv[pn];
    int b = nxt[pn];
    if(a == 0) a = -1;
    if(b == 0) b = -1;
    cout << a+2*b << '\n';
}

void Belt(){
    int num;
    cin >> num;
    num--;
    int a = head[num];
    int b = tail[num];
    int c = sz[num];
    if(a == 0) a = -1;
    if(b == 0) b = -1;
    cout << a + 2*b + 3*c << '\n';
}

int main() {
    fastio;
    cin >> q;
    while(q--){
        int stage;
        cin >> stage;
        if(stage == 100){
            Build();
        }
        if(stage == 200){
            Move();
        }
        if(stage == 300){
            Change();
        }
        if(stage == 400){
            Divide();
        }
        if(stage == 500){
            Present();
        }
        if(stage == 600){
            Belt();
        }

    }
    return 0;
}
