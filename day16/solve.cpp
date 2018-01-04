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
public:
	CyclicRecord()
	{
		for (size_t i = 1; i < N - 1; ++i) {
			_internal[i].next = &_internal[i + 1];
			_internal[i].prev = &_internal[i - 1];
		}
		start->next = start + 1;
		start->prev = end;

		end->next = start;
		end->prev = end - 1;
	}

	template <typename Content = T>
	struct BufferCell
	{
		struct BufferCell* next;
		struct BufferCell* prev;
		Content data;
	};

	void record(T id)
	{
		auto old_start = start;
		end->data = id;
		end = end->prev;
		start = end->next;
		start->prev = end;
		start->next = old_start;
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
	CyclicRecord r;
	r.record(13);
	r.record(14);
	r.record(15);
	std::cout << "Last 1st : " << r.get_last(1) << std::endl;
	std::cout << "Last 2nd : " << r.get_last(2) << std::endl;
	std::cout << "Last 3rd : " << r.get_last(3) << std::endl;
}
