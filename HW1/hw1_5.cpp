#include <bits/stdc++.h>
using namespace std;

void DEF(int a, int b, int& GCD, int& ITER){
	int range = min(a, b);
	for(int i = 2; i <= range; i++){
		ITER++;
		if(a % i == 0 && b % i == 0)
			GCD = i;
	}
	return;
}

void Reverse_Search(int a, int b, int& GCD, int& ITER){
	int range = min(a, b);
	for(int i = range; i >= 1; i--){
		ITER++;
		if(a % i == 0 && b % i == 0){
			GCD = i;
			return;
		}
	}
	return;
}

void Binary(int a, int b, int& GCD, int& ITER){
	int n = min(a, b), m = max(a, b);
	while(n && m){
		ITER++;
		if(!(n & 1) && !(m & 1))
			GCD <<= 1, n >>=1, m>>= 1;
		else if(!(n & 1) && (m & 1))
			n >>= 1;
		else if((n & 1) && !(m & 1))
			m >>= 1;

		if(n > m) swap(n, m);
		m -= n;		
	}
	GCD *= n;
	return;	
}

void Euclid(int a, int b, int& GCD, int& ITER){
	int n = min(a, b), m = max(a, b);
	while(m % n != 0){
		ITER++;
		swap(n, m); // m, n --> n, m % n
		n %= m;
	}
	GCD = n;
	return;
}

int main(){

	int a, b, gcd, iter; 

	while(1){
		if(scanf("%d%d" , &a, &b) != 2 || a == 0) break;

		gcd = 1, iter = 0;
		DEF(a, b, gcd, iter);
		printf("Case (%d, %d): GCD-By-Def = %d, taking %d iterations\n", a, b, gcd, iter);

		gcd = 1, iter = 0;
		Reverse_Search(a, b, gcd, iter);
		printf("Case (%d, %d): GCD-By-Reverse-Search = %d, taking %d iterations\n", a, b, gcd, iter);

		gcd = 1, iter = 0;
		Binary(a, b, gcd, iter);
		printf("Case (%d, %d): GCD-By-Binary = %d, taking %d iterations\n", a, b, gcd, iter);

		gcd = 1, iter = 0;
		Euclid(a, b, gcd, iter);
		printf("Case (%d, %d): GCD-By-Euclid = %d, taking %d iterations\n", a, b, gcd, iter);

	}
}