#include <string>
#include <vector>

class TrieNode
{
public:
	char edgeValue;
public:
	//TODO: what is in the string ?
	// probably only the relevant parts
	void addChild(std::string s);
private:
	std::string value;
	std::list<TrieNode*> children;
};

class Dictionnary
{
public:
	void addEntry(std::string s)
	{
	}

	std::list<std::string> query(std::string s)
	{
	}
private:
	TrieNode root;
};

int main()
{
	Dictionnary d;
	d.addEntry("string");
	d.addEntry("stringest");
	d.addEntry("stringer");

	std::string query = d.query("string");
}
