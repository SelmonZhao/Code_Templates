#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std; 

#define MAXC 1100010
#define MAXX 2
#define MAXP 19103
#define MOD 364875103

#define LL __int64

// ��Ҫ�洢 n! mod p 
LL factorialMod[MAXC][MAXX];


class PrimeIndex {
	map < int, int > primes;
	int primeCount;
public:
	PrimeIndex() {
		primeCount = 0;
	}
	void addPrime(int p) {
		if(primes.find(p) != primes.end()) {
			return ;
		}
		primes[p] = primeCount++;
	}
	
	int getIndex(int p) {
		return primes[p];
	}
	
	static PrimeIndex& Instance() {
		static PrimeIndex inst;
		return inst;
	}
};

// ��ʼ�� n! mod p 
void initFactorialMod(int n, int p) {
	int i;
	PrimeIndex &PI = PrimeIndex::Instance();
	PI.addPrime(p);
	
	int pIdx = PI.getIndex(p);
	factorialMod[0][pIdx] = 1;
	for(i = 1; i <= n; ++i) {
		factorialMod[i][pIdx] = factorialMod[i-1][pIdx] * i % p;
	}
}

// ���ֿ����� 
LL mod(LL a, LL b, LL p) {
	if(!b) {
		return 1;
	}
	LL x = mod(a*a%p, b>>1, p);
	if(b&1) {
		x = x * a % p;
	}
	return x;
}

// ���������n<p, m<p mod ����
LL Comb(int n, int m, int p) {
	// n��������ȡm�������m>n�������������ڣ�����0 
	if(m > n) {
		return 0;
	}
	// Comb(n,m,p) = n!/(m!(n-m)!) % p
	// ��x = m!(n-m)!��x'Ϊx��p����Ԫ����x*x'%p=1����Comb(n,m,p) = n!*x'%p
	// ���ݷ���С����a^(p-1)%p=1����a����ԪΪa^(p-2)%p����x' = x^(p-2)%p��
	//  Comb(n,m,p) = n! * (m!(n-m)!)^(p-2) % p
	// ����ת������ n! % p��
	int pIdx = PrimeIndex::Instance().getIndex(p);
	LL ans = 1;
	ans = ans * factorialMod[n][pIdx] % p;
	ans = ans * mod(factorialMod[m][pIdx], p-2, p) % p;
	ans = ans * mod(factorialMod[n-m][pIdx], p-2, p) % p;
	return ans;
}

// ��������� mod ���� 
// C(n,m) % p
LL Lucas(int n, int m, int p) {
	if(m == 0) {
		return 1;
	}
	return Lucas(n/p, m/p, p) * Comb(n%p, m%p, p) % p;
}


int main() {
	int p = 11;
	initFactorialMod(MAXC-1, p);
	int n = 10, m = 3;
	for(int i = 3; i <= n; ++i) {
		printf("C(%d,%d) mod %d = %I64d\n", i,m,p, Lucas(i, m, p));
	}
	
	return 0;
}




