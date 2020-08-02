#include <bits/stdc++.h>
using namespace std;
/*
 * Albert H.K Lin 2020
 * NTU CSIE
 *
 * This is my assignment for NTU DSA course
 * There is no guarantee for error query
 *
 * Compile this code with g++ -std=c++17
 * Also have your header bits/stdc++.h prepared
 *
 */

class Node{
private:
	string sale;
	int click_time_stamp;
	string price;
	string age_group;
	string product_id;
	string gender;	
	
public:

	// constructor
	Node(string data[]);

	// get private member
	inline string get_sale(){ return sale; }
	inline int get_click_time_stamp(){ return click_time_stamp; }
	inline string get_price(){ return price; }
	inline string get_age_group(){ return age_group; }
	inline string get_product_id(){ return product_id; }
	inline string get_gender(){ return gender; }

	bool operator < (const Node& obj){
		if(sale == "1" && obj.sale == "1" || sale != "1" && obj.sale != "1")
			return product_id == obj.product_id ? click_time_stamp < obj.click_time_stamp : product_id < obj.product_id;
		else 
			return (sale == "1");
	}

};

// record click time and purchase time
class theta_counter{
public:
	int click_time = 0;
	int purchase_time = 0;
};

// record the data of profit query
class profit_query_container{
public:
	int index;
	int time;
	double theta;

	profit_query_container(int i, int t, double th) :
		index(i), time(t), theta(th){}

};

Node::Node(string data[]):
	sale(data[0]), click_time_stamp(stoi(data[1])), price(data[2]),\
	age_group(data[3]),  gender(data[4]),  product_id(data[5]){}

inline bool Node_pointer_cmp(Node* a, Node* b){
	return a->get_product_id() == b->get_product_id() ?\
		a->get_click_time_stamp() < b->get_click_time_stamp() : a->get_product_id() < b->get_product_id();
}

inline bool PQC_Pointer_cmp(profit_query_container* a, profit_query_container* b){
	return a->time > b->time;
}

namespace{

	// record the data of stdin and stdout
	string query[10005][4];
	string answer[10005];
	int query_num;
	int min_profit_time;

	// record all u, p, t data needed to be construct into data structure
	unordered_set<string > u_table;
	unordered_set<string > p_table;
	set<int > t_table;

	//data structure for get and purchase
	unordered_map<string, unordered_map<string, unordered_map<int, vector<Node* > > > > get_and_pruchase_table;

	//data structure for click	
	unordered_map<string, set<string > > click_table;

	//data structure for profit
	// profit_query record all profit query
	// click_and_purchase_table save all click and purchase in time ordered
	// user_profit save the accumulate click and purchase data
	vector<profit_query_container* > profit_query;
	map<int, unordered_map<string, theta_counter* > > click_and_purchase_table;
	map<string, theta_counter* > user_profit;
}

namespace my_io{

	// read query from stdin
	void read_input(){
		query_num = 0;
		min_profit_time = INT_MAX;
		string str;

		
		while(getline(cin, str, '\n')){
      		int idx = 0;
			stringstream ss(str);
			while(getline(ss, query[query_num][idx], ' '))
				idx++;	

			// fill u, p, t table
			if(query[query_num][0] == "get" || query[query_num][0] == "purchased")
				u_table.insert(query[query_num][1]);
			else if(query[query_num][0] == "clicked"){
				p_table.insert(query[query_num][1]);
				p_table.insert(query[query_num][2]);
			}else if(query[query_num][0] == "profit"){
				t_table.insert(stoi(query[query_num][1]));
				min_profit_time = min(min_profit_time, stoi(query[query_num][1]));
				profit_query.push_back(new profit_query_container(query_num, stoi(query[query_num][1]), stod(query[query_num][2])));
			}else if(query[query_num][0] == "quit")
				break;
		
			query_num++;


      	}

      	sort(profit_query.begin(), profit_query.end(), &PQC_Pointer_cmp);
   		 
	}

