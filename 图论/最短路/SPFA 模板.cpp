#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long ValueType;
const int maxn = 1000010;
const int maxm = 1000010;
const ValueType inf = (ValueType)1e9 * 1e9;

struct Edge {
    int u, v, next;
    ValueType w;
    Edge(){}
    Edge(int _u, int _v, ValueType _w, int _next) :
        u(_u), v(_v), w(_w), next(_next)
    {
    }
}edges[maxm];

int head[maxn], edgeCount;
int visited[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, ValueType w) {
    edges[edgeCount] = Edge(u, v, w, head[u]);
    head[u] = edgeCount++;
}

void SPFA(int n, int st, ValueType *dist) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (st == i) ? 0 : inf;
        visited[i] = 0;
    }
    queue <int> que;
    que.push(st);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        // ����������
        if (visited[u] ++ > n) {
            //break;
        }

        // ���ñ�������������� ���·��Ϣ
        for (int e = head[u]; ~e; e = edges[e].next) {
            int v = edges[e].v;
            if (dist[u] + edges[e].w < dist[v]) {
                dist[v] = dist[u] + edges[e].w;
                que.push(v);
            }
        }
    }
}

