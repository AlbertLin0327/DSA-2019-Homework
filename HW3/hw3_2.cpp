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
	double Operand;
};

vector <Symbol*> postfix;

map <string, function <double(double)> > unary{
	{"+", [](double a){ return a; }},
	{"-", [](double a){ return -a; }},
	{"!", [](double a){ return a == 0; }},
	{"sin", [](double a){ return sin(a); }},
	{"cos", [](double a){ return cos(a); }},
	{"exp", [](double a){ return exp(a); }},
	{"log", [](double a){ return log(a); }},
	{"fabs", [](double a){ return fabs(a); }},
	{"sqrt", [](double a){ return sqrt(a); }}
};

map <string, function <double(double, double)> > binary{
	{"*", [](double a, double b){ return a * b; }},
	{"/", [](double a, double b){ return (b == 0) ? 0 : a / b; }},
	{"+", [](double a, double b){ return a + b; }},
	{"-", [](double a, double b){ return a - b; }},
	{"&&", [](double a, double b){ return a && b; }},
	{"||", [](double a, double b){ return a || b; }},
	{"==", [](double a, double b){ return a == b; }},
	{"!=", [](double a, double b){ return a != b; }},
	{"pow", [](double a, double b){ return pow(a, b);}}
};

Symbol* genSymbol(double data){
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
	else if(str == "&&")
		return 13;
	else if(str == "||")
		return 14;
	else if(str == "pow")
		return 16;
	else // for '('
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

int ten_pow(int k){
	int res = 1;
	for(int i = 0; i < k; i++)
		res *= 10;
	return res;
}

void Infix_to_Postfix(string input){
	stack <Built_in_Operator*> operator_stack;
	Built_in_Operator* right_paranthesis = new Built_in_Operator("(");

	int len = input.length();
	for(int i = 0; i < len; i++){
		if(isdigit(input[i])){
			double num = input[i] - '0';
			while(isdigit(input[i + 1])){
				i++; num = num * 10 + (double)(input[i] - '0');
			}
			if(input[i + 1] == '.'){
				int decimal = 0; i++;
				while(isdigit(input[i + 1])){
					i++; decimal++;
					num += (double)(input[i] - '0') / (double)ten_pow(decimal);
				}
			}
			postfix.push_back(genSymbol(num));
		}else if(input[i] == '(')
			operator_stack.push(new Built_in_Operator("("));
		else if(input[i] == ')'){
			while(!operator_stack.empty() && (operator_stack.top())->keyword != "("){
				Built_in_Operator* NewOP = operator_stack.top();
				operator_stack.pop();
				postfix.push_back(genSymbol(NewOP));
			}
			if(!operator_stack.empty() && (operator_stack.top())->keyword == "("){
				Built_in_Operator* tmp = operator_stack.top();
				operator_stack.pop(); delete tmp;
			}
		}else if(((input[i] == '+' || input[i] == '-') && ((i != 0 && (!isdigit(input[i - 1]) && input[i - 1] != ')')) || i == 0)) ||\
				(input[i] == '!' && input[i + 1] != '=')){
			Built_in_Operator* NewOP;
			NewOP = new Built_in_Operator(getString(input[i]));
			NewOP->arity = UNARY;
			operator_stack.push(NewOP);
		}else if(isalpha(input[i])){
			string op;
			if(input[i] == 'c')
				op = "cos";
			else if(input[i] == 'e')
				op = "exp";
			else if(input[i] == 'l')
				op = "log";
			else if(input[i] == 'f'){
				op = "fabs"; i++;
			}else if(input[i] == 's' && input[i + 1] == 'q'){
				op = "sqrt"; i++;
			}else if(input[i] == 's')
				op = "sin";
			else
				continue;
			Built_in_Operator* NewOP;
			NewOP = new Built_in_Operator(op);
			NewOP->arity = UNARY;
			operator_stack.push(NewOP);
			i += 2;
		}else{
			Built_in_Operator* NewOP;
			if(((input[i] == '<' || input[i] == '>' || input[i] == '&' || input[i] == '|' || input[i] == '=') &&\
				   i != len - 1 && input[i] == input[i + 1]) || (input[i] == '!' && input[i + 1] == '=')){
				NewOP = new Built_in_Operator(getString(input[i]) + getString(input[i + 1])); i++;
			}else if(input[i] == ','){
				NewOP = new Built_in_Operator("pow");
			}else{
				NewOP = new Built_in_Operator(getString(input[i]));
			}
			while(!operator_stack.empty() && precedence_order(NewOP) >= precedence_order(operator_stack.top())){
				Built_in_Operator* NewOP = operator_stack.top();
				operator_stack.pop();
				postfix.push_back(genSymbol(NewOP));
			}
			operator_stack.push(NewOP);
		}
	}
	while(!operator_stack.empty()){
		Built_in_Operator* NewOP = operator_stack.top();
		operator_stack.pop();
		postfix.push_back(genSymbol(NewOP));
	}
}

double calculate(){
	stack <double> number;
	for(auto& c : postfix){
		if((*c).type == OPERAND)
			number.push((*c).Operand);
		else{
			if(((*c).Operator)->arity == UNARY){
				double num = number.top(); number.pop();
				num = unary[((*c).Operator)->keyword](num);
				number.push(num);

			}else{
				double num1 = number.top(); number.pop();
				double num2 = number.top(); number.pop();
				double ans = binary[((*c).Operator)->keyword](num2, num1);
				number.push(ans);
			}
		}
	}
	return number.top();
}

int main(){
	string infix; cin >> infix; 
	Infix_to_Postfix(infix);
	print_postfix();
	cout << "---------------------------------------------" << endl;
	printf("RESULT: %.6f\n", calculate());
}