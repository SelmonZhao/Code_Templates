#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;


#define MAXP 65540
#define MOD 9937 
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

struct factor {
	int prime, count;
	factor() {
	} 
	factor(int p, int c) {
		prime = p;
		count = c;
	}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};

// �����������ɸѡ�� 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < MAXP; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
		    //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
			for(LL j = (LL)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// ��ʽ�ֽ� - ��n�ֽ�������ݳ˻�����ʽ
// ������
// 252 = (2^2) * (3^2) * (7^1) 
// �� ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
	ans.clear();
	if(n == 1) {
		return ;
	}
	// �����Գ� 
	for(int i = 1; i <= primes[0]; i++) {
		if(n % primes[i] == 0) {
			factor f(primes[i], 0);
			while( !(n % primes[i]) ) {
				n /= primes[i];
				f.count ++;
			}
			ans.push_back(f);
		}
		if(n == 1) {
			return ;
		}
	}
	// ©��֮������ ������MAXP�����������1�� 
	ans.push_back( factor(n, 1) );
}

int power(int a, int b, int c) {
	if(b == 0) {
		return 1 % c; 
	}
	int x = power(a*a%c, b/2, c);
	if(b&1)
		x = x * a % c;
	return x;
}

// n�����ӡ�m����ɫ
int n, m;
// ���������ķ�����
int ans;

int polyaPart(int fac, int facEula) {
	return facEula % MOD * power(m % MOD, n/fac, MOD) % MOD;
}

// ��ʽ�ֽ��ݹ�ö���������� 
// ö�����ӵ�ͬʱ��ö��ÿ�����ӵ�ŷ������ 
void emunFactor(int depth, vector <factor> fact, int now, int eula) {
	if(fact.size() == depth) {
		//printf("%d %d\n", now, eula);
		ans = (ans + polyaPart(now, eula) ) % MOD;
		return ;
	}
	factor &f = fact[depth];
	int i;
	emunFactor(depth+1, fact, now, eula);
	eula *= (f.prime - 1);
	now *= f.prime;
	for(i = 1; i <= f.count; ++i) {
		emunFactor(depth+1, fact, now, eula);
		now *= f.prime;
		eula *= f.prime;
	}
}


int main() {
	Eratosthenes();
	int i, t;
	while(scanf("%d %d", &n, &m)!=EOF) {
		if(m==0) {
			printf("0\n");
			continue;
		}
		ans = 0;
		vector <factor> v;
		Factorization(n, v);
		emunFactor(0, v, 1, 1);
		
		n %= MOD;
		for(i = 1; ; ++i) {
			if(n*i % MOD == ans) {
				break;
			}
		}
		printf("%d\n", i);
	}
	return 0;
} 
