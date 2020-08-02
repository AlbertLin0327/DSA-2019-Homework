#include <bits/stdc++.h>
using namespace std;

#define getString(c) ({string s(1, c); s;})

enum Type{OPERATOR, OPERAND};
enum Arity{UNARY, BINARY};

class Built_in_Operator{
public:
	enum Arity arity = BINARY;
	string keyword;

	Built_in_Operator(string str){
		keyword = str;
	}
};

class Symbol{
public:
	enum Type type;
	Built_in_Operator* Operator;
	int Operand;
};

vector <Symbol*> postfix;

map <string, function <int(int)> > unary{
	{"+", [](int a){ return a; }},
	{"-", [](int a){ return -a; }},
	{"!", [](int a){ return a == 0; }},
	{"~", [](int a){ return ~a; }}
};

map <string, function <int(int, int)> > binary{
	{"*", [](int a, int b){ return a * b; }},
	{"/", [](int a, int b){ return (b == 0) ? 0 : a / b; }},
	{"%", [](int a, int b){ return (b == 0) ? 0 : a % b; }},
	{"+", [](int a, int b){ return a + b; }},
	{"-", [](int a, int b){ return a - b; }},
	{"&", [](int a, int b){ return a & b; }},
	{"^", [](int a, int b){ return a ^ b; }},
	{"|", [](int a, int b){ return a | b; }},
	{"<<", [](int a, int b){ return a << b; }},
	{">>", [](int a, int b){ return a >> b; }},
	{"&&", [](int a, int b){ return a && b; }},
	{"||", [](int a, int b){ return a || b; }},
	{"==", [](int a, int b){ return a == b; }},
	{"!=", [](int a, int b){ return a != b; }}
};

Symbol* genSymbol(int data){
	Symbol* NewSymbol = new Symbol;
	NewSymbol->type = OPERAND;
	NewSymbol->Operand = data;
	return NewSymbol;
};

Symbol* genSymbol(Built_in_Operator* data){
	Symbol* NewSymbol = new Symbol;
	NewSymbol->type = OPERATOR;
	NewSymbol->Operator = data;
	return NewSymbol;
};

int precedence_order(Built_in_Operator* OP){
	if(OP->arity == UNARY) 
		return 3;
	string str = OP->keyword;
	if(str == "*" || str == "/" || str == "%")
		return 5;
	else if(str == "+" || str == "-")
		return 6;
	else if(str == "<<" || str == ">>")
		return 7;
	else if(str == "==" || str == "!=")
		return 9;
	else if(str == "&")
		return 10;
	else if(str == "^")
		return 11;
	else if(str == "|")
		return 12;
	else if(str == "&&")
		return 13;
	else if(str == "||")
		return 14;
	else
		return 100;
}

void print_postfix(){
	for(auto c : postfix){
		if((*c).type == OPERAND)
			cout << (*c).Operand << " ";
		else{
			cout << ((*c).Operator)->keyword << " ";
		}
	}
	cout << endl;
}

void Infix_to_Postfix(string input){
	stack <Built_in_Operator*> operator_stack;
	Built_in_Operator* right_paranthesis = new Built_in_Operator("(");

	int len = input.length();
	for(int i = 0; i < len; i++){
		if(isdigit(input[i])){
			int num = input[i] - '0';
			while(isdigit(input[i + 1])){
				i++; num = num * 10 + input[i] - '0';
			}
			postfix.push_back(genSymbol(num));
			cout << num << " to postfix" << endl;
		}else if(input[i] == '('){
			operator_stack.push(new Built_in_Operator("("));
			cout << "push ( to stack" << endl;
		}else if(input[i] == ')'){
			while(!operator_stack.empty() && (operator_stack.top())->keyword != "("){
				Built_in_Operator* NewOP = operator_stack.top();
				operator_stack.pop();
				postfix.push_back(genSymbol(NewOP));
				cout << "pop " << NewOP->keyword << " from stack and add to postfix" << endl;
			}
			if(!operator_stack.empty() && (operator_stack.top())->keyword == "("){
				cout << "pop ( from stack" << endl;
				Built_in_Operator* tmp = operator_stack.top();
				operator_stack.pop(); delete tmp;
			}
		}else if(((input[i] == '+' || input[i] == '-') && ((i != 0 && (!isdigit(input[i - 1]) && input[i - 1] != ')')) || i == 0)) ||\
				(input[i] == '!' && input[i + 1] != '=') || (input[i] == '~')){
			Built_in_Operator* NewOP;
			NewOP = new Built_in_Operator(getString(input[i]));
			NewOP->arity = UNARY;
			operator_stack.push(NewOP);
			cout << "push " << NewOP->keyword << " to stack" << endl;
		}else{
			Built_in_Operator* NewOP;
			if(((input[i] == '<' || input[i] == '>' || input[i] == '&' || input[i] == '|' || input[i] == '=') &&\
				   i != len - 1 && input[i] == input[i + 1]) || (input[i] == '!' && input[i + 1] == '=')){
				NewOP = new Built_in_Operator(getString(input[i]) + getString(input[++i]));
			}else{
				NewOP = new Built_in_Operator(getString(input[i]));
			}
			while(!operator_stack.empty() && precedence_order(NewOP) >= precedence_order(operator_stack.top())){
				Built_in_Operator* NewOP = operator_stack.top();
				operator_stack.pop();
				postfix.push_back(genSymbol(NewOP));
				cout << "pop " << NewOP->keyword << " from stack and add to postfix" << endl;
			}
			operator_stack.push(NewOP);
			cout << "push " << NewOP->keyword << " to stack" << endl;
		}
	}
	while(!operator_stack.empty()){
		Built_in_Operator* NewOP = operator_stack.top();
		operator_stack.pop();
		postfix.push_back(genSymbol(NewOP));
	}
}

int calculate(){
	stack <int> number;
	for(auto& c : postfix){
		if((*c).type == OPERAND)
			number.push((*c).Operand);
		else{
			if(((*c).Operator)->arity == UNARY){
				int num = number.top(); number.pop();
				num = unary[((*c).Operator)->keyword](num);
				number.push(num);
			}else{
				int num1 = number.top(); number.pop();
				int num2 = number.top(); number.pop();
				int ans = binary[((*c).Operator)->keyword](num2, num1);
				number.push(ans);
			}
		}
	}
	return number.top();
}

int main(){
	string infix; cin >> infix; 
	Infix_to_Postfix(infix);
	cout << "---------------------------------------------" << endl;
	print_postfix();
	cout << "---------------------------------------------" << endl;
	cout << "RESULT: " << calculate() << endl;
}