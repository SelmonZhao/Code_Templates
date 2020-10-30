/*
ŷ��������
n�ֽ������ӱ�ʾΪn = p1^e1 * p2^e2 * ... * pk^ek
��n��ŷ������Ϊ f(n) = (p1-1)p1^(e1-1) * (p2-1)p2^(e2-1) * ... * (pk-1)pk^(ek-1)

��չŷ������
a^b % c
�� b >= phi(c), a^b % c = a^(b % phi(c) + phi(c)) % c

Author: WhereIsHeroFrom
Update Time: 2020-10-29
Algorithm Complexity: O(sqrt(n))

*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXP 65540
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

// �����������ɸѡ�� 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			//��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
			for (LL j = (LL)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// ŷ������ - ��ȡС��n��������n���ص����ĸ��� 
// ������
// Phi(10) = 4
// �� 1��3��7��9  �ܹ�4�� 
LL Phi(LL n) {
	if (n == 1) {
		return 1;
	}
	LL ans = 1;
	// �����Գ� 
	for (int i = 1; i <= primes[0]; i++) {
		LL p = primes[i];
		if (n % p == 0) {
			n /= p;
			ans *= (p - 1);
			while (!(n % p)) {
				n /= p;
				ans *= p;
			}
		}
		if (n == 1) {
			return ans;
		}
	}
	return ans * (n - 1);
}

LL Exp(LL a, LL b, LL c) {
	if (b == 0) {
		return 1 % c;
	}
	LL tmp = Exp(a*a%c, (b >> 1), c);
	if (b & 1) {
		tmp = tmp * a % c;
	}
	return tmp;
}

// ��չŷ���������� a^b MOD c
LL ExtendPhi(LL a, LL b, LL c) {
	LL ph = Phi(c);
	if (b <= ph) {
		return Exp(a, b, c);
	}

	// ʵ���õ�ŷ�����������ʱ��
	// b ������һ���ܴ�������� b �Ǹ����ʽ���Ǿ�����ߵ���ʽ
	return Exp(a, b % ph + ph, c);
}
