#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
	int num[500];
	int length;

	BigInt(string s){
		memset(num, 0, sizeof(num));
		length = s.length();
		for(int i = length - 1; i >= 0; i--)
			num[length - 1 - i] = s[i] - '0';
	}

	void big_swap(BigInt& obj){
		BigInt tmp = obj;
		obj = *this;
		*this = tmp;
		return;
	}

	bool operator == (BigInt const& obj){
		if(length != obj.length)
			return 0;
		for(int i = 0; i < length; i++)
			if(num[i] != obj.num[i])
				return 0;
		return 1;
	}

	bool operator < (BigInt const& obj){
		if(length > obj.length)
			return 0;
		else if(length < obj.length)
			return 1;
		for(int i = length - 1; i >= 0; i--){
			if(num[i] > obj.num[i])
				return 0;
			else if(num[i] < obj.num[i])
				return 1;
		}
		return 0;
	}

	BigInt operator - (BigInt const& obj){
		BigInt result("");
		int borrow = 0;
		for(int i = 0; i < length; i++){
			result.num[i] = num[i] - obj.num[i] - borrow;
			if(result.num[i] < 0){
				result.num[i] += 10;
				borrow = 1;
			}else{
				borrow = 0;
			}
		}

		result.length = length;
		for(int i = length - 1; i >= 0; i--){
			if(result.num[i] == 0)
				result.length--;
			else
				break;
		}
		result.length = result.length ? result.length : 1;
		return result;
	}

	BigInt operator * (BigInt obj){
		BigInt curr("");
		for(int i = 0; i < length; i++){
			for(int j = 0; j < obj.length; j++){
				curr.num[i + j] += num[i] * obj.num[j];
			}
		}

		int carry = 0;
		for(int i = 0; i <= (length + obj.length); i++){
			curr.num[i] += carry;
			carry = curr.num[i] / 10;
			curr.num[i] %= 10;
			curr.length = (curr.num[i] == 0 ? curr.length : i + 1);
		}	
		return curr;
	}

	void devide_by_two(){
		int tenth = 0;
		for(int i = length - 1; i >= 0; i--){
			num[i] = (num[i] + tenth * 10);
			tenth = (num[i] & 1);
			num[i] >>= 1;
		}
		length -= (num[length - 1] == 0);
		return;
	}

	void multiply_by_two(){
		int carry = 0;
		for(int i = 0; i <= length; i++){
			num[i] = (num[i] * 2 + carry);
			carry = (num[i] >= 10 ? 1 : 0);
			num[i] %= 10;
		}
		length += (num[length] != 0);
		return;
	}

	void print(){
		for(int i = length - 1; i >= 0; i--){
			printf("%d", num[i]);
		}
		printf("\n");
		return;
	}
};

template <class T>
void Binary(T& a, T& b){
	T GCD("1"), n(""), m(""), zero("0");

	if(a < b){
		n = a, m = b;
	}
	else{
		n = b, m = a;
	}

	while(!(n ==  zero) && !(m == zero)){
		if(n.num[0] % 2 == 0 && m.num[0] % 2 == 0){
			n.devide_by_two(), m.devide_by_two(), GCD.multiply_by_two();
		}else if(n.num[0] % 2 == 0){
			n.devide_by_two();
		}else if(m.num[0] % 2 == 0){
			m.devide_by_two();
		}
		if(m < n) 
			m.big_swap(n);
		m = m - n;
	}
	
	GCD = GCD * n;
	GCD.print();
	return;	
}

int main(){
	string a, b;
	cin >> a >> b;

	BigInt A(a), B(b);
	Binary(A, B);
}