	// read from the data file
	void read_data(const string& route){

		// read whole file into data_set
		ifstream f(route);
		string data_set;

		while(getline(f, data_set, '\n')){
			stringstream ss(data_set);

			// parse the line and get the data needed.
			string field, tmp_buf[7];
			int field_cnt = 0;

			while(getline(ss, field, '\t')){
				field_cnt++;
				if(field_cnt == 1)
					tmp_buf[0] = field;
				else if(field_cnt == 4)
					tmp_buf[1] = field;
				else if(field_cnt == 6)
					tmp_buf[2] = field;
				else if(field_cnt == 7)
					tmp_buf[3] = field;
				else if(field_cnt == 10)
					tmp_buf[4] = field;
				else if(field_cnt == 20)
					tmp_buf[5] = field;
				else if(field_cnt == 23)
					tmp_buf[6] = field;
				else
					continue;
			}

			// create the data structure
			if(u_table.find(tmp_buf[6]) != u_table.end())
				get_and_pruchase_table[tmp_buf[6]][tmp_buf[5]][stoi(tmp_buf[1])].push_back(new Node(tmp_buf));
			
			if(p_table.find(tmp_buf[5]) != p_table.end())
				click_table[tmp_buf[5]].insert(tmp_buf[6]);
			
			if(stoi(tmp_buf[1]) >= min_profit_time){
				int nearest_time = *(--t_table.upper_bound(stoi(tmp_buf[1])));
				if(click_and_purchase_table[nearest_time].find(tmp_buf[6]) == click_and_purchase_table[nearest_time].end())
					click_and_purchase_table[nearest_time][tmp_buf[6]] = (new theta_counter);
				click_and_purchase_table[nearest_time][tmp_buf[6]]->click_time++;
				click_and_purchase_table[nearest_time][tmp_buf[6]]->purchase_time += (tmp_buf[0] == "1");
			}

			if(user_profit.find(tmp_buf[6]) == user_profit.end())
				user_profit[tmp_buf[6]] = (new theta_counter);
		}
	}
	
}

// get[u][p][t]
inline string get(string const& u, string const& p, int const& t){
	return ((*(get_and_pruchase_table[u][p][t].begin()))->get_sale() + "\n");
}

// get all data of user's purchase
string purchase(string const& u){
	vector<Node* > result;
	for(auto &p : get_and_pruchase_table[u]){
		for(auto &t : p.second){
			for(auto &n : t.second){
				if(n->get_sale() == "1")
					result.push_back(n);
			}
		}
	}

	ostringstream os;
	sort(result.begin(), result.end(), &Node_pointer_cmp);
	for(auto &c : result)
		os << c->get_product_id() << " " << c->get_click_time_stamp() << " " <<\
        		c->get_price() << " " << c->get_age_group() << " " << c->get_gender() << "\n";
	return os.str();

}

// search for intersection of p1 and p2
string click(string const& p1, string const& p2){
	vector<string > result;
	
	set_intersection(click_table[p1].begin(), click_table[p1].end(),\
	 				 click_table[p2].begin(), click_table[p2].end(), back_inserter(result));

	string ans;
	for(auto &c : result)
		ans += (c + "\n");
	return ans;
}

// process all profit query
void profit_processor(){

	// iterate through all click_and_purchase_table and profit_query
	for(auto [t, p] = tuple{click_and_purchase_table.rbegin(), profit_query.begin()};p != profit_query.end(); p++){
		
		// only add new click and purchase data when encountered the next profit_query times equals table's time
		while(t != click_and_purchase_table.rend() && (*t).first >= (*p)->time){
			for(auto &n : (*t).second){
				user_profit[n.first]->click_time += (*t).second[n.first]->click_time;
				user_profit[n.first]->purchase_time += (*t).second[n.first]->purchase_time;
			}
			t++;
		}
			
		// process all query w/ same time
		int cnt = 0;
		string ans;

		for(auto &n : user_profit){
			if((*p)->theta == 0.0){
				ans += (n.first + "\n");
				cnt++;
			}else{
				if((n.second->click_time) != 0 &&\
				    (double)(n.second->purchase_time) / (double)(n.second->click_time) >= (*p)->theta){
					ans += (n.first + "\n"); 
					cnt++;
				}
			}
			if(cnt >= 10)
				break;
		}
		answer[(*p)->index] = ans;
	}

}

void print(){
	for(int i = 0; i < query_num; i++){
		cout << "********************\n";
		cout << answer[i];
		cout << "********************\n";
	}
	cout << flush;

	return;
}

void solve(){
	
	for(int i = 0; i < query_num; i++){
		if(query[i][0] == "get")
			answer[i] = get(query[i][1], query[i][2], stoi(query[i][3]));
		else if(query[i][0] == "purchased")
			answer[i] = purchase(query[i][1]);
		else if(query[i][0] == "clicked")
			answer[i] = click(query[i][1], query[i][2]);
		else if(query[i][0] == "profit")
			continue;
	}

	profit_processor();

	return;
}



int main(int argc, char* argv[]){

	// fast i/o
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    
	// process stdin input and file data
	my_io::read_input();
	my_io::read_data(argv[1]);

	solve();
	print();

	return 0;
}
