#include <stdint.h>
#include <iostream>

// Simple array implmentation
template <size_t N = 5, typename T = int>
class Record
{
	public:
		void record(T id)
		{
			for (size_t i = N - 1; i > 0; --i)
				_internal[i] = _internal[i - 1];

			_internal[0] = id;
		}

		// index: [1, N]
		T get_last(size_t index)
		{
			return _internal[--index];
		}

	private:
		T _internal[N];
};


// Cyclic buffer implementation
// BUG doesnt work for N = 1
template <size_t N = 5, typename T = int>
class CyclicRecord
{
	CyclicRecord()
	{
		for (size_t i = 1; i < N - 1; ++i) {
			_internal[i]->next = &_internal[i + 1];
			_internal[i]->prev = &_internal[i - 1];
		}
		start->next = ++start;
		start->prev = end;
		end->next = start;
		end->prev = --end;
	}

	template <typename Content = T>
	struct BufferCell
	{
		struct BufferCell* next;
		struct BufferCell* prev;
		Content data;
	};

public:
	void record(T id)
	{
/*
		start->data = content;
		auto tmp = 


		end = end->prev;
*/
	}

	T get_last(size_t index)
	{
		--index;
		auto tmp = start;
		for (; index != 0; tmp = tmp->next, --index);
		return tmp->data;
	}

private:
	BufferCell<T> _internal[N];
	BufferCell<T>* start = &_internal[0];
	BufferCell<T>* end = &_internal[N - 1];
};


int main()
{
	Record r;
	r.record(13);
	r.record(14);
	r.record(15);
	std::cout << "Last : " << r.get_last(1) << std::endl;
	std::cout << "Last : " << r.get_last(2) << std::endl;
	std::cout << "Last : " << r.get_last(3) << std::endl;
}
