#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

// RMQ ���� GCD ѯ��

const int MAXM = 18;
const int MAXN = (1 << MAXM) + 1;

// typedef long long ValueType;
// typedef double ValueType;


typedef int ValueType;
int lg2K[MAXN];

ValueType GCD(ValueType a, ValueType b) {
    return !b ? a : GCD(b, a % b);
}

void RMQ_Init(ValueType A[], int ALen, int(*f)[MAXN]) {
    int i, j, k = 0;

    for (i = 1; i <= ALen; i++) {
        lg2K[i] = k - 1;
        if ((1 << k) == i) k++;
    }

    for (i = 0; i < MAXM; i++) {
        for (j = 1; j + (1 << i) - 1 <= ALen; j++) {
            if (i == 0) {
                f[i][j] = A[j];
            }
            else {
                f[i][j] = GCD(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
}

/*
�����䳤��Ϊ2^k����X��ʾ������Ϊ[a, a + 2^k)��Y��ʾ������Ϊ(b - 2^k, b]��
����Ҫ����һ����������X���Ҷ˵������ڵ���Y����˵�-1���� a+2^k-1 >= b-2^k��
��2^(k+1) >= (b-a+1), ����ȡ��������2Ϊ�ף����� k+1 >= lg(b-a+1)����k >= lg(b-a+1) - 1��
k ֻҪ��Ҫȡ��С��������������������( lg(x)������2Ϊ��x�Ķ��� )��
*/
ValueType RMQ_Query(ValueType A[], int(*f)[MAXN], int a, int b) {
    if (a == b) {
        return A[a];
    }
    else if (a > b) {
        a = a^b, b = a^b, a = a^b;
    }
    int k = lg2K[b - a + 1];
    return GCD(f[k][a], f[k][b - (1 << k) + 1]);
}

