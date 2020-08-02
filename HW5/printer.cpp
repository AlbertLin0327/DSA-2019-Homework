#include <bits/stdc++.h>
#include "minmax-heap.hpp"
using namespace std;

int32_t N, M; 
unordered_map <int, size_t> quotas;
vector < minmax_heap <pair <int, int> >* > printers;

void drop(int32_t printer_id){
	if(!printers[printer_id]->empty()){
		int32_t job_id = printers[printer_id]->min().second;
		printers[printer_id]->pop_min();
		cout << job_id << " dropped on printer " << printer_id << endl;
	}else
		cout << "no jobs in " << printer_id << endl;
	
	return;
}

void add(int32_t job_id, int32_t priority, int32_t printer_id){
	if(quotas.find(printer_id) != quotas.end() && (uint32_t)printers[printer_id]->size() >= quotas[printer_id])
		drop(printer_id);

	printers[printer_id]->push(make_pair(priority, job_id));
	cout << job_id << " added to printer " << printer_id << " with priority " << priority << endl;
	return;
}

void quota(size_t q, int32_t printer_id){
	quotas[printer_id] = q;
	size_t size = printers[printer_id]->size();

	while(printers[printer_id]->size() > q)
		drop(printer_id);
	
	cout << "quota " << q << " set for " << printer_id << endl;
	return;
}

void print(int32_t printer_id){
	if(!printers[printer_id]->empty()){
		int32_t job_id = printers[printer_id]->max().second;
		printers[printer_id]->pop_max();
		cout << job_id << " printed on printer " << printer_id << endl;
	}else
		cout << "no jobs in " << printer_id << endl;
	return;
}

int main(){
	cin >> N >> M;
	getchar(); // read the '\n' at the end
	string line;

	printers.reserve(N);
	
	for(int i = 0; i < N; i++)
		printers.push_back(new minmax_heap < pair <int, int> >);

	while(M--){
		getline(cin, line);
		int32_t idx = 0;
		string instruction[5];
		stringstream ss(line);
		while(getline(ss, instruction[idx], ' '))
			idx++;

		if(instruction[0] == "add")
			add(stoi(instruction[1]), stoi(instruction[2]), stoi(instruction[3]));
		else if(instruction[0] == "quota")
			quota((size_t)stoull(instruction[1]), stoi(instruction[2]));
		else if(instruction[0] == "drop")
			drop(stoi(instruction[1]));
		else
			print(stoi(instruction[1]));
	}
}
