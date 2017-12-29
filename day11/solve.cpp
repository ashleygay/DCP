#include <string>
#include <list>

class TrieNode
{
public:
	TrieNode(char edge, std::string s): edgeValue(edge), value(s) {}
	TrieNode(): edgeValue('\0'), value("") {}

	//TODO: what is in the string ?
	// probably only the relevant parts
	void addChildNode(char edge, std::string s)
	{
		TrieNode* newchild = new TrieNode(edge, s);
		children.push_back(newchild);
	}

	std::list<std::string> query(std::string& s)
	{
		TrieNode* current = this;
		std::list<std::string> queried;

		for (auto b = s.begin(); b != s.end() && current; ++b) {
			auto c = *b;
			current = current->getNextNode(c);
			if (!current) {
				// The edges of `current' does no have any edge
				// with c as a character.
				return {};
			}
		}
		// We have advanced in the tree, depending on the values in s.
		// We return all the possible substrings.
		queried = current->getAllSubstrings();

		// We add the given prefix to all strings.
		for (auto i = queried.begin(); i != queried.end(); ++i) {
			*i = s + *i;
		}
		return queried;
	}

	// This function tests if the edges of this trienode have the
	// character c. In case of success it returns the pointer to the next
	// node that would be useful to walk the tree.
	TrieNode* getNextNode(char c)
	{
		for (auto b = children.begin(); b != children.end(); ++b) {
			if ((*b)->edgeValue == c)
				return *b; //We return the address of the node
		}
		return nullptr;
	}

	std::list<std::string> getAllSubstrings()
	{
		// From the current node, we get all the possible substrings
		// using a depth-first traversal.
		for (auto n = children.begin(); n != children.end(); ++n){
			//TODO
		}
		return {"tmp", "str"};
	}

	char getEdgeValue() const {return edgeValue;}

private:
	// Represents the value of the incoming edge to this node.
	const char edgeValue;

	std::string value;
	std::list<TrieNode*> children;
};

template <typename T = TrieNode>
class Dictionnary
{
public:
	void addEntry(std::string s)
	{
		//t.addChild(s);
		//TODO We traverse the tree until we run out of characters in s.
		// We check if the tree has edges, if it has, the string is
		// already present in the tree and we stops.
		// If it does not have any children or only one, we check it and
		// we can either split it or add a new edge with the remainder
		// of the string
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
	Dictionnary d;
	d.addEntry("string");
	d.addEntry("stringest");
	d.addEntry("stringer");

	std::list<std::string> query = d.query("string");
}
