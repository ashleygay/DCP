#include <iostream>

class list_head {

/*	Contents of the diff fields:
 *
 *	A	B	C	D	E
 *	B  <-> A^C <-> B^D <-> C^E <->  D
*/

public:
	list_head(void* elt) : _elt(elt){}

	// Add an elt to the list
	void add(void* elt) {
		list_head* list = this;
		list_head* prev = nullptr;

		while (list->diff != (size_t)prev) {
			auto tmp = list;
			list = (list_head*)(((size_t)prev) ^ list->diff);
			prev = tmp;
		}

		list_head* new_list = new list_head(elt);
		new_list->diff = (size_t)list;

		list->diff = ((size_t)prev) ^ ((size_t)new_list);
	}

	// Get the ith element of the list
	void* get(int i) const {
		const list_head* list = this;
		const list_head* prev = nullptr;

		while (i != 0 && list->diff != (size_t)prev) {
			auto tmp = list;
			list = (list_head*)(((size_t)prev) ^ list->diff);
			prev = tmp;
			--i;
		}

		return list->_elt;
	}

private:

	size_t diff = 0;
	void* _elt = nullptr;


};

void print_index(list_head *h, int i)
{
	std::cout <<"	index " << i << " -> " <<  *((int*)h->get(i)) << std::endl;
}


int main() {
	int start = -1;
	int x = 0;
	int y = 1;
	int z = 2;


	list_head h(&start);
	h.add(&z);
	h.add(&x);
	std::cout << " List: " << std::endl;
	print_index(&h, 0);
	print_index(&h, 1);
	print_index(&h, 2);
}

