#include <iostream>

class list_head {
	size_t diff = 0;
	void* elt;

public:
	// Add an elt to the list
	void add(void* elt) {
		list_head* list = this;

		while (list->diff != 0) {
			list = (list_head*)(((size_t)list) ^ diff);
		}
		list_head* new_list = new list_head;
		new_list->elt = elt;

		list->diff = ((size_t)list) ^ ((size_t)new_list);
	}

	// Get the ith element of the list
	void* get(int i) const {
		const list_head* list = this;

		while (i != 0 && list->diff != 0) {
			list = (list_head*)(((size_t)list) ^ diff);
			--i;
		}

		return list->elt;
	}
};

int main() {
	int x = 0;
	int y = 1;
	int z = 3;


	list_head h;
	h.add(&x);
	h.add(&y);
	h.add(&z);
/*
	std::cout << " List: " << std::endl;
	std::cout <<"	" <<  *((int*)h.get(1));
	std::cout <<"	" <<  *((int*)h.get(2));
	std::cout <<"	" <<  *((int*)h.get(3));
*/
}

