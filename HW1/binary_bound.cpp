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
	}
	GCD *= n;
	return;	
}

int main(){

	int a, b, gcd, iter, m = 0; 
	int max_a, max_b;
	int bound; cin >> bound;
	for(a = 1; a <= bound; a++){
		for(b = 1; b <= a; b++){
			gcd = 1, iter = 0;
			Binary(a, b, gcd, iter);
			if(iter > m)
				m = iter, max_a = a, max_b = b;
			
		}
	}
	cout << (max_a) << endl;
	cout << (max_b) << endl;
	cout << m;

	
}