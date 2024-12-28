#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
    int VerAdj;//顶点序号
    int cost;//权值
    Edge *link;
};

struct Vertex {//顶点表
    int VerName;//顶点名称
    Edge *adjacent;//邻接结点
};

//求每个结点的入度
void GetInDegree(vector<Vertex> &Head, vector<int> &InDegree) {
    int n = Head.size();
    
    //初始化
    for(int i = 1; i <= n; i++) {
        InDegree[i] = 0;
    }

    //遍历顶点表
    for(int i = 1; i <= n; i++) {
        for(Edge *p = Head[i].adjacent; p != nullptr; p = p->link) {
            InDegree[p->VerAdj]++;
        }
    }
}


void DFS(vector<Vertex> &Head, int v, vector<int> &visited) {

    visited[v] = 1;//访问v

    for(Edge *p = Head[v].adjacent; p != nullptr; p = p->link) {
        if(visited[p->VerAdj] != 1) {
            DFS(Head, p->VerAdj, visited);
        }
    }
}

void NonRecDFS(vector<Vertex> &Head, int v, vector<int> &visited) {
    stack<int> stk;//存放即将访问的结点
    stk.push(v);

    while(!stk.empty()) {
        int tem = stk.top(); stk.pop();
    
        if(visited[tem] == 0) {
            visited[tem] = 1;//访问tem
    
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
            if(G[tem][i] && visited[i] == 0) {//边存在 且 未曾访问
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

//判断无向图是否连通以及连通分量数目
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

//给定n个结点的无向图，输出任意两个结点间的所有路径
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
    拓扑排序，并判断是否有环，
    首先将可完成（入度为0）的结点压栈
    弹栈时检查其邻接结点，将其入度-1，若使其入度变为0，则压栈
    若结束时仍存在入度不为0的结点，说明存在环
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

        Topo[++index] = tem;//获取拓扑序的关键,index记录已存放的拓扑序结点数

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

//用数组实现栈的拓扑排序
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
    关键路径
    1，每个结点的最早发生时间，即从源点到该点的最长路径，使得其它路径均在此路径前完成
        可以求出该结点的前驱结点的最短发生时间，进而求出该结点的最短发生时间
        因此可以通过拓扑序来递推，按照拓扑序列来逐个求结点的最早发生时间
    2，每个结点的最晚发生时间,而最晚发生时间 + 该点到汇点的最长路径 <= 汇点的最早发生时间
        因此，求每个结点最晚发生时间，即求汇点的最早发生时间 - 该点到汇点的最长路径
        知道该结点的所有后继结点的最晚发生时间，进而求出该结点的最晚发生时间
        通过逆拓扑序来递推计算即可
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
            //活动最早开始时间为弧尾最早开始时间
            //活动最晚开始时间为弧头最晚开始时间 - 边权值
            if(ve[i] == vl[p->VerAdj] - p->cost) {
                CriticalNodes.push_back(i);//可能含有多条关键路径
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
    //如何判断一个结点是否访问过，可以通过dist来判断
    //若dist[u]为INT32_MAX，则未曾访问，否则访问过
    dist[u] = 0;
    q.push(u);

    while(!q.empty()) {
        int tem = q.front(); q.pop();
        for(Edge *p = Head[tem].adjacent; p != nullptr; p = p->link) {
            //未曾访问该结点，或者曾经访问过该结点，但显然曾经访问时距离一定最短，也就不需要再次访问
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

    for(int i = 0; i < n; i++) {//初始化
        dist[i] = INF;
        pre[i] = -1;
    }

    dist[u] = 0;//到u的距离为0

    vector<int> S(n, 0);

    //for循环执行n次，第一次将u纳入S中，接下来n-1次循环将剩余点逐个纳入
    for(int i = 0; i < n; i++) {

        int v = DijkstraFindMin(S, dist, n);//从不在S中的顶点中选择D值最小的结点v
       
        if(v == -1) {//未找到满足条件的最短结点，故v = -1
            return;//图不连通
        }

        S[v] = 1;
        //访问
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

int Prim(int G[Floyd_N][Floyd_N],int n){//构造图的MST并返回边权和, G为图的邻接矩阵
    int ans=0; //ans为MST边权之和
    vector<int> Lowcost(Floyd_N), pre(Floyd_N);

    vector<int> S(Floyd_N, 0);
    
    for(int i = 0; i < n; i++) {
        Lowcost[i] = INF; 
        pre[i] = -1;
    }
    
    Lowcost[1] = 0; //顶点1作为起点
    
    for(int i = 0; i < n; i++) { //把n个点逐个加入集合S
        int v = DijkstraFindMin(S, Lowcost, n); //选出Lowcost值最小的点
        if(v == -1) {
            return ans; //不存在跨边，图不连通
        }
        if(v != 1) cout << pre[v] << '-' << v; //最小跨边(pre[v],v)是MST中的边
        ans += Lowcost[v];
        S[v] = 1; //累加边权，v加入集合S中
        for(int w = 0; w < n; w++) //更新v邻接顶点的Lowcost和pre值
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
    if(Father[x] <= 0) return x;//x是根
    Father[x] = Find(Father[x]);//路径压缩
    return Father[x];
}

void Union(int x, int y) {
    int fx = Find(x), fy = Find(y);

    if(fx == fy) {//x和y在同一棵树
        return;
    }

    if(Father[fx] < Father[fy]) {//因为存的是相反数，故fy秩小
        Father[fy] = fx;
    } else {
        Father[fx] = fy;
        if(Father[fx] == Father[fy]) {//fx和fy秩相等
            Father[fy]--;//fy的秩加1
        }
    }
}

void Sort(Kruskal_Edge P[], int e) {
    ;
}

int Kruskal(Kruskal_Edge E[], int n, int e){
    //E为图的边集数组, n为顶点数, e为边数
    for(int i = 0; i < n; i++) {
        Make_set(i); //初始化
    }
    Sort(E, e); //对边按权值递增排序,时间复杂度O(eloge)
    int ans = 0, k = 0; //ans为mst边权和, k为已找到的mst边的条数
    for(int i = 0; i < e; i ++){ //从小到大依次扫描每条边
        int u = E[i].head, v = E[i].tail, w = E[i].weight; 
        if(Find(u) != Find(v)){ //边(u,v)是最小生成树的一条边
            cout << u << '-' << v;
            k++; 
            ans += w; 
            Union(u,v); //合并集合
        }
        if(k == n-1) return ans; //成功找到mst的全部n-1条边
    }
    return INF;
}