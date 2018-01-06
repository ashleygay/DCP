#include <string>
#include <vector>
#include <iostream>


struct FileIterators
{
	int beg = 0;
	int end = 0;
};


// We find the first directory on the left that matches
// the level of indentation (ie the number of \t that we want)
int find_parent_directory(std::string& str, int beg, int indent)
{
	int current_indent = indent;

	// We want the root directory.
	// It is necessarilly at the start.
	if (indent == 0)
		return 0;


	while (current_indent != 0 && beg != 0) {
		if (str[beg] == '\t')
			--current_indent;
		else
			current_indent = indent;
		--beg;
	}
	// We have found number of \t, we return and index into the word.
	return (beg + indent);
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
//	std::string str = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
	std::string str = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
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

			int indent = get_file_indent(str, beg);
			size += (end - beg);

			--indent;
			// We stiil want to get the length of the root dir.
			while (indent != -1) {

				// We find the parent directory
				int parent = find_parent_directory(str, indent + 1, indent);
				//TODO update size here
				auto dir = get_file(str, beg);

				size += (dir.end - dir.beg) + 1;
				--indent;
			}


		}


	// We update the max path size
		if (size > path_max)
			path_max = size;

	}
	std::cout << "Maximum path size: " << path_max << std::endl;
}
