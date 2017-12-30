#include <iostream>
#include <array>
#include <vector>

using SolutionVector = std::vector<std::vector<int>>;

const extern std::vector<int> def_steps = {1,2};

template <int NbSteps = 4, std::vector<int> const& steps = def_steps>
struct Solver
{
	constexpr SolutionVector solve()
	{
		return {{1,1,1,1}};
	}
};

template <typename T>
void print_solutions(T v)
{
	for (auto a : v) {
		for (auto i : a) {
			std::cout << i;
		}
		std::cout << std::endl;
	}
}

int main()
{
	Solver s;
	auto t = s.solve();
	print_solutions(s.solve());
	print_solutions(t);
}
