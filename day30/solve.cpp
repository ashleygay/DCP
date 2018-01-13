#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::vector<int> vect = {3,3,1,2,3}; // -> result should be 6 units
	int result = 0;

	int i = 0;
	int leftwallindex = 0;
	int interwallcounter = 0;

	while (i < vect.size()) {


		if (vect[leftwallindex] <= vect[i]) { // New wall
			interwallcounter = 0;
			leftwallindex = i;

		}
		else {
			++interwallcounter;
			result += vect[leftwallindex] - vect[i];
		}


		++i;
	}

	if (vect[leftwallindex] > vect[--i]) {
		// Leftmost wall is smaller than the right wall
		result -= (vect[leftwallindex] - vect[i]) * interwallcounter;
	}


	std::cout << "Result is " << result << std::endl;
}
