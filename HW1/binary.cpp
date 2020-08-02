#include <bits/stdc++.h>
using namespace std;

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

		cout << bitset <12> (n) << "   " << bitset <12> (m) << endl;
		
	}
	GCD *= n;
	return;	
}

int main(){

	int a, b, gcd, iter; 

	while(1){
		if(scanf("%d%d" , &a, &b) != 2) break;
		if(a == 0) break;

		gcd = 1, iter = 0;
		cout << bitset <12> (a) << "   " << bitset <12> (b) << endl;
		Binary(a, b, gcd, iter);
		printf("Case (%d, %d): GCD-By-Binary = %d, taking %d iterations\n", a, b, gcd, iter);

	}
}