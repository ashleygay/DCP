#include <iostream>
#include <random>

long double estimate_pi(int r)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Size of side of the the square
	int size = 2 * r;
	// We get a million points to try and fit inside the circle
	size_t nb_points = size * size;

	size_t points_inside = 0;
 	std::uniform_int_distribution<> dis(0, size);
	for (size_t i = 0; i < nb_points; ++i) {
		int x = dis(gen);
		int y = dis(gen);
		if ((x * x + y * y) < r * r)
			++points_inside;
	}
	return (points_inside * 4)/((double)(r * r));
}


int main()
{
	long double pi = estimate_pi(1000);
	for (float i = 0; i < 100; ++i) {
		pi += estimate_pi(1000);
		pi /= 2.0;
	}
	printf("Pi estimate: %Lf\n", pi);
}
