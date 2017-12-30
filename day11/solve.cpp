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
		if (current == this) // String is absent
			return {};
		std::list<std::string> queried;

		// We have advanced in the tree, depending on the values in s.
		// We return all the possible substrings.
		queried = current->getAllSubstrings();

		// We add the given prefix to all strings.
		for (auto i = queried.begin(); i != queried.end(); ++i) {
			*i = s + *i;
		}
		if (current->isEndOfWord())
			queried.push_back(s);
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
			std::string s;
			s.insert(0, sizeof(char), c);

			auto substrs = (*n)->getAllSubstrings();
			// If list is empty, we just add it to the list.
			// It is a node without children.
			if (substrs.empty())
				substrs.push_back(s);
			else {
				for (auto i = substrs.begin();
					i != substrs.end(); ++i) {
					*i = s + *i;
				}
				if ((*n)->isEndOfWord())
					substrs.push_back(s);
			}

			// We add elements to the list
			l.splice(l.begin(), substrs);
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

	bool isEndOfWord() const {return end;}
	void markEndOfWord() {end = true;}


private:
	// Represents the value of the incoming edge to this node.
	const char edgeValue;
	bool end = false;

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

		for (;index < s.size(); ++index) {
			current->addChildNode(s[index]);
			current = current->getNextNode(s[index]);
		}
		current->markEndOfWord();
	}

	std::list<std::string> query(std::string s)
	{
		return t.query(s);
	}

private:
	T t;
};

template <typename D = Dictionnary<TrieNode>>
void print_query(D& d, std::string s)
{
	std::cout << "Querying : " << s << std::endl;
	std::list<std::string> q = d.query(s);
	print_list(q);
}

int main()
{
	Dictionnary d;
	d.addEntry("string");
	d.addEntry("stringest");
	d.addEntry("stringer");
	d.addEntry("strigero");
	d.addEntry("btringest");
	d.addEntry("aaa");
	d.addEntry("aaaaa");

	print_query(d, "a");
	print_query(d, "str");
	print_query(d, "btringe");
}
