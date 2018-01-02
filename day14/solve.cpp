#include <iostream>
#include <random>




int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int r = 500;
	// Size of side of the the square
	int size = 1000;
	// We get a million points to try and fit inside the circle
	size_t nb_points = 1000000;

	size_t points_inside = 0;
 	std::uniform_int_distribution<> dis(0, size);
	for (size_t i = 0; i < nb_points; ++i) {
		int x = dis(gen);
		int y = dis(gen);
		if ((x ^ 2 + y ^ 2) <= r ^ 2)
			++points_inside;
	}
	std::cout << "Points inside :" << points_inside << std::endl;
	double pi = (points_inside * 4)/nb_points;
	//printf("Ratio: %lf\n", pi);
	printf("Ratio: %lf\n", pi);
}
