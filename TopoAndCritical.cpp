#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
    int VerAdj;//�������
    int cost;//Ȩֵ
    Edge *link;
};

struct Vertex {//�����
    int VerName;//��������
    Edge *adjacent;//�ڽӽ��
};

//��ÿ���������
void GetInDegree(vector<Vertex> &Head, vector<int> &InDegree) {
    int n = Head.size();
    
    //��ʼ��
    for(int i = 1; i <= n; i++) {
        InDegree[i] = 0;
    }

    //���������
    for(int i = 1; i <= n; i++) {
        for(Edge *p = Head[i].adjacent; p != nullptr; p = p->link) {
            InDegree[p->VerAdj]++;
        }
    }
}


void DFS(vector<Vertex> &Head, int v, vector<int> &visited) {

    visited[v] = 1;//����v

    for(Edge *p = Head[v].adjacent; p != nullptr; p = p->link) {
        if(visited[p->VerAdj] != 1) {
            DFS(Head, p->VerAdj, visited);
        }
    }
}

void NonRecDFS(vector<Vertex> &Head, int v, vector<int> &visited) {
    stack<int> stk;//��ż������ʵĽ��
    stk.push(v);

    while(!stk.empty()) {
        int tem = stk.top(); stk.pop();
    
        if(visited[tem] == 0) {
            visited[tem] = 1;//����tem
    
            for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
                if(visited[p->VerAdj] != 1) {
                    stk.push(p->VerAdj);
                }
            }
        }
    }
}

void BFS(vector<Vertex> &Head, int v, int n, vector<int> &visited) {
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    queue<int> q;
    visited[v] = 1;
    q.push(v);

    while(!q.empty()) {
        int tem = q.front(); q.pop();
        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(visited[p->VerAdj] == 0) {
                visited[p->VerAdj];
                q.push(p->VerAdj);
            }
        }
    }
}

const int AdjMatrixEdge = 100;
void BFS(int G[AdjMatrixEdge][AdjMatrixEdge], int v, int n, vector<int> &visited) {
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    queue<int> q;
    q.push(v);
    visited[v];

    while(!q.empty()) {
        int tem = q.front(); q.pop();
        for(int i = 0; i < AdjMatrixEdge; i++) {
            if(G[tem][i] && visited[i] == 0) {//�ߴ��� �� δ������
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

//�ж�����ͼ�Ƿ���ͨ�Լ���ͨ������Ŀ
int ConnectedComponentNum(vector<Vertex> &Head, int n, vector<int> &visited) {
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            DFS(Head, n, visited);
            cnt++;
        }
    }

    return cnt;
}

bool PathExisted(vector<Vertex> &Head, int u, int v, int n, vector<int> &visited) {
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    stack<int> stk;
    visited[u]; stk.push(u);

    while(!stk.empty()) {
        int tem = stk.top(); stk.pop();
        if(tem = v) {
            return true;
        }
        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(visited[p->VerAdj] == 0) {
                visited[p->VerAdj] = 1; stk.push(p->VerAdj);
            }
        }
    }

    return false;
}

//����n����������ͼ����������������������·��
void AllPathBetweenTwoNodes(vector<Vertex> &Head, int u, int v, int n, vector<int> &visited) {
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    stack<int> stk;
    visited[u]; stk.push(u);

    vector<int> path;
    path.push_back(u);

    while(!stk.empty()) {
        int tem = stk.top(); stk.pop();
        if(tem = v) {
            for(auto i : path) {
                cout << i << ' ';
            }
            cout << endl;
        }
        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(visited[p->VerAdj] == 0) {

            }
        }
    }
}

bool RingsInUndirectedGrapg(vector<Vertex> &Head, int v, vector<int> &visited, int pre) {
    visited[v] = 1;

    for(Edge *p = Head[v].adjacent; p != nullptr; p = p->link) {
        if(visited[p->VerAdj] == 0) {
            if(RingsInUndirectedGrapg(Head, p->VerAdj, visited, v)) {
                return true;
            } 
        } else if(p->VerAdj != pre) {
            return true;
        }
    }

    return false;
}

