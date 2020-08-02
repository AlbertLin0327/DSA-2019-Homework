// OP: https://dl.acm.org/doi/pdf/10.1145/6617.6621
#ifndef MIN_MAX_HEAP
#define MIN_MAX_HEAP
#include<vector>
#include<algorithm>

// 0, 2, 4, 6, ... Even level is min level
// 1, 3, 5, 7, ... Odd level is Max level

template <typename T, typename _Seq = std::vector<T>, typename _Compare = std::less<T> >
class minmax_heap{
	_Seq s;
	_Compare cmp;

	// __CHAR_BIT__ is how much bits are in a char (mostly 8)
	// __builtin_clz is a built-in function to count leading zeros
	// is_min_level return whether the layer is even or odd (++id changes 0-based to 1-based)
	bool is_min_level(size_t id){
		return !((sizeof(int) * __CHAR_BIT__ - __builtin_clz(++id) - 1) & 1);
	}
	
	// determine whether to go up or down
	void TrickleDown(size_t id){
		if(is_min_level(id)) 
			TrickleDownMin(id);
		else 
			TrickleDownMax(id);
	}

	// get min descendant's index from descending 2 levels
	size_t get_min_descendant(size_t id){
		size_t res = (++id) * 2 - 1;

		for(size_t i = 2; i <= 4; i *= 2){
			for(size_t j = 0; j < i; ++j){
				size_t descendant = id * i + j - 1;

				// found the empty leaf
				if(descendant >= s.size()) 
					return res;

				// update the minimum node
				if(cmp(s[descendant],s[res]))
					res = descendant;
			}
		}
		return res;
	}

	// Sink the new root down
	void TrickleDownMin(size_t id){

		// the root still has children
		while((id + 1) * 2 <= s.size()){
			size_t m = get_min_descendant(id);

			if(cmp(s[m], s[id])){
				std::swap(s[m], s[id]);

				// stop if m is children (get to Max level)
				if(m <= (id + 1) * 2) 
					return;
				
				// compare m (after swap) to its parent
				if(cmp(s[(m + 1) / 2 - 1], s[m]))
					std::swap(s[(m + 1) / 2 - 1], s[m]);
				
				id = m;
			}else return;
		}
	}

	size_t get_max_descendant(size_t id){
		size_t res = (++id) * 2 - 1;

		for(size_t i = 2;i <= 4; i *= 2){
			for(size_t j = 0; j < i; ++j){
				size_t descendant = id * i + j - 1;

				if(descendant >= s.size()) 
					return res;
				
				if(cmp(s[res], s[descendant])){
					res = descendant;
				}
			}
		}
		return res;
	}

	void TrickleDownMax(size_t id){
		while((id + 1) * 2 <= s.size()){
			size_t m = get_max_descendant(id);

			if(cmp(s[id], s[m])){
				std::swap(s[m],s[id]);

				if(m <= (id + 1) * 2) 
					return;
				
				if(cmp(s[m], s[(m + 1) / 2 - 1]))
					std::swap(s[(m + 1) / 2 - 1], s[m]);
				
				id = m;
			}else return;
		}
	}

	// decide whether the newly add node should be in min or Max level, then bubble up
	void BubbleUp(size_t id){
		if(!id) return;

		size_t parent = (id + 1) / 2 - 1;
		if(is_min_level(id)){

			// place newly add node to the level it belongs to by comparing to its parent
			if(cmp(s[parent], s[id])){
				std::swap(s[parent], s[id]);
				BubbleUpMax(parent);

			}else BubbleUpMin(id);

		}else{
			if(cmp(s[id], s[parent])){
				std::swap(s[parent], s[id]);
				BubbleUpMin(parent);

			}else BubbleUpMax(id);
		}
	}

	// Continue to bubble up in the same kinds of level
	void BubbleUpMin(size_t id){
		while(id > 2){
			size_t grandparent = (id + 1) / 4 - 1;

			// only two compare two levels ahead
			if(cmp(s[id], s[grandparent])){
				std::swap(s[id], s[grandparent]);
				id = grandparent;
			}else break;
		}
	}

	void BubbleUpMax(size_t id){
		while(id > 2){
			size_t grandparent = (id + 1) / 4 - 1;

			if(cmp(s[grandparent], s[id])){
				std::swap(s[id], s[grandparent]);
				id = grandparent;
			}else break;
		}
	}

	// search first three node (or the remained) to find the smallest
	size_t find_max_id()const{
		size_t res = 0, n = std::min(s.size(), size_t(3));
		while(--n) 
			if(cmp(s[res], s[n])) res = n;

		return res;
	}

	void erase_id(size_t id){
		s[id] = s.back();
		s.pop_back();
		TrickleDown(id);
	}

public:
	bool empty() const{
		return s.empty();
	}
	
	size_t size() const{
		return s.size();
	}
	
	void push(const T& data){
		s.push_back(data);
		BubbleUp(s.size() - 1);
	}
	
	const T& max() const{
		return s[find_max_id()];
	}
	
	const T& min() const{
		return s[0];
	}
	
	void pop_max(){
		erase_id(find_max_id());
	}
	
	void pop_min(){
		erase_id(0);
	}
	
};
#endif