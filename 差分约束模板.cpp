#include <iostream>
#include <queue>

using namespace std;

#define MAXN 50010
#define MAXE 1000020
#define INF 100000000

/*
	�����Ȩ�� 
*/ 
class Edge {
public:	
	int edgeValue; 
	int toVertex;
	Edge* next;

	Edge() {}
	void reset(int _to, int _val, Edge* _next) {
		toVertex = _to;
		edgeValue = _val;
		next = _next;
	}
};
typedef Edge* EdgePtr;

/*
	����ͼ 
*/
class Graph {
	EdgePtr *head;
	Edge *edges;
	int edgeCount;
	int vertexCount;

	Graph() {
		// ��ʽǰ���� �洢
		// �ڽӱ��׽��
		head = new EdgePtr[MAXN];
		// ���� 
		dist = new int[MAXN];
		// ������ʴ��� 
		visit = new int[MAXN]; 
		// ���ڴ��
		edges = new Edge[MAXE];
	}
	~Graph() {
		delete [] edges;
		delete [] head;
		delete [] dist;
		delete [] visit;
	}
public:
	int *visit;
	int *dist;
	
	void init(int vCount);
	void initDist();
	void addConstraint(int a, int b, int c); 
	void addEdge(int from, int to, int value);
	bool spfa(int start);

	static Graph& Instance() {
		static Graph inst;
		return inst; 
	}
};

void Graph::init(int vCount) {
	vertexCount = vCount;
	edgeCount = 0;
	for(int i = 0; i <= vCount; i++) {
		head[i] = NULL;
	}
}

/*
	����һ������������
	a - b >= c 
	if(b + c > a) {
		a = b + c; 
		// ����и��£���Ϊ���·������ 
	}
	���ʾb����c�������ܹ�����a���򽨱����£�b->a(ȨΪc) 
*/

void Graph::addConstraint(int a, int b, int c) {
	//printf("%d-%d>=%d\n", a, b, c);
	addEdge(b, a, c);
}

void Graph::addEdge(int from, int to, int value) {
	edges[edgeCount].reset(to, value, head[from]);
	head[from] = &edges[edgeCount++];
}

void Graph::initDist() {
    for(int i = 0; i <= vertexCount; ++i) {
        dist[i] = -INF;
        visit[i] = 0;
    }
}

bool Graph::spfa(int start) {
    int i;
    Edge *e;
    dist[start] = 1;
    visit[start] = 1;
    queue<int> Q;
    Q.push(start);
    while( !Q.empty() ) {
        int u = Q.front();
        Q.pop();
        if( visit[u]++ > vertexCount + 1) {
        	return false;
		}
		 
        for(e = head[u]; e; e = e->next) {
            int &v = e->toVertex;
            int &val = e->edgeValue;
            if( dist[u] + val > dist[v] ) {
                dist[v] = dist[u] + val;
                Q.push(v);
            }
        }
    }
    return true;
}