bool RingsInDirectedGrapg(vector<Vertex> &Head, int v, vector<int> &visited) {
    visited[v] = 1;

    for(Edge *p = Head[v].adjacent; p != nullptr; p = p->link) {
        if(visited[p->VerAdj] == 0) {
            if(RingsInDirectedGrapg(Head, p->VerAdj, visited)) {
                return true;
            }
        } else if(visited[p->VerAdj == 1]) {
            return false;
        }
    }

    visited[v] = 2;
    return false;
}

/*
    �������򣬲��ж��Ƿ��л���
    ���Ƚ�����ɣ����Ϊ0���Ľ��ѹջ
    ��ջʱ������ڽӽ�㣬�������-1����ʹ����ȱ�Ϊ0����ѹջ
    ������ʱ�Դ�����Ȳ�Ϊ0�Ľ�㣬˵�����ڻ�
*/
bool TopoSort(vector<Vertex> &Head, vector<int> &Topo) {
    int n = Head.size();
    int index = 0;

    vector<int> InDegree(n, 0);
    GetInDegree(Head, InDegree);

    stack<int> stk;
    
    for(int i = 1; i <= n; i++) {
        if(InDegree[i] == 0) {
            stk.push(i);
        }
    }

    while(!stk.empty()) {
        int tem = stk.top(); stk.pop();

        Topo[++index] = tem;//��ȡ������Ĺؼ�,index��¼�Ѵ�ŵ�����������

        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(--InDegree[p->VerAdj] == 0) {
                stk.push(p->VerAdj);
            }
        }
    }

    if(index == n) {
        return true;
    }
    return false;
}

//������ʵ��ջ����������
bool TopoOrderWithoutStack(vector<Vertex> &Head, vector<int> &Topo) {
    int n = Head.size();
    int index_Topo = 0;

    vector<int> InDegree(n, 0);
    GetInDegree(Head, InDegree);
    
    vector<int> stk; int index_stk = -1;
    
    for(int i = 1; i <= n; i++) {
        if(InDegree[i] == 0) {
            stk[++index_stk] = i;
        }
    }

    while(index_stk >= 0) {
        int tem = stk[index_stk--];

        Topo[++index_Topo] = tem;

        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(--InDegree[p->VerAdj] == 0) {
                stk[++index_stk] = p->VerAdj;
            }
        }
    }

    if(index_Topo == n) {
        return true;
    }
    return false;
}

/*
    �ؼ�·��
    1��ÿ���������緢��ʱ�䣬����Դ�㵽�õ���·����ʹ������·�����ڴ�·��ǰ���
        ��������ý���ǰ��������̷���ʱ�䣬��������ý�����̷���ʱ��
        ��˿���ͨ�������������ƣ��������������������������緢��ʱ��
    2��ÿ������������ʱ��,��������ʱ�� + �õ㵽�����·�� <= �������緢��ʱ��
        ��ˣ���ÿ�����������ʱ�䣬����������緢��ʱ�� - �õ㵽�����·��
        ֪���ý������к�̽���������ʱ�䣬��������ý���������ʱ��
        ͨ���������������Ƽ��㼴��
*/

void VertexEarliestTime(vector<Vertex> &Head, vector<int> &Topo, vector<int> &ve) {
    int n = Head.size();

    for(int i = 1; i <= n; i++) {
        ve[i] = 0;
    }

    for(int i = 1; i <= n; i++) {
        int tem = Topo[i];

        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(ve[tem] + p->cost > ve[p->VerAdj]) {
                ve[p->VerAdj] = ve[tem] + p->cost;
            }
        }
    }
}

