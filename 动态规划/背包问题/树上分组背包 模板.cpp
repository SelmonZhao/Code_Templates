#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 510;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

vector <int> edges[MAXN];

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    int cap[2][MAXC], pre = 0;

    int maxCapacity = m - Knap[u].capacity;
    for (i = 0; i <= maxCapacity; ++i)              // 1�����鱳��������ʼ��
        cap[0][i] = 0;
    for (i = 0; i < edges[u].size(); ++i) {         // 2�����鱳��ö���飨1������1���飩
        int v = edges[u][i];
        if (v == father) continue;
        treeGroupKnapsack(u, v, maxCapacity);       // 3���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]
        for (j = maxCapacity; j >= 0; --j) {        // 4�����鱳������ö������
            cap[pre ^ 1][j] = cap[pre][j];          // 5������鲻ѡ��Ʒ��������̳�����һ��
            for (k = 0; k <= j; ++k) {               
                                                    // 6��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                                                    // ע��һ��Ҫ��������Ϊ 0 �����
                cap[pre^1][j] = opt(
                    cap[pre^1][j],
                    cap[pre][j - k] + dp[v][k]
                );
            }
        }
        pre ^= 1;
    }
    for (i = m; i >= Knap[u].capacity; --i)         // 6��������ѡ
        dp[u][i] = cap[pre][i - Knap[u].capacity] + Knap[u].weight;
    for (i = 0; i < Knap[u].capacity; ++i) 
        dp[u][i] = 0;
    
    // ���ĳ���ӽ��Ϊ 0 ������������ߣ����ע��
    // dp[u][0] = 0;
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************