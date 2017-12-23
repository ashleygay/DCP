#include <iostream>

int solve(int* tab, size_t size)
{
	int max_sum = INT_MIN;

	int* helper = (int*)malloc(sizeof(int) * size);

	// We iterate over the table.
	for (int i = 0; i < size ; ++i) {
		
	}
	return max_sum;
}

int main()
{
	int tab[4] = [5,1,1,5]; // Result should be 5 + 5
	size_t size = sizeof(tab);
	std::cout << "Sum is : " << solve(tab, size) << std::endl;


}