void VertexLatestTime(vector<Vertex> &Head, vector<int> &Topo, vector<int> &ve, vector<int> &vl) {
    int n = Head.size();

    for(int i = n; i >= 1; i--) {
        vl[i] = ve[n - 1];
    }

    for(int i = n; i >= 1; i--) {
        int tem = Topo[i];

        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            if(vl[p->VerAdj] - p->cost < vl[tem]) {
                vl[tem] = vl[p->VerAdj] -  p->cost;
            }
        } 
    }
}

vector<int> ActivityStartTime(vector<Vertex> &Head, vector<int> &ve, vector<int> &vl) {
    int n = Head.size();

    vector<int> CriticalNodes;

    for(int i = 1; i <= n; i++) {
        for(Edge *p = Head[i].adjacent; p != nullptr; p = p->link) {
            //����翪ʼʱ��Ϊ��β���翪ʼʱ��
            //�����ʼʱ��Ϊ��ͷ����ʼʱ�� - ��Ȩֵ
            if(ve[i] == vl[p->VerAdj] - p->cost) {
                CriticalNodes.push_back(i);//���ܺ��ж����ؼ�·��
            }
        }
    }

    return CriticalNodes;
}


void CriticalPath(vector<Vertex> &Head) {
    int n = Head.size();

    vector<int> Topo(n), ve(n), vl(n);
    
    VertexEarliestTime(Head, Topo,  ve);
    
    VertexLatestTime(Head, Topo, ve, vl);
    
    vector<int> CrtticalNodes = ActivityStartTime(Head, ve, vl);
}

void PowerlessGrapgShortestPath(vector<Vertex> &Head, int n, int u, int dist[], int pre[]) {
    for(int i = 0; i < n; i++) {
        dist[i] = INT32_MAX;
        pre[i] = -1;
    }

    queue<int> q;
    //����ж�һ������Ƿ���ʹ�������ͨ��dist���ж�
    //��dist[u]ΪINT32_MAX����δ�����ʣ�������ʹ�
    dist[u] = 0;
    q.push(u);

    while(!q.empty()) {
        int tem = q.front(); q.pop();
        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            //δ�����ʸý�㣬�����������ʹ��ý�㣬����Ȼ��������ʱ����һ����̣�Ҳ�Ͳ���Ҫ�ٴη���
            if(dist[p->VerAdj] == INT32_MAX) {
                dist[p->VerAdj] = dist[tem] + 1;
                pre[p->VerAdj] = tem;
                q.push(p->VerAdj);
            }
        }
    }
}

int DijkstraFindMin(vector<int> &S, vector<int> dist, int n) {
    int v = -1, min = INF;
    for(int i = 0; i < n; i++) {
        if(S[i] == 0 && dist[i] < min) {
            min = dist[i];
            v = i;
        }
    }
    return v;
}

void Dijkstra(vector<Vertex> &Head, int u, vector<int> dist, vector<int> pre) {
    int n = Head.size();

    for(int i = 0; i < n; i++) {//��ʼ��
        dist[i] = INF;
        pre[i] = -1;
    }

    dist[u] = 0;//��u�ľ���Ϊ0

    vector<int> S(n, 0);

    //forѭ��ִ��n�Σ���һ�ν�u����S�У�������n-1��ѭ����ʣ����������
    for(int i = 0; i < n; i++) {

        int v = DijkstraFindMin(S, dist, n);//�Ӳ���S�еĶ�����ѡ��Dֵ��С�Ľ��v
       
        if(v == -1) {//δ�ҵ�������������̽�㣬��v = -1
            return;//ͼ����ͨ
        }

        S[v] = 1;
        //����
        for(Edge *p = Head[v].adjacent; p != nullptr; p = p->link) {
            if(S[p->VerAdj] == 0 && dist[v] + p->cost < dist[p->VerAdj]) {
                dist[p->VerAdj] = dist[v] + p->cost;
                pre[p->VerAdj] = v;
            }
        }
    }
}

const int Floyd_N = 10;

