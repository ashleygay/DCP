#include <iostream>
#include <array>
#include <vector>


// TODO create make_array

constexpr std::array<int, 2> def_steps = {1,2};

template <int NbSteps = 4, std::array<int, 2> const& steps = def_steps>
struct Solver
{
	using SolutionVector = std::vector<std::array<int, NbSteps>>;
	constexpr SolutionVector solve()
	{
		int nbsteps = NbSteps;
		std::array<int, steps[steps.size() - 1]>  solution = {};
		// First we consider generating only unique solutions
		// IEe: we consider 211 and 112 the same
		// We can then generate all possibilities easily

		for (auto step : steps) { // We iterate over the different steps.
		}


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
