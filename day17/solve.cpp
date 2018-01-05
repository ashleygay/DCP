#include <string>
#include <vector>


struct FileIterators
{
	int beg = 0;
	int end = 0;
};


// We find the first directory on the left that matches
// the level of indentation (ie the number of \t that we want)
int find_parent_directory(std::string& str, int beg, int indent)
{
	



}


int get_file_indent(std::string& str, int beg)
{
	int indent = beg;
	for (; str[indent] == '\t' && indent != 0; --indent);
	return beg - indent; // We count the numbers of \t
}


// Return the bounds of the word pointed by the index i
FileIterators get_file(std::string& str, int i)
{
	int beg = i;
	int end = i;
	for (; str[beg] != '\t' && beg != 0; --beg);
	for (; str[end] != '\n' && end != str.size(); ++end);
	return {beg, end};
}

int main()
{
	std::string str = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
	int path_max = 0;
	for (int i = 0;i < str.size(); ++i) {

		int size = 0;
		// We find all files
		if (str[i] == '.') {
			auto file = get_file(str, i);
			auto beg = file.beg;
			auto end = file.end;
			// We have the beginning and end of the file
			// Depending on the number of \t we want to get
			// a different number of directories.

			//TODO
			// Somehow do a loop here
			int indent = get_file_indent(str, beg);

			//TODO update size here

			// We find the parent directory
			int parent = find_parent_directory(str, indent, indent - 1);


		}


	// We update the max path size
		if (size > path_max)
			path_max = size;

	}
}