void Floyd(vector<vector<int>> &G, vector<vector<int>> &D, vector<vector<int>> &path) {
    for(int i = 0; i < G.size(); i++) {
        for(int j = 0; j < G.size(); j++) {
            D[i][j] = G[i][j];
            
            if(i != j && G[i][j] < INT32_MAX) {
                path[i][j] = j;
            } else {
                path[i][j] = -1;
            }
        }
    }

    for(int k = 0; k < G.size(); k++) {
        for(int i = 0; i < G.size(); i++) {
            for(int j = 0; j < G.size(); j++) {
                if(D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }
}


void Warshall(int G[Floyd_N][Floyd_N], int n, int R[Floyd_N][Floyd_N]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            R[i][j] = G[i][j];
        }
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
            }
        }
    }
}

int Prim(int G[Floyd_N][Floyd_N],int n){//����ͼ��MST�����ر�Ȩ��, GΪͼ���ڽӾ���
    int ans=0; //ansΪMST��Ȩ֮��
    vector<int> Lowcost(Floyd_N), pre(Floyd_N);

    vector<int> S(Floyd_N, 0);
    
    for(int i = 0; i < n; i++) {
        Lowcost[i] = INF; 
        pre[i] = -1;
    }
    
    Lowcost[1] = 0; //����1��Ϊ���
    
    for(int i = 0; i < n; i++) { //��n����������뼯��S
        int v = DijkstraFindMin(S, Lowcost, n); //ѡ��Lowcostֵ��С�ĵ�
        if(v == -1) {
            return ans; //�����ڿ�ߣ�ͼ����ͨ
        }
        if(v != 1) cout << pre[v] << '-' << v; //��С���(pre[v],v)��MST�еı�
        ans += Lowcost[v];
        S[v] = 1; //�ۼӱ�Ȩ��v���뼯��S��
        for(int w = 0; w < n; w++) //����v�ڽӶ����Lowcost��preֵ
            if(S[w] == 0 && G[v][w] < Lowcost[w]){
                Lowcost[w] = G[v][w]; 
                pre[w] = v;
        } 
    }
    
    return ans;
}

struct Kruskal_Edge {
    int head;
    int tail;
    int weight;
}; Kruskal_Edge E[1010];

vector<int> Father;

void Make_set(int x) {
    Father[x] == 0;
}

int Find(int x) {
    if(Father[x] <= 0) return x;//x�Ǹ�
    Father[x] = Find(Father[x]);//·��ѹ��
    return Father[x];
}

void Union(int x, int y) {
    int fx = Find(x), fy = Find(y);

    if(fx == fy) {//x��y��ͬһ����
        return;
    }

    if(Father[fx] < Father[fy]) {//��Ϊ������෴������fy��С
        Father[fy] = fx;
    } else {
        Father[fx] = fy;
        if(Father[fx] == Father[fy]) {//fx��fy�����
            Father[fy]--;//fy���ȼ�1
        }
    }
}

void Sort(Kruskal_Edge P[], int e) {
    ;
}

int Kruskal(Kruskal_Edge E[], int n, int e){
    //EΪͼ�ı߼�����, nΪ������, eΪ����
    for(int i = 0; i < n; i++) {
        Make_set(i); //��ʼ��
    }
    Sort(E, e); //�Ա߰�Ȩֵ��������,ʱ�临�Ӷ�O(eloge)
    int ans = 0, k = 0; //ansΪmst��Ȩ��, kΪ���ҵ���mst�ߵ�����
    for(int i = 0; i < e; i ++){ //��С��������ɨ��ÿ����
        int u = E[i].head, v = E[i].tail, w = E[i].weight; 
        if(Find(u) != Find(v)){ //��(u,v)����С��������һ����
            cout << u << '-' << v;
            k++; 
            ans += w; 
            Union(u,v); //�ϲ�����
        }
        if(k == n-1) return ans; //�ɹ��ҵ�mst��ȫ��n-1����
    }
    return INF;
}