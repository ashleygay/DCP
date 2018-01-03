#include <iostream>
#include <climits>
#include <random>

// It picks an object from a stream, using uniform distribution
class StreamElementAccepter
{
public:
	bool check_elt(int elt)
	{
		if (elt < min)
			min = elt;
		if (elt > max)
			max = elt;
		float prob = 1.0/(max - min);

		float r = static_cast <float> (rand())
			/ static_cast <float> (RAND_MAX);
		if (r > prob)
			return false;
		return true;
	}
private:
	int min = INT_MAX;
	int max = INT_MIN;
};

int main()
{
	srand (static_cast <unsigned> (time(0)));
	StreamElementAccepter s;
	int n;
	while (true) {
		std::cin >> n;
		std::cout << "Reading int : " << n << std::endl;
		if (s.check_elt(n))
			std::cout << "Accepting element : " << n << std::endl;
		else
			std::cout << "Rejecting element : " << n << std::endl;
	}
}
