#include <bits/stdc++.h>
using namespace std;

enum ANSWER{YES, NO};
enum TYPE{CONDITION, RESULT};

class Decision{
public:
	ANSWER ans;
	unordered_map <int, double> factors;
};

class Node{
public:
    Node* left;
    Node* right;

    TYPE type;
    int indice;
    double threshold;
    ANSWER ans;

    Node(Node* L, Node* R, TYPE T):
    	left(L), right(R), type(T){}
};

double epsilon;
int total_elements, total_depth;
vector <Decision*> dataset;

void read_data(const string& route){

	total_elements = total_depth = 0;
	ifstream f(route);
	string line;

	while(getline(f, line, '\n')){
		stringstream ss_line(line);
		string field;

		getline(ss_line, field, ' ');
		Decision* newDecision = new Decision();
		newDecision->ans = (field == "+1") ? YES : NO;

		while(getline(ss_line, field, ' ')){
			stringstream ss_sparse(field);
			string key, value;

			getline(ss_sparse, key, ':');
			getline(ss_sparse, value, ' ');
			newDecision->factors[stoi(key)] = stod(value);
			total_depth = max(stoi(key), total_depth);
		}
		total_elements++;
		dataset.push_back(newDecision);
	}
}

inline double confusion(int a, int b){
	return 2.0 * (float)min(a, b) / (float)(a + b);
}

inline double total_confusion(int c, int d, int e, int f){
	return ((float)(c + d) * confusion(c, d) + (float)(e + f) * confusion(e, f)) / (float)(c + d + e + f);
}

bool find_threshold(const unordered_set <int>& choices, int &indice, double &threshold, ANSWER &major){
	int total_Y = 0, total_N = 0;
	double min_confusion = FLT_MAX;

	for(auto c : choices){
		if(dataset[c]->ans == YES)
			total_Y++;
		else
			total_N++;
	}

	major = (total_Y < total_N) ? NO : YES;

	if(confusion(total_Y, total_N) <= epsilon)
		return 0;
	

	for(int i = 1; i <= total_depth; i++){
		map <double, pair <int, int> > table;
		
		for(auto c : choices){
			double value = dataset[c]->factors.find(i) != dataset[c]->factors.end() ? dataset[c]->factors[i] : 0;
			if(table.find(value) == table.end())
				table[value] = make_pair(0, 0);
			
			if(dataset[c]->ans == YES)
				table[value].first++;
			else
				table[value].second++;
		}

		if(table.size() == 1)
			continue;

		int curr_Y = 0, curr_N = 0;
		for(auto n = table.begin(); n != (--table.end()); n++){
			curr_Y += n->second.first;
			curr_N += n->second.second;
			double curr_confusion = total_confusion(curr_Y, curr_N, total_Y - curr_Y, total_N - curr_N);

			if(curr_confusion < min_confusion){
				min_confusion = curr_confusion;
				threshold = (n->first + (next(n, 1))->first) / 2;
				indice = i;
			}
		}
	}
	if(min_confusion == FLT_MAX)
		return 0;
	
	return 1;
}

Node* construct_Tree(unordered_set <int>& choices){
	if(choices.empty())
		return NULL;

	int indice;
	ANSWER major;
	double threshold;
	if(find_threshold(choices, indice, threshold, major)){

		unordered_set <int> left_indices;
		unordered_set <int> right_indices;
		for(auto c : choices){
			if(dataset[c]->factors[indice] < threshold)
				left_indices.insert(c);
			else
				right_indices.insert(c);
		}

		Node* root = new Node(construct_Tree(left_indices), construct_Tree(right_indices), CONDITION);
		
		root->indice = indice;
		root->threshold = threshold;
		return root;
	}else{
	
		Node* root = new Node(NULL, NULL, RESULT);
		root->ans = major;
		return root;
	}
}

inline void tab_printer(int n){
	for(int i = 0; i < n; i++)
		printf("\t");
}

void preorder_statement(Node* root, int layer){
	if(root == NULL) return;
	
	if(root->type == RESULT){
		tab_printer(layer); printf("return %d;\n", root->ans == YES ? 1 : -1);
	}else{
		tab_printer(layer); printf("if(attr[%d] < %f){\n", root->indice, root->threshold);
		preorder_statement(root->left, layer + 1);
		tab_printer(layer); printf("}else{\n");
		preorder_statement(root->right, layer + 1);
		tab_printer(layer); printf("}\n");
	}
	return;
}

int main(int argc, char* argv[]){
    
	read_data(argv[1]);
	epsilon = stod(argv[2]);

	unordered_set <int> index;
	for(int i = 0; i < total_elements; i++)
		index.insert(i);

	Node* root = construct_Tree(index);
	printf("int tree_predict(double *attr){\n");
	preorder_statement(root, 1);
	printf("}\n");

	return 0;
}
