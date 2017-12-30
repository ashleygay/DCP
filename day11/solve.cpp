#include <iostream>
#include <string>
#include <list>


void print_list(std::list<std::string>& l)
{
	for (auto b = l.begin(); b != l.end(); ++b) {
		std::cout << *b << std::endl;
	}
}


class TrieNode
{
	// Used by traverse() as a return type
	// The index is the next character in the string.
	struct TraverseResult
	{
		TrieNode* ptr;
		int index;
	};


public:
	TrieNode(char edge): edgeValue(edge) {}
	TrieNode(): edgeValue('\0') {}

	void addChildNode(char edge)
	{
		TrieNode* newchild = new TrieNode(edge);
		children.push_back(newchild);
	}

	std::list<std::string> query(const std::string& s)
	{
		auto result = traverse(s);
		const TrieNode* current = result.ptr;
		if (!current)
			return {};
		std::list<std::string> queried;

		// We have advanced in the tree, depending on the values in s.
		// We return all the possible substrings.
		queried = current->getAllSubstrings();

		// We add the given prefix to all strings.
		for (auto i = queried.begin(); i != queried.end(); ++i) {
			*i = s + *i;
		}
		return queried;
	}

	TraverseResult traverse(const std::string& s)
	{
		// We traverse the tree until we run out of characters,
		// in that case we return the last node that we traversed.

		TrieNode* current = this;
		int i = 0;
		for (auto c = s.begin(); c != s.end() && current; ++c) {
			auto tmp = current->getNextNode(*c);
			if (!tmp)
				return {current, i};
			current = current->getNextNode(*c);
			++i;
		}
		return {current, i};
	}

	std::list<std::string> getAllSubstrings() const
	{
		// From the current node, we get all the possible substrings
		// using a depth-first traversal.
		// Do a recursive call.
		std::list<std::string> l;

		for (auto n = children.begin(); n != children.end(); ++n) {
			char c = (*n)->getEdgeValue();
			auto tmp = (*n)->getAllSubstrings();
			for (auto i = tmp.begin(); i != tmp.end(); ++i) {
				*i = c + *i;
			}
			print_list(tmp);
			// We add elements to the list
			l.splice(l.begin(), tmp);
		}

		return l;
	}

	char getEdgeValue() const {return edgeValue;}

	// This function tests if the edges of this trienode have the
	// character c. In case of success it returns the pointer to the next
	// node that would be useful to walk the tree.
	TrieNode* getNextNode(char c) const
	{
		for (auto b = children.begin(); b != children.end(); ++b) {
			if ((*b)->edgeValue == c)
				return *b; // We return the address of the node
		}
		return nullptr;
	}

private:
	// Represents the value of the incoming edge to this node.
	const char edgeValue;

	std::list<TrieNode*> children;
};

template <typename T = TrieNode>
class Dictionnary
{
public:
	void addEntry(std::string s)
	{
		// We traverse the tree until we run out of characters in s.
		// We check if the tree has edges, if it has, the string is
		// already present in the tree and we stops.
		// If it does not have any children or only one, we create it
		// then we add node by node in the tree.
		auto result = t.traverse(s);
		TrieNode* current = result.ptr;
		int index = result.index;
		if (index >= s.size())
			return; // String already present.

		for (;index < s.size(); ++index) {
			current->addChildNode(s[index]);
			current = current->getNextNode(s[index]);
		}
	}

	std::list<std::string> query(std::string s)
	{
		return t.query(s);
	}

private:
	T t;
};

int main()
{
	Dictionnary<TrieNode> d;
	d.addEntry("string");
	d.addEntry("stringest");
	d.addEntry("stringer");

	std::list<std::string> query = d.query("string");
	print_list(query);

}
