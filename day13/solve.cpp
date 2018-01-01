#include <string>
#include <set>
#include <iostream>

int solve(int i, const std::string& s)
{
	std::set<char> set;

	int max = 0;
	for (auto c = s.cbegin(); c != s.cend(); ++c) {
		int sub_length = 0;

		auto nc = c;
		int k = i; // Max number of different characters in substr.
		while (nc != s.cend()) {

			if (set.find(*nc) == set.end()) {
				if (k != 0) {
					set.insert(*nc);
					--k;
				}
				else
					break;
			}
			++sub_length;
			++nc;
		}

		if (max < sub_length) {
			max = sub_length;
		}
		set.clear();
	}

	return max;
}

int main()
{
	int i = 2;
	std::string s = "abcba";
	// Result should be 3 -> "bcb"
	std::cout << "Result " << solve(i, s)  << std::endl;
}
