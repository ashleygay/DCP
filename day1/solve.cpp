#include <stack>
#include <queue>
#include <iostream>

/*
 *	The idea is to pop half the elements of the stack and
 *	to enqueue them. We then pop/dequeue one element of each data
 *	structure that we then enqueue again.
 */


void print_stack(std::stack<int> s)
{
	for (std::stack<int>& dump = s; !dump.empty(); dump.pop())
		std::cout << dump.top() << " ";
}

void print_queue(std::queue<int> q)
{
	for (std::queue<int>& dump = q; !dump.empty(); dump.pop())
		std::cout << dump.front() << " ";
}

void solve(std::stack<int>& s, std::queue<int>& q)
{
	// We get the half of the stack in the queue.
	const int c_half = s.size()/2;
	int half = s.size()/2;

	while (half != 0) {
		int elt = s.top();
		s.pop();
		q.push(elt);
		--half;
	}

	std::cout << "Queue first: ";
	print_queue(q);
	std::cout << std::endl;

	// We reverse the order on the stack of the second half
	while (!q.empty()) {
		int elt = q.front();
		q.pop();
		s.push(elt);
	}

	half = s.size()/2;
	while (half != 0) {
		int elt = s.top();
		s.pop();
		q.push(elt);
		--half;
	}

	// We interleave them in the queue
	// we need to count the number that we dequeue,
	// in order to de and enqueue the last character
	int acc = 0;
	while (s.size() != 1) {
		int elt = s.top();
		s.pop();
		q.push(elt);

		elt = q.front();
		q.pop();
		q.push(elt);
		++acc;
	}
	std::cout << "Queue interleaved: ";
	print_queue(q);
	std::cout << std::endl;

	// We have the good order but reversed
	// we use the stack to change it
	while (q.size() != 0) {
		int elt = q.front();
		q.pop();
		s.push(elt);
	}

	std::cout << "Stack in wrong order";
	print_stack(s);
	std::cout << std::endl;


	// We put them back in the queue, in the good order
	while (s.size() != 1) {
		int elt = s.top();
		s.pop();
		q.push(elt);
	}

	while (q.size() != 0) {
		int elt = q.front();
		q.pop();
		s.push(elt);
	}
}

int main()
{
	// [1,2,3,4,5]
	std::stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	std::queue<int> q;

	std::cout << "Stack at the beginning :";
	print_stack(s);
	std::cout << std::endl;

	solve(s, q);

	std::cout << "Stack at the end :";
	print_stack(s);
	std::cout << std::endl;
}
