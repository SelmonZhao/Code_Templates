#include <iostream>
#include <cstring>
using namespace std;

#define MAXP 65536
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];
 
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

int main() {
	Eratosthenes();
	printf("%d\n", primes[0]);
	return 0;
}
