#include <iostream>

using namespace std;

#define MAXN 100010

int n, k;
int sum[MAXN];
char str[3000000];

void input() {
	getchar();
	int i, idx = 1;
	sum[0] = 0;
	while(gets(str)) {
		i = 0;
		int s = 0;
		while(str[i] != '\0' && str[i] != '\n') {
			if(str[i] >= '0' && str[i] <= '9') {
				s = s * 10 + (str[i] - '0');
			}else if(s > 0) {
				sum[idx] = sum[idx-1] + s;
				s = 0;
				++idx;
			}
			++i;
		}
		if(s > 0) {
			sum[idx] = sum[idx-1] + s;
			s = 0;
			++idx;
		}
		if(idx == n + 1) {
			break;
		}
	}
}



//////////////////////////////////////////////////////////////////
/////////////////////////б���Ż�-ģ��////////////////////////////
//////////////////////////���ƽ��ֵ//////////////////////////////

#define ll long long

// �������У�˫�˶���ʵ�֣�ά�� ����͹�����ߣ������д����ԭ�����±� 
int deq[MAXN];
// ˫�˶��е�����ָ�� 
int head, tail;

bool isBigger(int i, int j, int k) {
	// i-k��б�� K(i, k) = (sum[k] - sum[i]) / (k-i)
	// j-k��б�� K(j, k) = (sum[k] - sum[j]) / (k-j)
	// K(i, k) >= K(j, k)
	return (ll)(sum[k] - sum[i]) * (ll)(k-j) >= (ll)(sum[k] - sum[j]) * (ll)(k-i);
}

double getMaxSlope() {
	head = tail = 0;
	double slope, maxv = 0; 
	for(int i = k; i <= n; i++) {
		// ��(i-k)��Ҫ���뵥�����У������������β�ĵ� deq[tail-1] �Ǹ� ����͹���㣬�����ɾ�� 
		while(head + 1 < tail && isBigger(deq[tail-2], deq[tail-1], i-k))
			--tail;
		// ��(i-k)���뵥������β��		
		deq[tail++] = i-k;
		
		// �߶�A = <deq[head] - i> 
		// �߶�B = <deq[head+1] - i> 
		// K(A) < K(B) ɾ��������Ԫ��
		// ֱ������  K(A) >= K(B)���� <deq[head] - i>Ϊ�������ߵ����� 
		while(head + 1 < tail && !isBigger(deq[head], deq[head+1], i))
			++head;
		
		// �������ߵ����߸������ֵ 
		slope = (sum[i] - sum[deq[head]]) * 1.0 / (i - deq[head]);
		if(slope > maxv) {
			maxv = slope;
		} 
	}	 
	return maxv;
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

int main() {
	//freopen("1.in", "r", stdin);
	//freopen("1.my.out", "w", stdout);
	while( scanf("%d %d", &n, &k) != EOF ) {
		input();
		printf("%.2lf\n", getMaxSlope());
	}
	return 0;
}
/*
20 3
96 86 94 44 24 88 15 4 49 1 59 19 81 97 99 82 90 99 10 58

// 14 - 18, 97,99,82,90,99
*/
